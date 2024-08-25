/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:01:46 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/25 19:05:17 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	simple_export_aux(t_env *cur, t_env **env, t_env *name, int *size, int fd)
{
	cur = *env;
	name = cur;
	while (name->is_printed == TRUE && name->next)
		name = name->next;
	while (cur)
	{
		if (ft_strcmp(name->name, cur->name) > 0 && cur->is_printed == FALSE)
			name = cur;
		cur = cur->next;
	}
	name->is_printed = TRUE;
	if (!name->is_exp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(name->name, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(name->content, fd);
	}
	else
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(name->name, fd);
	}
	ft_putstr_fd("\n", fd);
	(*size)--;
}

void	simple_export(t_env **env, int fd)
{
	t_env	*current;
	t_env	*name;
	int		size;

	size = 0;
	name = NULL;
	current = *env;
	while (current)
	{
		size++;
		current = current->next;
	}
	while (size > 1)
		simple_export_aux(current, env, name, &size, fd);
	current = *env;
	while (current)
	{
		current->is_printed = FALSE;
		current = current->next;
	}
}

void	export_add_node(t_env *env, char *name, char *content, int mode)
{
	t_env	*current;
	t_env	*new_node;
	t_env	*exist;

	exist = find_env_var(&env, name);
	if (!exist)
	{
		if (mode == 1)
			new_node = new_env_node(name, content, 1, 0);
		else if (mode == 0)
			new_node = new_env_node(name, NULL, 0, 1);
		if (!env)
		{
			env = new_node;
			return ;
		}
		current = env;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	else
	{
		exist->content = ft_strdup(content, 0);
		free(exist->content);
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
	else if (len > 1 && ft_strcmp(node->full_cmd[1], "?")
	&& ft_strcmp(node->full_cmd[1], "_") && ft_strcmp(node->full_cmd[1], ""))
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