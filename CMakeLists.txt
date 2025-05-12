cmake_minimum_required(VERSION 3.31)
project(minishell)
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_FLAGS "-Wall -Wextra -Werror -g -I/opt/homebrew/opt/readline/include")
add_link_options("-L/opt/homebrew/opt/readline/lib")
add_subdirectory(ft_printf)
set(SOURCE_FILES
        src/builtin.c
        src/builtin2.c
        src/builtin3.c
        src/env.c
        src/etc.c
        src/etc2.c
        src/etc3.c
        src/interact.c
        src/interact2.c
        src/interact3.c
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
set(BONUS_SRCS
        src/bonus/builtin_bonus.c
        src/bonus/builtin2_bonus.c
        src/bonus/builtin3_bonus.c
        src/bonus/env_bonus.c
        src/bonus/etc_bonus.c
        src/bonus/etc2_bonus.c
        src/bonus/etc3_bonus.c
        src/bonus/interact_bonus.c
        src/bonus/interact2_bonus.c
        src/bonus/interact3_bonus.c
        src/bonus/lex_bonus.c
        src/bonus/lex2_bonus.c
        src/bonus/lex3_bonus.c
        src/bonus/main_bonus.c
        src/bonus/parse_bonus.c
        src/bonus/parse2_bonus.c
        src/bonus/parse3_bonus.c
        src/bonus/parse4_bonus.c
        src/bonus/phrase_bonus.c
        src/bonus/phrase2_bonus.c
        src/bonus/phrase3_bonus.c
        src/bonus/phrase4_bonus.c
        src/bonus/process_bonus.c
        src/bonus/process2_bonus.c
        src/bonus/process3_bonus.c
        src/bonus/process4_bonus.c
        src/bonus/process5_bonus.c
)

add_executable(minishell ${SOURCE_FILES})
target_link_libraries(minishell ft_printf)
target_link_libraries(minishell readline)
add_executable(minishell_bonus ${BONUS_SRCS})
target_link_libraries(minishell_bonus ft_printf)
target_link_libraries(minishell_bonus readline)
