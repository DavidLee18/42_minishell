CC := cc
CFLAGS := -Wall -Werror -Wextra -g
NAME := minishell
BFLAGS := -Lft_printf -lftprintf -lreadline

BUILD_DIR := build
SRC_DIR := src

SRCS := src/builtin.c src/etc.c src/etc2.c src/interact.c \
	src/lex.c src/lex2.c src/main.c src/parse.c \
	src/parse2.c src/parse3.c src/process.c src/process2.c

OBJS := $(patsubst src/%.c, build/%.o, $(SRCS))


all: $(NAME)

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
