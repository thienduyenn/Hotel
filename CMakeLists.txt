cmake_minimum_required(VERSION 3.28)
project(FileUtilsV2 C)

set(CMAKE_C_STANDARD 11)

add_executable(FileUtilsV2 main.c
        src/core/User.database.c
        src/core/User.database.h
        System.c
        System.h
        src/cli/UserCommand.c
        src/cli/UserCommand.h
        src/core/Order.database.c
        src/core/Order.database.h
        src/utils/CheckToken.c
        src/utils/CheckToken.h
        src/core/Admin.database.c
        src/core/Admin.database.h
        src/core/Staff.database.c
        src/core/Staff.database.h
        src/core/entity/staff.h
        src/core/entity/admin.h

)
