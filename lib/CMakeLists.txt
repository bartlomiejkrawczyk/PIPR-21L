include_directories(value)
add_library(value value/value.cpp value/value_visitor.cpp)

include_directories(stack_machine)
add_library(stack_machine stack_machine/stack_machine.cpp stack_machine/operations.cpp)

target_link_libraries(stack_machine value)

include_directories(command)
add_library(command command/command.cpp)

include_directories(memory)
add_library(memory memory/memory.cpp)

include_directories(program)
add_library(program program/program.cpp)

target_link_libraries(program stack_machine)
target_link_libraries(program memory)
target_link_libraries(program command)
