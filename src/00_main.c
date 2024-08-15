/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/15 11:44:02 by eviscont         ###   ########.fr       */
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
void	init_minishell(t_minishell *mini)
{
	char	*input;

	while (1)
	{
		input = readline("minishell:");
		add_history(input);
		if (!ft_strcmp(input, "exit"))
		{
			ft_putstr_fd("exit\n", 2);
			free(input);
			break ;
		}
		mini->input = ft_strdup(input, 0);
		if (!ft_strcmp(input, "\"\"") || !ft_strcmp(input, "\'\'"))
		{
			print_error(7, NULL);//$? 127 TO DO
		}
		else if (check_pipe_redir(input, 0, 0, 0) == TRUE) //$? 2 TO DO
		{
			mini->tokens = set_tokens(mini, input);
			if (mini->tokens && mini->tokens[0])
			{
				if (set_execution_nodes(mini) == TRUE)
					execute_commands(mini);
			}
			//print_aux(mini);
			free_array(mini->tokens);
			free_nodes(mini->nodes);
		}
		free(input);
		free(mini->input);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	mini;

	if (argc > 1)
		return (1);
	(void)argv;
	ft_memset(&mini, 0, sizeof(mini));
	mini.argenv = env;
	set_env(env, &mini);
	set_bin_path(&mini);
	init_minishell(&mini);
	free_main(&mini);
	return (0);
}
