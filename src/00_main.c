/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/28 21:36:35 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// checks if there are wrong numbers of pipes or redirections
int	check_pipe_redir(char *input)
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '|' && input[i + 1] == '|')
			return (print_error(2), FALSE);
		else if (input[i] == '>' && input[i + 1] == '>' && input[i + 2] == '>')
			return (print_error(3), FALSE);
		else if (input[i] == '<' && input[i + 1] == '<' && input[i + 2] == '<')
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
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		else if (!ft_strcmp(input, "\"\"") || !ft_strcmp(input, "\'\'"))
			ft_putstr_fd("Command '' not found\n", 1); //$? 127 TO DO
		else if (check_pipe_redir(mini->input)) //$? 2 TO DO
		{
			if (!quotes_tokenizer(add_spaces_tokenizer(mini->input, 0, 0, ft_strlen(mini->input))))
				print_error(1);
		}
		//print_aux(mini);
		free(mini->input);
	}
	free_program(mini);
	return (0);
}
