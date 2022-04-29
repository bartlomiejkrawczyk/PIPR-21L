include_directories(value)
add_library(value value/value.cpp value/value_visitor.cpp)

include_directories(stack_machine)
add_library(stack_machine stack_machine/stack_machine.cpp stack_machine/operations.cpp)

target_link_libraries(stack_machine value)