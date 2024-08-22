/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_environment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 18:34:13 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/22 16:31:48 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// find a specific environment variable
t_env	*find_env_var(t_env **env_var, char *name)
{
	t_env	*current;

	current = *env_var;
	while (current)
	{
		if (!ft_strcmp(current->name, name))
			return (current);
		current = current->next;
	}
	return (NULL);
}

// stores the paths of the binaries
void	set_bin_path(t_minishell *mini)
{
	t_env	*bin_path;

	bin_path = find_env_var(&(mini->env), "PATH");
	if (bin_path)
		mini->bin_path = ft_split(bin_path->content, ':');
	else
		mini->bin_path = NULL;
}

// creates a new environment variable
t_env	*new_env_node(char *name, char *content)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	if (name)
		new_node->name = ft_strdup(name, 0);
	else
		new_node->name = ft_strdup("", 0);
	if (content)
		new_node->content = ft_strdup(content, 0);
	else
		new_node->content = ft_strdup("", 0);
	new_node->is_env = TRUE;
	new_node->is_exp = FALSE;
	new_node->is_printed = FALSE;
	new_node->next = NULL;
	return (new_node);
}

// initialize environment variables
void	set_env(char **env, t_minishell *mini)
{
	char	**split_env;
	t_env	*current;
	t_env	*new_node;

	while (*env != NULL)
	{
		split_env = ft_split(*env, '=');
		new_node = new_env_node(split_env[0], split_env[1]);
		if (!mini->env)
			mini->env = new_node;
		else
		{
			current = mini->env;
			while (current->next)
				current = current->next;
			current->next = new_node;
		}
		free_array(split_env);
		env++;
	}
}
