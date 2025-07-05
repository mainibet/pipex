CC = cc

CFLAGS = -Wall -Wextra -Werror -g

LIBFT_DIR = ./libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

NAME = pipex

SRC = pipex.c util_initial.c util_child.c util_exec.c util_other.c util_findpath.c util_parent.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

# Link object files and libft to create the executable
$(NAME): $(OBJ) $(LIBFT_LIB)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $@

# Rule to build libft if it doesn't exist
$(LIBFT_LIB): 
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

