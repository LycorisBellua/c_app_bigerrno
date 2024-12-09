CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g# -fsanitize=address
LDFLAGS = -Llibft -lft -lncurses -lreadline -lhistory
RM = rm -f

NAME = bigerrno
SRC = main.c $(wildcard */*.c) $(wildcard */*/*.c)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT_BIN = $(LIBFT_DIR)/libft.a

all: $(LIBFT_BIN) $(NAME)

$(LIBFT_BIN):
	@$(MAKE) -C $(LIBFT_DIR) --silent

$(NAME): $(OBJ)
	@norminette | grep -v "OK" | grep -v "Error\!" | grep -v "INVALID_HEADER"
	@$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

animation:
	@bash animation.sh

clean:
	@$(RM) $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@$(RM) $(NAME) $(LIBFT_BIN)

re: fclean animation all

.PHONY: all clean fclean re animation
