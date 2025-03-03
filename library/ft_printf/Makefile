NAME = libftprintf.a
CC = cc
FLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRCS =	ft_print_c.c\
		ft_print_s.c\
		ft_print_d_i.c\
		ft_print_u.c\
		ft_print_x.c\
		ft_print_p.c\
		ft_printf.c\

OBJS = $(SRCS:.c=.o)

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)
	
.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
