/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_set_full_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:37:16 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/14 18:22:04 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//checks if the command is a builtin
int	is_builtin(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") || \
	!ft_strcmp(s, "pwd") || !ft_strcmp(s, "export") || \
	!ft_strcmp(s, "unset") || !ft_strcmp(s, "env") || \
	!ft_strcmp(s, "exit"))
		return (TRUE);
	return (FALSE);
}

char	*set_full_path(t_node *n, char **bin_path)
{
	char	*p;
	int		i;

	i = 0;
	if (n->full_cmd && !is_builtin(n->full_cmd[0]))
	{
		while (bin_path[i] != NULL)
		{
			p = ft_strjoin(ft_strjoin(bin_path[i], "/", 2), n->full_cmd[0], 3);
			if (access(p, X_OK) == 0)
				return (p);
			free(p);
			i++;
		}
		return (ft_strdup(n->full_cmd[0], 0));
	}
	return (NULL);
}
