/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   11_set_full_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 14:37:16 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/13 11:30:58 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//checks if the command is a builtin
int	is_builtin(char *s)
{
	if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd") ||
	!ft_strcmp(s, "pwd") || !ft_strcmp(s, "export") ||
	!ft_strcmp(s, "unset") || !ft_strcmp(s, "env") ||
	!ft_strcmp(s, "exit"))
		return (TRUE);
	return  (FALSE);
}

char	*set_full_path(t_node *node, char **bin_path)
{
	char	*path;
	int		i;

	i = 0;
	if (node->full_cmd && !is_builtin(node->full_cmd[0]))
	{
		while (bin_path[i] != NULL)
		{
			path = ft_strjoin(ft_strjoin(bin_path[i], "/", 2), node->full_cmd[0], 3);
			if (access(path, X_OK) == 0)
				return (path) ;
			free(path);
			i++;
		}
	}
	return (NULL);
}
