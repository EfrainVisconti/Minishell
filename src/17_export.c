/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:01:46 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/25 20:51:20 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	simple_export_aux(t_env **cu_na, t_env **env, int *size, int fd)
{
	cu_na[0] = *env;
	cu_na[1] = cu_na[0];
	while (cu_na[1]->is_pri == TRUE && cu_na[1]->next)
		cu_na[1] = cu_na[1]->next;
	while (cu_na[0])
	{
		if (ft_strcmp(cu_na[1]->name, cu_na[0]->name) > 0 && !cu_na[0]->is_pri)
			cu_na[1] = cu_na[0];
		cu_na[0] = cu_na[0]->next;
	}
	cu_na[1]->is_pri = TRUE;
	if (!cu_na[1]->is_exp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(cu_na[1]->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(cu_na[1]->content, fd);
	}
	else
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(cu_na[1]->name, fd);
	}
	ft_putstr_fd("\n", fd);
	(*size)--;
}

//current 0, name 1
void	simple_export(t_env **env, int fd)
{
	t_env	*current_name[2];
	int		size;

	size = 0;
	current_name[1] = NULL;
	current_name[0] = *env;
	while (current_name[0])
	{
		size++;
		current_name[0] = current_name[0]->next;
	}
	while (size > 1)
		simple_export_aux(current_name, env, &size, fd);
	current_name[0] = *env;
	while (current_name[0])
	{
		current_name[0]->is_pri = FALSE;
		current_name[0] = current_name[0]->next;
	}
}

//new_node 0, exist 1
void	export_add_node(t_env *env, char *name, char *content, int mode)
{
	t_env	*current;
	t_env	*new_node_exist[2];

	new_node_exist[1] = find_env_var(&env, name);
	if (!new_node_exist[1])
	{
		if (mode == 1)
			new_node_exist[0] = new_env_node(name, content, 1, 0);
		else if (mode == 0)
			new_node_exist[0] = new_env_node(name, NULL, 0, 1);
		if (!env)
		{
			env = new_node_exist[0];
			return ;
		}
		current = env;
		while (current->next)
			current = current->next;
		current->next = new_node_exist[0];
	}
	else
	{
		new_node_exist[1]->content = ft_strdup(content, 0);
		free(new_node_exist[1]->content);
	}
}

int	ft_export(t_minishell *mini, t_node *node, int fd)
{
	int		len;
	char	*equal;
	char	*name;
	char	*content;

	equal = NULL;
	len = ft_arraylen(node->full_cmd);
	if (len == 1)
		return (simple_export(&(mini->env), fd), 0);
	else if (len > 1 && ft_strcmp(node->full_cmd[1], "?") && \
		ft_strcmp(node->full_cmd[1], "_") && ft_strcmp(node->full_cmd[1], ""))
	{
		equal = ft_strchr(node->full_cmd[1], '=');
		if (equal)
		{
			name = ft_substr(node->full_cmd[1], 0, equal - node->full_cmd[1]);
			content = ft_substr(equal + 1, 0, ft_strlen(equal + 1));
			export_add_node(mini->env, name, content, 1);
			return (free(name), free(content), 0);
		}
		else
			return (export_add_node(mini->env, node->full_cmd[1], "", 0), 0);
	}
	return (print_error(21, NULL), 1);
}
