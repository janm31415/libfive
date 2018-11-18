/*
libfive: a CAD kernel for modeling with implicit functions
Copyright (C) 2018  Matt Keeter

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this file,
You can obtain one at http://mozilla.org/MPL/2.0/.
*/
#pragma once

#include <Eigen/Eigen>

#include "libfive/render/brep/util.hpp"
#include "libfive/render/brep/region.hpp"
#include "libfive/render/brep/indexes.hpp"

namespace Kernel {

/*
 *  This is documented in a long article at
 *  https://mattkeeter.com/projects/qef
 */
template <unsigned N>
class QEF
{
public:
    struct Solution {
        Eigen::Matrix<double, N, 1> position;
        double value;
        unsigned rank;
        double error;
    };

    using Matrix = Eigen::Matrix<double, N + 1, N + 1>;
    using RowVector = Eigen::Matrix<double, 1, N + 1>;
    using Vector = Eigen::Matrix<double, N + 1, 1>;

    QEF() : AtA(Matrix::Zero()), AtBp(Matrix::Zero()), BptBp(Matrix::Zero())
    {
        // Nothing to do here
    }

    void insert(Eigen::Matrix<double, 1, N> position,
                Eigen::Matrix<double, 1, N> normal,
                double value)
    {
        RowVector ni;
        RowVector pi;

        ni << normal, -1;
        pi << position, value;

        RowVector Bp_row = ni.cwiseProduct(pi);

        AtA += ni.transpose() * ni;
        AtBp += ni.transpose() * Bp_row;
        BptBp += Bp_row.transpose() * Bp_row;
    }

    Solution solve(Eigen::Matrix<double, 1, N> target_pos=
                        Eigen::Matrix<double, 1, N>::Zero(),
                   double target_value=0.0)
    {
        Vector target;
        target << target_pos.transpose(), target_value;

        // Unpack from raw solution to position + value form
        const auto sol = QEF<N>::solve(AtA, AtB(), BtB(), target);

        Solution out;
        out.position = sol.value.template head<N>();
        out.value = sol.value(N);
        out.rank = sol.rank - 1; // Skip the rank due to value
        out.error = sol.error;

        return out;
    }

    /*
     *  Returns a new QEF with the axes set in a bitfield mask preserved
     *
     *  For example, this lets you go from a 2D QEF to a 1D QEF by dropping
     *  one axis from the matrices.
     */
    template <unsigned mask>
    QEF<bitcount(mask)> sub() const
    {
        static_assert(bitcount(mask) <= N, "Too many axes");

        QEF<bitcount(mask)> out;
        unsigned row_ = 0;
        for (unsigned row=0; row <= N; ++row) {
            unsigned col_ = 0;
            if ((mask & (1 << row)) || row == N) {
                for (unsigned col=0; col <= N; ++col) {
                    if ((mask & (1 << col)) || col == N) {
                        out.AtA(row_, col_) = AtA(row, col);
                        out.AtBp(row_, col_) = AtBp(row, col);
                        out.BptBp(row_, col_) = BptBp(row, col);
                        col_++;
                    }
                }
                assert(col_ == bitcount(mask) + 1);
                row_++;
            }
        }
        assert(row_ == bitcount(mask) + 1);

        return out;
    }

