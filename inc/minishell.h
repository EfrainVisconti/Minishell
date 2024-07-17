/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:05:03 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/17 15:42:13 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include "../libs/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>

# define FALSE 0
# define TRUE 1

//linked list for enviroment variables
typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

//main struct for the program
typedef struct s_minishell
{
	t_env		*env;
	char		**bin_path;
	char		*input;
}					t_minishell;

//main.c
void	set_env(char **env, t_minishell *mini);
t_env	*new_env_node(char *name, char *content);
void	set_bin_path(t_minishell *mini);
t_env	*find_env_var(t_env **env_var, char *name);

//utils.c
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char	*s1, char *s2);

//free.c
void	free_program(t_minishell *mini);
void	free_array(char **array);
void	free_env(t_env *env);

#endif