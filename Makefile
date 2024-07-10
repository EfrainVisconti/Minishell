# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/10 13:58:33 by eviscont          #+#    #+#              #
#    Updated: 2024/07/10 17:51:19 by eviscont         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# # Definir colores
# RED = \033[0;31m
# GREEN = \033[0;32m
# YELLOW = \033[0;33m
# NC = \033[0m

# # Comandos
# CFLAGS = -Wall -Wextra -Werror

# # Nombre ejecutable
# NAME = minishell

# # Ficheros
# SRC_FILES = 00_main
# SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
# OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
# LIBFT = libs/libft
# HEADER = inc/minishell.h

# # Librerias
# LIBS = $(LIBFT)/libft.a

# # Directorios
# SRC_DIR = src/
# OBJ_DIR = obj/

# # Reglas
# all: libs $(NAME)

# # Compilar
# $(NAME): $(OBJ)
# 	@gcc $(CFLAGS) $(OBJ) $(LIBS) -o $(NAME)
# 	@echo "$(GREEN)MINISHELL HAS BEEN COMPILED$(NC)"

# $(OBJ_DIR)%.o: $(SRC_DIR)%.c
# 	@mkdir -p $(OBJ_DIR)
# 	@echo "$(YELLOW)Compiling...$<$(NC)"
# 	@gcc $(CFLAGS) -o $@ -c $<

# libs:
# 	@echo "$(YELLOW)COMPILING LIBFT...$(NC)"
# 	@make -C $(LIBFT)
# 	@echo "$(GREEN)LIBFT HAS BEEN COMPILED$(NC)"

# # Eliminar temporales
# clean:
# 	@make clean -C $(LIBFT)
# 	@rm -f -r $(OBJ_DIR)
# 	@echo "$(RED)OBJECTS CLEANED!$(NC)"

# fclean: clean
# 	@rm -f $(NAME) $(LIBS)
# 	@echo "$(RED)EXECUTABLE CLEANED!$(NC)"

# re: fclean all

# Definir colores
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m # No color (reiniciar)

#Comandos
DEL			=	rm -f
CC			=	gcc
CCFLAGS		=	-Wall -Wextra -Werror

#Nombre ejecutable
NAME		=	minishell

#Ficheros
SRC_FILES	=	00_main
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