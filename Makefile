# Librerías
LIBFT = libft/libft.a

# Flags
INC = -lreadline -lhistory
#LFLAGS = -L /home/achacon-/.brew/Cellar/readline/8.2.13/lib -lreadline -lncurses
CFLAGS = -Wall -Werror -Wextra
COMPILE = -g

# Colors
GREEN = \033[0;32m
YELLOW = \033[0;93m
FYELLOW = \033[38;5;154m
BLUE = \033[0;96m
PURPLE = \033[0;95m
PINK = \033[0;91m
RED = \033[0;31m
END = \033[0m

# Minishell
NAME = minishell
SRC = $(wildcard src/*.c)
OBJ_DIR = obj
OBJT = $(SRC:src/%.c=$(OBJ_DIR)/%.o)

# Compilation Rules
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	@gcc ${CFLAGS} ${INC} -c $< -o $@

all: $(NAME)

$(NAME): ${OBJT}
	@echo "$(YELLOW)Compiling Libft.$(END)"
	@make bonus -C libft
	@echo "$(GREEN)Libft Compiled.$(END)"
	@echo "$(YELLOW)Compiling Minishell.$(END)"
	@gcc ${CFLAGS} ${OBJT} ${INC} ${LIBFT} -o ${NAME}
	@echo "$(GREEN)Minishell Compiled.$(END)"

debug: $(LIBFT)
	@gcc src/*.c $(LIBFT) $(LFLAGS) $(INC) -o paco -g

$(LIBFT):
	@make bonus -c libft

clean:
	@rm -rf ${OBJ_DIR}
	@make clean -s -C libft
	@echo "$(RED)Compiled objects have been removed.$(END)"

fclean: clean
	@rm -f ${NAME}
	@make fclean -s -C libft
	@echo "$(RED)Executables objects have been removed.$(END)"

re: fclean all

norminette:
	@echo "$(YELLOW)Norminette libft.$(END)"
	@norminette ./libft
	@echo "$(YELLOW)Norminette minishell.$(END)"
	@norminette ./src

.PHONY: norminette clean fclean debug re all