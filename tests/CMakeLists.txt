add_executable(mecha_core_tests
    core/application_tests.cpp
)

target_link_libraries(mecha_core_tests PRIVATE mecha_core mecha_warnings)

add_test(NAME mecha_core_tests COMMAND mecha_core_tests)
