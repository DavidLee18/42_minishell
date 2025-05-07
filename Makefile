CC := cc
CFLAGS := -Wall -Werror -Wextra -O2 -foptimize-sibling-calls
DEBUG_CFLAGS := -Wall -Werror -Wextra -g #-fsanitize=address -O1 -fno-omit-frame-pointer
NAME := minishell
BFLAGS := -Lft_printf -lftprintf -lreadline
DEBUG_BFLAGS := -Lft_printf -lftprintf -lreadline -g #-fsanitize=address -O1 -fno-omit-frame-pointer

BUILD_DIR := build
SRC_DIR := src

SRCS := src/builtin.c src/builtin2.c src/builtin3.c src/env.c \
	src/etc.c src/etc2.c src/etc3.c src/interact.c \
	src/interact2.c src/interact3.c src/lex.c src/lex2.c \
	src/main.c src/parse.c src/parse2.c src/parse3.c \
	src/process.c src/process2.c src/process3.c

OBJS := $(patsubst src/%.c, build/%.o, $(SRCS))

BONUS_SRCS := src/bonus/builtin_bonus.c \
	src/bonus/builtin2_bonus.c src/bonus/builtin3_bonus.c \
	src/bonus/env_bonus.c src/bonus/etc_bonus.c \
	src/bonus/etc2_bonus.c \
	src/bonus/interact_bonus.c src/bonus/interact2_bonus.c \
	src/bonus/interact3_bonus.c src/bonus/lex_bonus.c \
	src/bonus/lex2_bonus.c src/bonus/lex3_bonus.c \
	src/bonus/main_bonus.c src/bonus/parse_bonus.c \
	src/bonus/parse2_bonus.c src/bonus/parse3_bonus.c \
	src/bonus/parse4_bonus.c src/bonus/process_bonus.c \
	src/bonus/process2_bonus.c src/bonus/process3_bonus.c \
	src/bonus/process4_bonus.c src/bonus/phrase_bonus.c \
	src/bonus/phrase2_bonus.c src/bonus/phrase3_bonus.c

BONUS_OBJS := $(patsubst src/bonus/%.c, build/bonus/%.o, $(BONUS_SRCS))

all: $(NAME)

$(NAME): $(OBJS)
	make -C ft_printf
	$(CC) $(OBJS) $(DEBUG_BFLAGS) -o $(NAME)

build/%.o: src/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@

$(SRCS): $(SRC_DIR)/minishell.h

clean:
	rm -rf $(BUILD_DIR)
	make clean -C ft_printf

fclean:	clean
	rm -f $(NAME)
	make fclean -C ft_printf

bonus: $(BONUS_OBJS)
	make -C ft_printf
	$(CC) $(BONUS_OBJS) $(DEBUG_BFLAGS) -o $(NAME)

build/bonus/%.o: src/bonus/%.c
	mkdir -p $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/bonus
	$(CC) $(DEBUG_CFLAGS) -c $< -o $@

re:	fclean all

rebo: fclean bonus

.PNONY: all clean fclean re bonus rebo
