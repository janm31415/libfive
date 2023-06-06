if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
endif()


set(SRCS_EVAL
    eval/base.cpp
    eval/deck.cpp
    eval/eval_interval.cpp
    eval/eval_jacobian.cpp
    eval/eval_array.cpp
    eval/eval_deriv_array.cpp
    eval/eval_feature.cpp
    eval/tape.cpp
    eval/feature.cpp
)

set(SCRS_RENDER_DISCRETE
    render/discrete/heightmap.cpp
    render/discrete/voxels.cpp
)

set(SCRS_RENDER_BREP
    render/brep/contours.cpp
    render/brep/edge_tables.cpp
    render/brep/manifold_tables.cpp
    render/brep/mesh.cpp
    render/brep/neighbor_tables.cpp
    render/brep/progress.cpp
)

set(SCRS_RENDER_BREP_DC
    render/brep/dc/marching.cpp
    render/brep/dc/dc_contourer.cpp
    render/brep/dc/dc_mesher.cpp
    render/brep/dc/dc_neighbors2.cpp
    render/brep/dc/dc_neighbors3.cpp
    render/brep/dc/dc_worker_pool2.cpp
    render/brep/dc/dc_worker_pool3.cpp
    render/brep/dc/dc_tree2.cpp
    render/brep/dc/dc_tree3.cpp
    render/brep/dc/dc_xtree2.cpp
    render/brep/dc/dc_xtree3.cpp
    render/brep/dc/dc_object_pool2.cpp
    render/brep/dc/dc_object_pool3.cpp
)

set(SCRS_RENDER_BREP_HYBRID
    render/brep/hybrid/hybrid_debug.cpp
    render/brep/hybrid/hybrid_worker_pool2.cpp
    render/brep/hybrid/hybrid_worker_pool3.cpp
    render/brep/hybrid/hybrid_neighbors2.cpp
    render/brep/hybrid/hybrid_neighbors3.cpp
    render/brep/hybrid/hybrid_tree2.cpp
    render/brep/hybrid/hybrid_tree3.cpp
    render/brep/hybrid/hybrid_xtree2.cpp
    render/brep/hybrid/hybrid_xtree3.cpp
    render/brep/hybrid/hybrid_object_pool2.cpp
    render/brep/hybrid/hybrid_object_pool3.cpp
    render/brep/hybrid/hybrid_mesher.cpp
)

set(SCRS_RENDER_BREP_SIMPLEX
    render/brep/simplex/simplex_debug.cpp
    render/brep/simplex/simplex_neighbors2.cpp
    render/brep/simplex/simplex_neighbors3.cpp
    render/brep/simplex/simplex_worker_pool2.cpp
    render/brep/simplex/simplex_worker_pool3.cpp
    render/brep/simplex/simplex_tree2.cpp
    render/brep/simplex/simplex_tree3.cpp
    render/brep/simplex/simplex_xtree2.cpp
    render/brep/simplex/simplex_xtree3.cpp
    render/brep/simplex/simplex_object_pool2.cpp
    render/brep/simplex/simplex_object_pool3.cpp
    render/brep/simplex/simplex_mesher.cpp
)

set(SCRS_RENDER_BREP_VOL
    render/brep/vol/vol_neighbors.cpp
    render/brep/vol/vol_object_pool.cpp
    render/brep/vol/vol_tree.cpp
    render/brep/vol/vol_worker_pool.cpp
)

set(SCRS_SOLVE
    solve/solver.cpp
)

set(SCRS_TREE
    tree/opcode.cpp
    tree/archive.cpp
    tree/data.cpp
    tree/deserializer.cpp
    tree/serializer.cpp
    tree/tree.cpp
    tree/operations.cpp
)

set(SCRS_ORACLE
    oracle/oracle_clause.cpp
    oracle/transformed_oracle.cpp
    oracle/transformed_oracle_clause.cpp
)

set(SCRS
    libfive.cpp
)

set(HDRS
  ../include/libfive.h
  )
  
