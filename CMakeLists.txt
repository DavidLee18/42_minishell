cmake_minimum_required(VERSION 3.31)
project(minishell)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -g -I/opt/homebrew/opt/readline/include")
add_link_options("-L/opt/homebrew/opt/readline/lib")
add_subdirectory(ft_printf)
set(SOURCE_FILES
        src/builtin.c
        src/builtin2.c
        src/etc.c
        src/etc2.c
        src/etc3.c
        src/interact.c
        src/interact2.c
        src/lex.c
        src/lex2.c
        src/main.c
        src/parse.c
        src/parse2.c
        src/parse3.c
        src/process.c
        src/process2.c
        src/process3.c
)

add_executable(minishell ${SOURCE_FILES})
target_link_libraries(minishell ft_printf)
target_link_libraries(minishell readline)
