/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:05:03 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/27 21:31:21 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include "../libs/libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <signal.h>

# define FALSE 0
# define TRUE 1
# define ERROR -1

# define READ 0
# define WRITE 1

//linked list for enviroment variables
typedef struct s_env
{
	char			*name;
	char			*content;
	int				is_env;
	int				is_exp;
	int				is_pri;
	struct s_env	*next;
}					t_env;

//struct for nodes resulting from separation by pipes
typedef struct s_node
{
	char	**full_cmd;
	char	*full_path;
	int		infile;
	int		outfile;
	int		is_exec;
	pid_t	n_pid;
}			t_node;

//main struct for the program
typedef struct s_minishell
{
	t_env		*env;
	char		**argenv;
	char		**bin_path;
	char		*input;
	char		**tokens;
	t_node		**nodes;
	int			nbr_nodes;
	int			signal;
}					t_minishell;

//main.c
void	init_minishell(t_minishell *mini, char *input);
int		check_pipe_redir(char *input, int i, int sq, int dq);
void	handle_quotes(char c, int *qs, int *qd);

//free.c
void	free_main(t_minishell *mini);
void	free_array(char **array);
void	free_env(t_env *env);
void	free_nodes(t_node **nodes);

//utils.c
char	*ft_herejoin(char const *s1, char const *s2);
char	*ft_strcpy(char	*s1, char *s2);
int		ft_strcmp(char *s1, char *s2);
int		ft_arraylen(char **array);

//environment
void	set_env(char **env, t_minishell *mini);
t_env	*new_env_node(char *name, char *content, int env, int exp);
void	set_bin_path(t_minishell *mini);
t_env	*find_env_var(t_env **env_var, char *name);

//main_tokenizer
char	**set_tokens(t_minishell *mini, char *input);
int		look_for_expansion(char **tokens);
void	remove_quotes(char **tokens);
int		has_quotes(char	*str);
void	remove_quotes_aux(char *s);

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
char	*creates_new_aux(char *token, t_env *env, t_env *var, int *nbr);
int		check_expand_needed(char *token, int *nbr);

//expand_vars_utils
char	*var_name_exp(char *s);
char	*from_beginning_to_dollar(char	*s);
char	*from_var_name_to_end(char *s);

//set_execution_nodes
int		set_execution_nodes(t_minishell *mini);
t_node	**create_exec_nodes(t_minishell *mini, int nbr);
t_node	*create_exec_nodes_aux(t_minishell *mini, char **tokens);
char	**get_next_node(char **tmp, char ***next);

//check_tokens
int		pipes_handler(char **tokens);
int		check_wrong_redir(char **tok);

//set_full_cmd
char	**set_full_cmd(char **tokens, int i, int cmd);
int		count_cmd(char **tokens);
int		is_redirection(char *s);

//set_full_path
char	*set_full_path(t_node *n, char **bin_path);
int		is_builtin(char *s);

//set_infile_outfile
int		set_infile_outfile(t_node *node, char **tok, int out_fd, int in_fd);
int		third_case_aux(char **tok, int *in_fd, int i);
int		second_case_aux(char **tok, int *out_fd, int i);
int		first_case_aux(char **tok, int *out_fd, int i);
void	check_heredoc(char *limit, int *in_fd);

//excute_commands
void	execute_commands(t_minishell *mini);
void	execute_simple_command(t_minishell *mini, t_node *node, pid_t pid);
void	excecute_pipe_sequence(t_minishell *mini, int pipefd[2]);
void	child_process(t_minishell *m, t_node *node, int aux[2], int pfd[2]);
void	child_execution(t_minishell *min, t_node *node, int aux);

//builtins
void	execute_builtin(char *s, t_minishell *mini, int i);
int		ft_cd(t_minishell *mini, t_node *node, char *cwd, char *dir);
void	cd_to_dir(t_node *node, char **dir, t_env *old);
void	cd_to_home(t_minishell *mini, char **dir, t_env *old, t_env *pwd);
void	ft_unset(t_minishell *mini, t_node *node, int len);
void	ft_pwd(int fd);
int		ft_env(t_minishell *mini, t_node *node, int len, int fd);
int		ft_exit(t_minishell *mini, t_node *node);
int		is_numeric(char *str);
void	ft_echo(t_node *node, int fd);
void	ft_echo_aux(t_node *node, int fd, int i, int len);

//export
int		ft_export(t_minishell *mini, t_node *node, int fd);
void	export_add_node(t_env *env, char *name, char *content, int mode);
void	simple_export(t_env **env, int fd);
void	simple_export_aux(t_env **cur_name, t_env **env, int *size, int fd);

//print_error
void	print_error(int id, char *s);
void	print_error2(int id, char *s);
void	print_error3(int id, char *s);

//signals
void	init_signals(int *signal_comand);

//exit_status
void	set_exit_status(t_minishell *mini);
void	update_exit_status(t_minishell *mini);

//heredoc
int		get_here_doc(char *str[2], char *aux[2]);
char	*get_here_str(char *str[2], int len, char *limit, char *warn);

// print_aux
// void	print_aux(t_minishell *mini);

extern int	g_status;

#endif