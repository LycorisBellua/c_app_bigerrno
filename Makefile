CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude -g# -fsanitize=address
LDFLAGS = -Llibft -lft -lncurses -lreadline -lhistory
DBUG_FLAG = -DDBUG=1
RM = rm -f

NAME = bigerrno
SRC = main.c $(wildcard */*.c) $(wildcard */*/*.c)
OBJ = $(SRC:.c=.o)

LIBFT_DIR = libft
LIBFT_BIN = $(LIBFT_DIR)/libft.a

all: $(LIBFT_BIN) $(NAME)

debug_env: CFLAGS += $(DBUG_FLAG)

debug_env: re

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

fcklean: fclean

re: fclean animation all

.PHONY: all clean fclean re debug_env fcklean animation
