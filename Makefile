# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 13:58:33 by eviscont          #+#    #+#              #
#    Updated: 2024/07/25 18:48:21 by eviscont         ###   ########.fr        #
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
CCFLAGS		=	-Wall -Wextra -Werror -lreadline #-fsanitize=leak

#Nombre ejecutable
NAME		=	minishell

#Ficheros
SRC_FILES	=	00_main 01_free 02_utils 03_environment 04_tokenizer
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