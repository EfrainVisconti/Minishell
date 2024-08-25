/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/25 21:05:21 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_status = 0;

//handle quote status
void	handle_quotes(char c, int *sq, int *dq)
{
	if (c == '\'' && !(*dq))
		*sq = !(*sq);
	else if (c == '"' && !(*sq))
		*dq = !(*dq);
}

//checks if there are wrong numbers of consecutive pipes or redirections
//but only without spaces
int	check_pipe_redir(char *s, int i, int sq, int dq)
{
	while (s[i] != '\0')
	{
		handle_quotes(s[i], &sq, &dq);
		if (s[i] == '|' && s[i + 1] == '|' && !dq && !sq)
			return (print_error(2, NULL), FALSE);
		else if (s[i] == '>' && (s[i + 1] == '<' || (s[i + 1] == '>'
					&& s[i + 2] == '>' && s[i + 3] != '>')) && !dq && !sq)
			return (print_error(3, NULL), FALSE);
		else if (s[i] == '<' && (s[i + 1] == '>' || (s[i + 1] == '<'
					&& s[i + 2] == '<' && s[i + 3] != '<')) && !dq && !sq)
			return (print_error(4, NULL), FALSE);
		else if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>'
			&& s[i + 3] == '>' && !dq && !sq)
			return (print_error(5, NULL), FALSE);
		else if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<'
			&& s[i + 3] == '<' && !dq && !sq)
			return (print_error(6, NULL), FALSE);
		else if (s[i] == '<' && s[i + 1] == '|' && !dq && !sq)
			return (print_error(2, NULL), FALSE);
		else if (s[i] == '>' && s[i + 1] == '|' && !dq && !sq)
			return (print_error(2, NULL), FALSE);
		i++;
	}
	return (TRUE);
}

//minishell loop
void	init_minishell(t_minishell *mini, char *input)
{
	while (1)
	{
		mini->signal = FALSE;
		init_signals(&(mini->signal));
		set_bin_path(mini);
		input = readline("minishell:");
		add_history(input);
		mini->input = ft_strdup(input, 0);
		free(input);
		if (check_pipe_redir(mini->input, 0, 0, 0) == TRUE)
		{
			mini->tokens = set_tokens(mini, mini->input);
			if (mini->tokens && mini->tokens[0])
			{
				if (set_execution_nodes(mini) == TRUE)
				{
					execute_commands(mini);
					free_nodes(mini->nodes);
				}
			}
			free_array(mini->tokens);
		}
		free_array(mini->bin_path);
		free(mini->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	mini;
	char		*input;

	if (argc > 1)
		return (1);
	(void)argv;
	input = NULL;
	ft_memset(&mini, 0, sizeof(mini));
	mini.argenv = env;
	set_env(env, &mini);
	init_minishell(&mini, input);
	free_main(&mini);
	return (0);
}
