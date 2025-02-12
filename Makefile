NAME = gnl.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror -g

SRC = get_next_line.c \
	get_next_line_utils.c

SRC_BONUS = get_next_line_bonus.c \
	get_next_line_utils_bonus.c

OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_BONUS = $(addprefix $(OBJ_DIR)/, $(SRC_BONUS:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	@ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

bonus: $(OBJ) $(OBJ_BONUS)
	@ar rcs $(NAME) $(OBJ) $(OBJ_BONUS)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
