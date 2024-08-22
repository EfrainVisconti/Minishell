/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:07:14 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/22 13:57:44 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	free_nodes(t_node **nodes)
{
	int	i;

	i = 0;
	if (nodes && *nodes && nodes[i])
	{
		while (nodes[i] != NULL)
		{
			if (nodes[i]->full_cmd != NULL)
				free(nodes[i]->full_cmd);
			if (nodes[i]->full_path != NULL)
				free(nodes[i]->full_path);
			free(nodes[i]);
			i++;
		}
	}
	free(nodes);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env;
		env = env->next;
		free(tmp->name);
		free(tmp->content);
		free(tmp);
	}
}

void	free_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

//free program from main exit fuction
void	free_main(t_minishell *mini)
{
	free_env(mini->env);
	if (mini->bin_path)
		free_array(mini->bin_path);
}
