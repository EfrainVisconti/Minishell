/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_check_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 12:30:55 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/14 14:52:08 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//last check of redirections before execution
int	check_wrong_redir(char **tok)
{
	int	i;

	i = 0;
	while (tok[i] != NULL)
	{
		if (tok[i + 1] && (!ft_strcmp(tok[i], "<") || !ft_strcmp(tok[i], "<<")
				|| !ft_strcmp(tok[i], ">") || !ft_strcmp(tok[i], ">>"))
			&& (!ft_strcmp(tok[i + 1], "<") || !ft_strcmp(tok[i + 1], "<<")
				|| !ft_strcmp(tok[i + 1], ">") || !ft_strcmp(tok[i + 1], ">>")))
			return (FALSE);
		i++;
	}
	if (i != 0 && (!ft_strcmp(tok[i - 1], "<") || \
	!ft_strcmp(tok[i - 1], "<<") || !ft_strcmp(tok[i - 1], ">") || \
	!ft_strcmp(tok[i - 1], ">>")))
		return (ERROR);
	return (TRUE);
}

//last check of the pipes before execution
int	pipes_handler(char **tokens)
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
