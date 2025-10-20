CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g# -fsanitize=address
LDFLAGS = -Llibft -lft -lncurses -lreadline -lhistory
NAME = bigerrno
DIR_OBJ = build
SRC = $(shell find src -name '*.c')
OBJ = $(patsubst %.c, $(DIR_OBJ)/%.o, $(SRC))
LIBFT_DIR = libft
LIBFT_BIN = $(LIBFT_DIR)/libft.a

all: $(LIBFT_BIN) $(NAME)

$(LIBFT_BIN):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	@norminette | grep -v "Setting locale" | grep -v "OK" | grep -v "Error\!" \
		| grep -v "INVALID_HEADER"
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(DIR_OBJ)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
