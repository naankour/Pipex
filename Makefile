NAME = pipex
CC = cc
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
RM = rm -rf
LIBFT = library/libft/libft.a
LIBFT_FLAGS = -L./library/libft -lft

SRCS =	pipex.c\
		free.c\
		pipex_bonus.c\

OBJS = $(SRCS:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)

$(LIBFT):
	make -C library/libft

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)
	@make -s -C library/libft clean

fclean: clean
	$(RM) $(NAME)
	@make -s -C library/libft fclean

re: fclean all

.PHONY: all clean fclean re