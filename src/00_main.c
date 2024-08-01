/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/01 17:53:14 by eviscont         ###   ########.fr       */
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

//checks if there are wrong numbers of consecutive pipes or redirections
//but only without spaces
int	check_pipe_redir(char *s, int i, int sq, int dq)
{
	while (s[i] != '\0')
	{
		handle_quotes(s[i], &sq, &dq);
		if (s[i] == '|' && s[i + 1] == '|' && !dq && !sq)
			return (print_error(2), FALSE);
		else if (s[i] == '>' && (s[i + 1] == '<' || (s[i + 1] == '>'
					&& s[i + 2] == '>' && s[i + 3] != '>')) && !dq && !sq)
			return (print_error(3), FALSE);
		else if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<'
			&& s[i + 3] != '<' && !dq && !sq)
			return (print_error(4), FALSE);
		else if (s[i] == '>' && s[i + 1] == '>' && s[i + 2] == '>'
			&& s[i + 3] == '>' && !dq && !sq)
			return (print_error(5), FALSE);
		else if (s[i] == '<' && s[i + 1] == '<' && s[i + 2] == '<'
			&& s[i + 3] == '<' && !dq && !sq)
			return (print_error(6), FALSE);
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
		if (input == NULL)
			return ;
		mini->input = ft_strdup(input);
		add_history(input);
		if (!ft_strcmp(input, "exit"))
		{
			ft_putstr_fd("exit\n", 2);
			free(input);
			break ;
		}
		else if (!ft_strcmp(input, "\"\"") || !ft_strcmp(input, "\'\'"))
			print_error(7); //$? 127 TO DO
		else if (!check_pipe_redir(mini->input, 0, 0, 0)) //$? 2 TO DO
			break ;
		// 	mini->tokens = main_tokenizer(mini);
		// if (mini->tokens != NULL)
		free(mini->input);
		free(input);
		print_aux(mini);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	mini;

	if (argc > 1)
		return (1);
	(void)argv;
	mini.env = NULL;
	mini.bin_path = NULL;
	mini.input = NULL;
	mini.tokens = NULL;
	set_env(env, &mini);
	set_bin_path(&mini);
	init_minishell(&mini);
	free_main(&mini);
	return (0);
}
