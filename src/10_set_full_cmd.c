/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_set_full_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 19:07:26 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/13 11:26:26 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_redirection(char *s)
{
	if (!ft_strcmp(s, "<<") || !ft_strcmp(s, "<") ||
	!ft_strcmp(s, ">>") || !ft_strcmp(s, ">"))
		return (TRUE);
	return  (FALSE);
}

int	count_cmd(char **tokens)
{
	int i;
	int	cmd;

	cmd = 0;
	i = 0;
	while (tokens[i] != NULL)
	{
		if (is_redirection(tokens[i]))
			i++;
		else
			cmd++;
		i++;
	}
	return (cmd);
}

char	**set_full_cmd(char **tokens, int i, int cmd)
{
	char	**full_cmd;

	cmd = count_cmd(tokens);
	i = 0;
	if (cmd > 0)
		full_cmd = malloc(sizeof(char *) * (cmd + 1));
	else
		return (NULL);
	if (!full_cmd)
		return (NULL);
	cmd = 0;
	while (tokens[i] != NULL)
	{
		if (is_redirection(tokens[i]))
			i++;
		else
			full_cmd[cmd++] = tokens[i];
		i++;
	}
	full_cmd[cmd] = NULL;
	return (full_cmd);
}
