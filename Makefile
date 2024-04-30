# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -Ilibft

# Header file
HEADER = push_swap.h

# Source files for the mandatory part
SRC = push_swap.c stack_functions.c validate.c sort.c rotate_sort.c is_sorted.c find_best_move.c push.c rotate.c swap.c reverse_rotate.c find_best_move_b_utils.c perform_best_move.c

# Name of the executable
NAME = push_swap

# Subfolder for object files
OBJDIR = obj/

# Object files for the mandatory part
#OBJS = $(addprefix $(OBJDIR),$(notdir $(SRC:.c=.o)))
OBJS = $(patsubst %.c,$(OBJDIR)%.o,$(SRC))

# Rule for creating the library
all: $(NAME)

$(NAME): $(OBJS)
	make bonus -C libft
	$(CC) $(CFLAGS) $(OBJS) libft/libft.a -o $(NAME)
#	mkdir -p $(OBJDIR)
#	cd $(OBJDIR) && ar -x ../libft/libft.a
#	ar rcs $(NAME) $(OBJS) $(OBJDIR)/*.o

$(OBJDIR)%.o: %.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C libft
	rm -f $(OBJS)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
