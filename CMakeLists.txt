cmake_minimum_required(VERSION 3.22)
project(coop C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_BUILD_TYPE Debug)
add_executable(coop main.c
        _main.c
        _main.h
        coop/exceptions/exception.h
        coop/exceptions/exception.h
        coop/memory_management/allocator.c
        coop/memory_management/allocator.h
        coop/data_structures/node.c
        coop/data_structures/node.h
        coop/data_structures/linked_list.c
        coop/data_structures/linked_list.h
        coop/logging/logger.c
        coop/logging/logger.h
        coop/utils.h
        coop/utils.c
        coop/exceptions/exception.c
        coop/builtins.h
        coop/data_structures/interface_random_access.h
        coop/structs/optional.h
        coop/print.c
        coop/print.h
        coop/macros.h
        coop/structs/type.c
        coop/structs/type.h
        coop/structs/field.c
        coop/structs/field.h
        coop/structs/function.c
        coop/structs/function.h
        coop/structs/Object.c
        coop/structs/Object.h
)
