/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/30 21:25:03 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//handle quote status
void	handle_quotes(char c, int *sq, int *dq)
{
    if (c == '\'' && !(*dq))
        *sq = !(*sq);
	else if (c == '"' && !(*sq))
        *dq = !(*dq);
}

// checks if there are wrong numbers of pipes or redirections
int	check_pipe_redir(char *input)
{
	int	i;
	int	sq;
	int	dq;

	sq = 0;
	dq = 0;
	i = 0;
	while (input[i] != '\0')
	{
		handle_quotes(input[i], &sq, &dq);
		if (input[i] == '|' && input[i + 1] == '|' && !dq && !sq)
			return (print_error(2), FALSE);
		else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>' && !dq && !sq)
			return (print_error(3), FALSE);
		else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<' && !dq && !sq)
			return (print_error(4), FALSE);
		i++;
	}
	return (TRUE);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*mini;
	char		*input;

	if (argc > 1)
		return (1);
	(void)argv;
	mini = (t_minishell *)malloc(sizeof(t_minishell));
	if (!mini)
		return (1);
	mini->env = NULL;
	set_env(env, mini);
	set_bin_path(mini);
	while (1)
	{
		input = readline("minishell:");
		if (input == NULL)
			return (1) ;
		mini->input = ft_strdup(input);
		add_history(input);
		if (!ft_strcmp(input, "exit"))
		{
			ft_putstr_fd("exit\n", 2);
			break ;
		}
		else if (!ft_strcmp(input, "\"\"") || !ft_strcmp(input, "\'\'"))
			ft_putstr_fd("Command '' not found\n", 1); //$? 127 TO DO
		else if (check_pipe_redir(mini->input)) //$? 2 TO DO
			mini->tokens = main_tokenizer(mini);
		if (mini->tokens != NULL)
			print_aux(mini);
		free(mini->input);
	}
	free_program(mini);
	return (0);
}
