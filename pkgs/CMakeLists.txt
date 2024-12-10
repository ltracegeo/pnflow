include(ExternalProject)
# ExternalProject_Add(hyprePar
#     DOWNLOAD_COMMAND ""
#     SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hypre/src
#     CMAKE_ARGS (
#         -DHYPRE_WITH_OPENMP=ON
#         -DHYPRE_WITH_MPI=OFF
#         -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
#         -DBUILD_SHARED_LIBS=False
#         -DCMAKE_TOOLCHAIN_FILE=${PROJECT_SOURCE_DIR}/src/script/toolchain.exe.txt
#     )
# )
ExternalProject_Add(hypreSeq
    DOWNLOAD_COMMAND ""
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/hypre/src
    CMAKE_ARGS(
        -DHYPRE_WITH_MPI=OFF
        -DHYPRE_SEQUENTIAL=ON
        -DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}
        -DBUILD_SHARED_LIBS=False
        -DCMAKE_TOOLCHAIN_FILE=${PROJECT_SOURCE_DIR}/src/script/toolchain${OPT}.txt
        -DCMAKE_POSITION_INDEPENDENT_CODE:BOOL=true
        -DCMAKE_C_COMPILER_WORKS=True
        -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}
    )
)
