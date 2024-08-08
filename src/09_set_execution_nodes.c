/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_set_execution_nodes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:32:48 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/08 14:26:22 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_pipes(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i] != NULL)
	{
		if (!ft_strcmp(tokens[i], "|"))
		{
			count++;
			if (i == 0 || tokens[i + 1] == NULL || \
				!ft_strcmp(tokens[i - 1], "<") || \
				!ft_strcmp(tokens[i - 1], "<<") || \
				!ft_strcmp(tokens[i - 1], ">") || \
				!ft_strcmp(tokens[i - 1], ">>") || \
				!ft_strcmp(tokens[i - 1], "|"))
				return (ERROR);
		}
		i++;
	}
	return (count);
}

void	pipes_handler(t_minishell *mini)
{
	int	nbr;

	nbr = count_pipes(mini->tokens);
	if (nbr == ERROR)
		ft_printf("PIPE ERROR");
	else if (nbr != FALSE)
		ft_printf("SUCCESS %d PIPES", nbr);
	else
		ft_printf("SUCCESS %d PIPES", nbr);
}
