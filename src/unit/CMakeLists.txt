set(UNIT_TESTS acceptance_test.h)

include_directories(CXXTEST_INCLUDE_DIR)

foreach (UNIT_TEST_SRC ${UNIT_TESTS})
    string(REPLACE ".h" "" UNIT_TEST_BASENAME ${UNIT_TEST_SRC})
    set(UNIT_TEST_RUNNER_SRC ${CMAKE_BINARY_DIR}/${UNIT_TEST_BASENAME}.cpp)
    add_executable(${UNIT_TEST_BASENAME} ${UNIT_TEST_RUNNER_SRC})
    target_link_libraries(${UNIT_TEST_BASENAME} setproctitle)
    set_target_properties(${UNIT_TEST_BASENAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/unit)
    add_custom_command(OUTPUT ${UNIT_TEST_RUNNER_SRC}
            COMMAND ${CXXTEST_PYTHON_TESTGEN_EXECUTABLE} --error-printer -o ${UNIT_TEST_RUNNER_SRC} ${UNIT_TEST_SRC}
                       WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
    add_test(NAME test_${UNIT_TEST_BASENAME}
             COMMAND ${UNIT_TEST_BASENAME})
endforeach(UNIT_TEST_SRC)

