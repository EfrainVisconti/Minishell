/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:14:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/25 19:24:28 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// checks there are not unclosed quotes
int	check_unclosed_quotes(char *args)
{
	int	i;
	int	oneq;
	int	twoq;

	i = 0;
	oneq = 0;
	twoq = 0;
	while (args[i])
	{
		if (args[i] == '\'')
			oneq++;
		else if (args[i] == '"')
			twoq++;
		i++;
	}
	if (twoq % 2 != 0 || oneq % 2 != 0)
		return (print_error(1), FALSE);
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
			break ;
		mini->input = ft_strdup(input);
		add_history(input);
		if (!ft_strcmp(input, "exit"))
		{
			ft_printf("exit\n");
			break ;
		}
		else if (!ft_strcmp(input, "\"\"") || !ft_strcmp(input, "\'\'"))
			ft_printf("Command '' not found\n"); //$? 127 TO DO
		else if (check_unclosed_quotes(mini->input))
			count_tokens(mini->input);
		free(mini->input);
	}
	free(input);
	free_program(mini);
	return (0);
}
