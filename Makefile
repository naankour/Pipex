NAME = pipex
NAME_BONUS = pipex_bonus
CC = cc
FLAGS = -Wall -Wextra -g3 # -o -fsanitize=address
RM = rm -rf
LIBFT = library/libft/libft.a
LIBFT_FLAGS = -L./library/libft -lft

SRCS =	mandatory/error_free.c\
		mandatory/pipex.c\
		mandatory/file_utils.c\
		mandatory/parsing_path.c\
		mandatory/commands.c\

SRCS_BONUS = bonus/error_free_bonus.c\
			bonus/pipex_bonus.c\
			bonus/file_utils_bonus.c\
			bonus/parsing_path_bonus.c\
			bonus/commands_bonus.c\

OBJS_BONUS = $(SRCS_BONUS:.c=.o)
OBJS = $(SRCS:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(LIBFT_FLAGS)

$(NAME_BONUS): $(LIBFT) $(OBJS_BONUS)
	$(CC) $(FLAGS) -o $(NAME_BONUS) $(OBJS_BONUS) $(LIBFT_FLAGS)

$(LIBFT):
	make -C library/libft

bonus: $(NAME_BONUS)
		mv $(NAME_BONUS) $(NAME)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@make -s -C library/libft clean

fclean: clean
	$(RM) $(NAME) $(NAME_BONUS)
	@make -s -C library/libft fclean

re: fclean all

bonus_re: fclean bonus

.PHONY: all clean fclean re bonus bonus_re