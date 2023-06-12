file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

list(REMOVE_ITEM SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/InOutCNM.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/FlowData.cpp
)

add_executable(pnflow ${SRC_FILES})

add_dependencies(pnflow
    hypreSeq
)

set_target_properties(pnflow PROPERTIES
    CXX_STANDARD 17
)

execute_process(
    COMMAND bash -c "date +'%Y.%m.%d'"
    OUTPUT_VARIABLE RELEASE_DATE
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
target_compile_definitions(pnflow PRIVATE RELEASE_DATE=\"${RELEASE_DATE}\")

target_include_directories(pnflow
    PRIVATE ${PROJECT_SOURCE_DIR}/pkgs/hypre/src/hypre/include
    PRIVATE ${PROJECT_SOURCE_DIR}/src/include
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/polygon
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/psPrc
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/psPrc
)

target_link_libraries(pnflow
    PRIVATE -static-libstdc++
    PRIVATE -static-libgcc
    PRIVATE stdc++fs
    ${CMAKE_BINARY_DIR}/pkgs/hypreSeq-prefix/src/hypreSeq-build/libHYPRE.a
)
