# Download catch
Include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG origin/devel)
# cmake > 3.15 FetchContent_MakeAvailable(Catch2)
FetchContent_GetProperties(Catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(Catch2)
    add_subdirectory("${catch2_SOURCE_DIR}" "${catch2_BINARY_DIR}")
endif()

# Executable with tests

# Sanity Check
add_executable(sanity-tests sanity_tests.cpp)
target_link_libraries(sanity-tests Catch2::Catch2WithMain)

# Value
add_executable(value-tests value_tests.cpp)
target_link_libraries(value-tests value)
target_link_libraries(value-tests Catch2::Catch2WithMain)

# Stack Machine
add_executable(stack-machine-tests stack_machine_tests.cpp)
target_link_libraries(stack-machine-tests stack_machine)
target_link_libraries(stack-machine-tests Catch2::Catch2WithMain)

# Memory
add_executable(memory-tests memory_tests.cpp)
target_link_libraries(memory-tests memory)
target_link_libraries(memory-tests value)
target_link_libraries(memory-tests Catch2::Catch2WithMain)

# Program
add_executable(program-tests program_tests.cpp)
target_link_libraries(program-tests program)
target_link_libraries(program-tests Catch2::Catch2WithMain)

# Command
add_executable(command-tests command_tests.cpp)
target_link_libraries(command-tests command)
target_link_libraries(command-tests value)
target_link_libraries(command-tests program)
target_link_libraries(command-tests Catch2::Catch2WithMain)


# Debugger
add_executable(debugger-tests debugger_tests.cpp)
target_link_libraries(debugger-tests debugger)
target_link_libraries(debugger-tests Catch2::Catch2WithMain)


add_test(sanity-tests sanity-tests)
add_test(value-tests value-tests)
add_test(stack-machine-tests stack-machine-tests)
add_test(memory-tests memory-tests)
add_test(program-tests program-tests)
add_test(command-tests command-tests)
add_test(debugger-tests debugger-tests)