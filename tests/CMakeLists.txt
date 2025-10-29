add_executable(tests 02_algebra_test.c ${PROJECT_SOURCE_DIR}/src/math/02_algebra/algebra.c)

target_include_directories(tests PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(tests PRIVATE criterion m)

add_test(NAME AlgebraTests COMMAND tests)