set(HDRS_EVAL
  ../include/libfive/eval/base.hpp
  ../include/libfive/eval/clause.hpp
  ../include/libfive/eval/deck.hpp
  ../include/libfive/eval/eval_array.hpp
  ../include/libfive/eval/eval_array_size.hpp
  ../include/libfive/eval/eval_deriv_array.hpp
  ../include/libfive/eval/eval_feature.hpp
  ../include/libfive/eval/eval_interval.hpp
  ../include/libfive/eval/eval_jacobian.hpp
  ../include/libfive/eval/evaluator.hpp
  ../include/libfive/eval/feature.hpp
  ../include/libfive/eval/interval.hpp
  ../include/libfive/eval/tape.hpp
)

set(HDRS_ORACLE
../include/libfive/oracle/oracle.hpp
../include/libfive/oracle/oracle_clause.hpp
../include/libfive/oracle/oracle_context.hpp
../include/libfive/oracle/oracle_storage.hpp
../include/libfive/oracle/transformed_oracle.hpp
../include/libfive/oracle/transformed_oracle_clause.hpp
)

set(HDRS_RENDER
../include/libfive/render/axes.hpp
)

set(HDRS_RENDER_BREP_DC
../include/libfive/render/brep/dc/dc_contourer.hpp
../include/libfive/render/brep/dc/dc_flags.hpp
../include/libfive/render/brep/dc/dc_mesher.hpp
../include/libfive/render/brep/dc/dc_neighbors.hpp
../include/libfive/render/brep/dc/dc_tree.hpp
../include/libfive/render/brep/dc/dc_worker_pool.hpp
../include/libfive/render/brep/dc/intersection.hpp
../include/libfive/render/brep/dc/marching.hpp
)

set(HDRS_RENDER_BREP_HYBRID
../include/libfive/render/brep/hybrid/hybrid_debug.hpp
../include/libfive/render/brep/hybrid/hybrid_mesher.hpp
../include/libfive/render/brep/hybrid/hybrid_neighbors.hpp
../include/libfive/render/brep/hybrid/hybrid_tree.hpp
../include/libfive/render/brep/hybrid/hybrid_worker_pool.hpp
)

set(HDRS_RENDER_BREP_SIMPLEX
../include/libfive/render/brep/simplex/qef.hpp
../include/libfive/render/brep/simplex/simplex_debug.hpp
../include/libfive/render/brep/simplex/simplex_mesher.hpp
../include/libfive/render/brep/simplex/simplex_neighbors.hpp
../include/libfive/render/brep/simplex/simplex_tree.hpp
../include/libfive/render/brep/simplex/simplex_worker_pool.hpp
../include/libfive/render/brep/simplex/surface_edge_map.hpp
)

set(HDRS_RENDER_BREP_VOL
../include/libfive/render/brep/vol/vol_neighbors.hpp
../include/libfive/render/brep/vol/vol_tree.hpp
../include/libfive/render/brep/vol/vol_worker_pool.hpp
)

set(HDRS_RENDER_BREP
../include/libfive/render/brep/brep.hpp
../include/libfive/render/brep/contours.hpp
../include/libfive/render/brep/default_new_delete.hpp
../include/libfive/render/brep/dual.hpp
../include/libfive/render/brep/edge_tables.hpp
../include/libfive/render/brep/free_thread_handler.hpp
../include/libfive/render/brep/indexes.hpp
../include/libfive/render/brep/manifold_tables.hpp
../include/libfive/render/brep/mesh.hpp
../include/libfive/render/brep/neighbor_tables.hpp
../include/libfive/render/brep/neighbors.hpp
../include/libfive/render/brep/object_pool.hpp
../include/libfive/render/brep/per_thread_brep.hpp
../include/libfive/render/brep/progress.hpp
../include/libfive/render/brep/region.hpp
../include/libfive/render/brep/root.hpp
../include/libfive/render/brep/settings.hpp
../include/libfive/render/brep/util.hpp
../include/libfive/render/brep/worker_pool.hpp
../include/libfive/render/brep/xtree.hpp
)

set(HDRS_RENDER_DISCRETE
../include/libfive/render/discrete/heightmap.hpp
../include/libfive/render/discrete/voxels.hpp
)

set(HDRS_SOLVE
../include/libfive/solve/solver.hpp
)

