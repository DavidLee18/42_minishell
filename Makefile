CC := cc
CFLAGS := -Wall -Werror -Wextra -O2 -foptimize-sibling-calls
NAME := minishell
BFLAGS := -Lft_printf -lftprintf
# BONUS_NAME := pipex_bonus

BUILD_DIR := build
SRC_DIR := src

SRCS := src/etc.c src/lex.c src/lex2.c
# BONUS_SRCS := src/main_bonus.c src/fd_cleaner.c \
#			src/path.c src/files_pipes_bonus.c \
#			src/getln_until_bonus.c

OBJS := $(patsubst src/%.c, build/%.o, $(SRCS))
# BONUS_OBJS := $(patsubst src/%.c,build/%.o,$(BONUS_SRCS))


all: $(NAME)

# bonus: $(BONUS_NAME)

$(NAME): $(OBJS)
	make -C ft_printf
	$(CC) $(OBJS) $(BFLAGS) -o $(NAME)

build/%.o: src/%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SRCS): $(SRC_DIR)/minishell.h

clean:
	rm -rf $(BUILD_DIR)
	make clean -C ft_printf

fclean:	clean
	rm -f $(NAME)
#	rm -f $(BONUS_NAME)
	make fclean -C ft_printf

# $(BONUS_NAME): $(BONUS_OBJS)
#	make -C ft_printf
#	$(CC) $(BONUS_OBJS) $(BFLAGS) -o $(BONUS_NAME)


# $(BONUS_OBJS): $(BONUS_SRCS)
#	$(CC) $(CFLAGS) -c $(patsubst build/%.o,src/%.c,$@)
#	mkdir -p build
#	mv $(patsubst build/%.o,%.o,$@) $@

re:	fclean all

.PNONY: all clean fclean re
