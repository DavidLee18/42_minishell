CC := cc
CFLAGS := -Wall -Werror -Wextra -O2 -foptimize-sibling-calls
NAME := libft

SRCS			:=	ft_isalnum.c ft_isprint.c ft_memcmp.c ft_putchar_fd.c gc_split.c \
					ft_strlcat.c ft_strncmp.c gc_substr.c ft_atoi.c ft_isalpha.c \
					gc_itoa.c ft_memcpy.c ft_putendl_fd.c ft_strchr.c ft_strlcpy.c \
					ft_strnstr.c ft_tolower.c ft_bzero.c ft_isascii.c ft_striteri.c \
					ft_memmove.c ft_putnbr_fd.c gc_strdup.c ft_strlen.c ft_strrchr.c \
					ft_toupper.c ft_calloc.c ft_isdigit.c ft_memchr.c ft_memset.c  \
					ft_putstr_fd.c gc_strjoin.c gc_strmapi.c gc_strtrim.c \
					gc_getline.c ft_strcmp.c \
					gc.c gc2.c stack.c stack2.c stack3.c
OBJS			:= $(SRCS:.c=.o)

BONUS			:=	ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c \
					ft_lstdelone.c ft_lstiter.c ft_lstlast.c \
					ft_lstmap.c ft_lstnew.c ft_lstsize.c
BONUS_OBJS		:= $(BONUS:.c=.o)


all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME).a $(OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean:	clean
	rm -f $(NAME).a

re:	fclean $(NAME)

bonus:	$(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME).a $(OBJS) $(BONUS_OBJS)

.PNONY: all clean fclean re bonus
