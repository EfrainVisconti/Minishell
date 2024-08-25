# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 13:58:33 by eviscont          #+#    #+#              #
#    Updated: 2024/08/25 21:01:13 by eviscont         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Definir colores
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No color (reiniciar)

#Comandos
DEL			=	rm -f
CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror -lreadline -g3 #-fsanitize=leak

#Nombre ejecutable
NAME		=	minishell

#Ficheros
SRC_FILES	=	00_main 01_free 02_utils 03_environment 06_quotes_tokenizer \
				07_expand_vars 04_main_tokenizer 05_add_spaces_tokenizer \
				08_expand_vars_utils 09_set_execution_nodes 11_set_full_cmd \
				12_set_full_path 13_set_infile_outfile 10_check_tokens \
				14_execute_commands 18_print_error 15_builtins 16_builtins \
				17_export 19_signals print_aux
SRC			=	$(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ			=	$(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
LIBFT		=	libs/libft

#Librerias
LIBS		= $(LIBFT)/libft.a

#Directorios
SRC_DIR = src/
OBJ_DIR = obj/

# REGLAS #
all: libft $(NAME)

#Compilar
$(NAME):$(OBJ)
		@$(CC) $(OBJ) $(LIBS) $(CCFLAGS) -o $(NAME)
		@echo "$(GREEN)MINISHELL HAS BEEN COMPILED!$(NC)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compiling: $<$(NC)"
	@$(CC) $(CCFLAGS) $(RLFLAGS) -o $@ -c $<
	@echo "$(YELLOW)Compiled!$(NC)"

#compilar librerias individuales
libft:
	@echo "$(YELLOW)COMPILING LIBFT...$(NC)"
	@make -C $(LIBFT)
	@echo "$(GREEN)LIBFT HAS BEEN COMPILED$(NC)"

# Eliminar tmp libft
fclean_libft:
	@make fclean -C $(LIBFT)
	@echo "$(RED)LIBFT FULL CLEANED!$(NC)"

# Eliminar temporales
clean:
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)OBJS AND DIRECTORY CLEANED!$(NC)"

# Eliminar temporales y ejecutable
fclean: clean fclean_libft
	@$(RM) $(NAME)
	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"

re: fclean all