    /*
     *  Solves this QEF with constraints applied so that the solution lies
     *  in the subspace specified by NeighborIndex_
     *
     *  Constrained axes are given values based on the evaluation region.
     *
     *  For example, you could use this function to solve a 2D QEF constrained
     *  to lie on a specific cell edge.
     *
     *  This is a building block for more the more general task of "solve this
     *  QEF constrained to a particular region", where we iterate over
     *  subspaces in descending order of dimensionality until we find one
     *  which doesn't escape.
     */
    template <unsigned Neighbor_>
    Solution solveConstrained(Region<N> region,
                              Eigen::Matrix<double, 1, N> target_pos=
                                  Eigen::Matrix<double, 1, N>::Zero(),
                              double target_value=0.0)
    {
        constexpr NeighborIndex Neighbor(Neighbor_);

        constexpr unsigned NumConstrainedAxes = N - Neighbor.dimension();
        static_assert(NumConstrainedAxes <= N,
                      "Wrong number of constrained axes");

        constexpr unsigned MatrixSize = N + NumConstrainedAxes + 1;

        // Build AtA, with extra rows and columns for constraints
        Eigen::Matrix<double, MatrixSize, MatrixSize> AtA_c =
            Eigen::Matrix<double, MatrixSize, MatrixSize>::Zero();
        AtA_c.template topLeftCorner<N + 1, N + 1>() = 2 * AtA;

        Eigen::Matrix<double, MatrixSize, 1> AtB_c =
            Eigen::Matrix<double, MatrixSize, 1>::Zero();
        AtB_c.template head<N + 1>() = 2 * AtB();

        {   // Build up the constrained matrices, which are like AtA and AtB
            // with extra rows + columns to encode the constraints.
            unsigned col = 0;
            for (unsigned j=0; j < N; ++j) {
                if (Neighbor.fixed() & (1 << j)) {
                    // Add symmetric termps to AtA
                    AtA_c(j, N + 1 + col) = 1.0;
                    AtA_c(N + 1 + col, j) = 1.0;

                    AtB_c(N + 1 + col) = (Neighbor.pos() & (1 << j))
                        ? region.upper(j)
                        : region.lower(j);
                    col++;
                }
            }
            assert(col == NumConstrainedAxes);
        }

        // Build the new target matrix, which is padded with zeros
        // for the constrained rows.
        Eigen::Matrix<double, MatrixSize, 1> target_c =
            Eigen::Matrix<double, MatrixSize, 1>::Zero();
        target_c.template head<N>() = target_pos;
        target_c(N) = target_value;

        auto sol = QEF<N + NumConstrainedAxes>::solve(
                AtA_c, AtB_c, BtB(), target_c);

        Solution out;
        out.position = sol.value.template head<N>();
        out.value = sol.value(N);
        out.rank = sol.rank - NumConstrainedAxes - 1;
        out.error = sol.error;

        return out;
    }


protected:
    struct RawSolution {
        Vector value;
        unsigned rank;
        double error;
    };

    /*
     *  Core QEF solver, which knows nothing of our fancy constraint
     *  systems or distance-field details.  It just takes the three matrices
     *  (and a point to minimize towards) and does the math.
     */
    static RawSolution solve(
            const Matrix& AtA,
            const Vector& AtB,
            const Eigen::Matrix<double, 1, 1>& BtB,
            const Vector& target)
    {
        // Our high-level goal here is to find the pseduo-inverse of AtA,
        // with special handling for when it isn't of full rank.
        Eigen::SelfAdjointEigenSolver<Matrix> es(AtA);
        auto eigenvalues = es.eigenvalues().real();

        // Build the SVD's diagonal matrix, truncating near-singular eigenvalues
        Matrix D = Matrix::Zero();
        const double max_eigenvalue = eigenvalues.cwiseAbs().maxCoeff();
        const double EIGENVALUE_CUTOFF = 0.02;
        unsigned rank = 0;
        for (unsigned i=0; i < N + 1; ++i) {
            if (fabs(eigenvalues[i]) / max_eigenvalue > EIGENVALUE_CUTOFF) {
                D.diagonal()[i] = 1 / eigenvalues[i];
                rank++;
            }
        }

        // SVD matrices
        auto U = es.eigenvectors().real().eval(); // = V

        // Pseudo-inverse of A
        auto AtA_inv = (U * D * U.transpose()).eval();

        // Solve for vertex position (minimizing distance to target)
        Vector sol = AtA_inv * (AtB - (AtA * target)) + target;

        // Calculate the resulting error, hard-code the matrix size here so
        // that Eigen checks that all of our types are correct.
        Eigen::Matrix<double, 1, 1> err =
            sol.transpose() * AtA * sol - 2 * sol.transpose() * AtB + BtB;

        // Unpack these results into our solution struct
        RawSolution out;
        out.value = sol;
        out.rank = rank;
        out.error = err(0);

        return out;
    }

    // Pack our expanded A^T B' into a convention A^T B for solving
    Vector AtB() const {
        return AtBp * Vector::Ones();
    }

    // Pack our expanded B'^T B' into a convention B^T B for solving
    Eigen::Matrix<double, 1, 1> BtB() const {
        return RowVector::Ones() * BptBp * Vector::Ones();
    }

    // Here are our matrices!
    Matrix AtA;
    Matrix AtBp;
    Matrix BptBp;

    friend class QEF<0>;
    friend class QEF<1>;
    friend class QEF<2>;
    friend class QEF<3>;
};

}   // namespace Kernel