set(HDRS_TREE
../include/libfive/tree/archive.hpp
../include/libfive/tree/data.hpp
../include/libfive/tree/deserializer.hpp
../include/libfive/tree/key.hpp
../include/libfive/tree/opcode.hpp
../include/libfive/tree/operations.hpp
../include/libfive/tree/serializer.hpp
../include/libfive/tree/tree.hpp
)

add_library(libfive SHARED
    ${SRCS} ${SRCS_EVAL} ${SCRS_RENDER_DISCRETE} ${SCRS_RENDER_BREP} ${SCRS_RENDER_BREP_DC} 
    ${SCRS_RENDER_BREP_HYBRID} ${SCRS_RENDER_BREP_SIMPLEX} ${SCRS_RENDER_BREP_VOL}
    ${SCRS_SOLVE} ${SCRS_TREE} ${SCRS_ORACLE}
    ${HDRS} ${HDRS_EVAL} ${HDRS_ORACLE} ${HDRS_RENDER} ${HDRS_RENDER_BREP_DC} ${HDRS_RENDER_BREP_HYBRID}
    ${HDRS_RENDER_BREP_SIMPLEX} ${HDRS_RENDER_BREP_VOL} ${HDRS_RENDER_BREP} ${HDRS_RENDER_DISCRETE}
    ${HDRS_SOLVE} ${HDRS_TREE}
)

#set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#set_source_files_properties(${SRCS_EVAL} PROPERTIES FOLDER eval)

################################################################################
# Attach the Git revision to libfive.cpp
execute_process(COMMAND git log --pretty=format:'%h' -n 1
                OUTPUT_VARIABLE GIT_REV
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                ERROR_QUIET)

# Check whether we got any revision (which isn't always the case, e.g.
# when someone downloaded a zip file from Github instead of a checkout)
if ("${GIT_REV}" STREQUAL "")
    set(GIT_REV "N/A")
    set(GIT_DIFF "")
    set(GIT_TAG "N/A")
    set(GIT_BRANCH "N/A")
else()
    execute_process(COMMAND bash -c "git diff --quiet --exit-code || echo +"
                    OUTPUT_VARIABLE GIT_DIFF
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    execute_process(COMMAND git describe --exact-match --tags
                    OUTPUT_VARIABLE GIT_TAG
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                    ERROR_QUIET)
    execute_process(COMMAND git rev-parse --abbrev-ref HEAD
                    OUTPUT_VARIABLE GIT_BRANCH
                    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

    string(STRIP "${GIT_REV}" GIT_REV)
    string(SUBSTRING "${GIT_REV}" 1 7 GIT_REV)
    string(STRIP "${GIT_DIFF}" GIT_DIFF)
    string(FIND "${GIT_DIFF}" "https://aka.ms/wslstore" INVALID_DIFF)
    if (INVALID_DIFF GREATER_EQUAL 0)
        set(GIT_DIFF "")
    endif()
    string(STRIP "${GIT_TAG}" GIT_TAG)
    string(STRIP "${GIT_BRANCH}" GIT_BRANCH)
endif()

set_property(
    SOURCE libfive.cpp
    APPEND PROPERTY COMPILE_DEFINITIONS
    GIT_TAG="${GIT_TAG}"
    GIT_REV="${GIT_REV}${GIT_DIFF}"
    GIT_BRANCH="${GIT_BRANCH}"
)

################################################################################
# Produce a library named 'libfive' on all platforms
set_target_properties(libfive PROPERTIES PREFIX "")

target_include_directories(libfive SYSTEM PUBLIC
    ${PNG_INCLUDE_DIR}
    ${EIGEN_INCLUDE_DIRS}
)
target_include_directories(libfive PUBLIC
    ../include
)

set(LIBS ${PNG_LIBRARIES})

if(UNIX AND NOT(APPLE))
    set(LIBS ${LIBS} ${CMAKE_THREAD_LIBS_INIT})
endif(UNIX AND NOT(APPLE))

if (UNIX)
    install(TARGETS libfive DESTINATION ${CMAKE_INSTALL_LIBDIR})
    install(FILES ../include/libfive.h DESTINATION include)
    install(DIRECTORY ../include/libfive DESTINATION include
            FILES_MATCHING PATTERN "*.hpp")
endif(UNIX)

target_link_libraries(libfive ${LIBS})
