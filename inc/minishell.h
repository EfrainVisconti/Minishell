/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:05:03 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/07 17:39:03 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define FALSE 0
# define TRUE 1

# define OTHER 1
# define RED_FROM 2	//operator '<'
# define RED_TO 3	//operator '>'
# define HEREDOC 4	//operator '<<'
# define APPEND 5	//operator '>>'
# define PIPE 6		//operator '|'

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
	char		**tokens;
}					t_minishell;

//main.c
void	init_minishell(t_minishell *mini);
int		check_pipe_redir(char *input, int i, int sq, int dq);
void	handle_quotes(char c, int *qs, int *qd);

//free.c
void	free_main(t_minishell *mini);
void	free_array(char **array);
void	free_env(t_env *env);

//utils.c
void	print_error(int id);
int		ft_arraylen(char **array);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strcpy(char	*s1, char *s2);

//environment
void	set_env(char **env, t_minishell *mini);
t_env	*new_env_node(char *name, char *content);
void	set_bin_path(t_minishell *mini);
t_env	*find_env_var(t_env **env_var, char *name);

//add_spaces_tokenizer
char	*add_spaces_tokenizer(char *input, int i, int j, int len);
int		add_spaces_aux(char *input, char *result, int i, int j);

//quotes_tokenizer
char	**quotes_tokenizer(char *input);
char	**quotes_tokenizer_aux(char **tokens, char	*s, int start, int end);
int		count_tokens(char *s, int i, int tokens);

//expand_vars
char	**expand_vars(char **tokens, t_env *env);
char	*creates_new(char *token, t_env *env);
int		check_expand_needed(char *token, int *nbr);

//expand_vars_utils
char	*var_name_exp(char *s);
char	*from_beginning_to_dollar(char	*s);
char	*from_var_name_to_end(char *s);

//main_tokenizer
char	**set_tokens(t_minishell *mini, char *input);
void	remove_quotes_aux(char *s);
int		has_quotes(char	*str);
void	remove_quotes(char **tokens);
int		look_for_expansion(char **tokens);

//print_aux
void	print_aux(t_minishell *mini);

#endif