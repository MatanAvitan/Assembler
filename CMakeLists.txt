cmake_minimum_required(VERSION 3.15)
project(final_project C)

set(CMAKE_C_STANDARD 90)

add_executable(final_project main.c input.c parsed_command.h input.h parsed_command.c validator.h validator.c consts.h addressing/instant_addressing.c addressing/instant_addressing.h bits_command.c bits_command.h command_router.c command_router.h addressing/direct_addressing.c addressing/direct_addressing.h addressing/indirect_register_addressing.c addressing/indirect_register_addressing.h addressing/direct_register_addressing.c addressing/direct_register_addressing.h utils.c utils.h addressing/addressing_utils.c addressing/addressing_utils.h file_handler.c file_handler.h parsed_instruction.c parsed_instruction.h instruction_router.c instruction_router.h)