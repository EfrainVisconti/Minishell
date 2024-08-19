/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:11:52 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/19 22:46:50 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_node *node)
{
	int	i;
	int	len;

	len = ft_arraylen(node->full_cmd);
	i = 1;
	if (!ft_strcmp(node->full_cmd[i], "-n"))
	{
		i++;
		while (node->full_cmd[i])
		{
			ft_putstr_fd(node->full_cmd[i], 1);
			if (i++ < len - 1)
				ft_putstr_fd(" ", 1);
		}
	}
	else
	{
		while (node->full_cmd[i])
		{
			ft_putstr_fd(node->full_cmd[i], 1);
			if (i++ < len - 1)
				ft_putstr_fd(" ", 1);
		}
		ft_putstr_fd("\n", 1);
	}
}

int	is_numeric(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	ft_exit(t_minishell *mini, t_node *node)
{
	int	len;
	int	exit_status;

	exit_status = 2;
	len = ft_arraylen(node->full_cmd);
	if (len > 2 && is_numeric(node->full_cmd[1]))
	{
		print_error(16, NULL);
		return (1);
	}
	else if (len >= 2 && !is_numeric(node->full_cmd[1]))
		print_error(17, node->full_cmd[1]);
	else if (len == 1)
		exit_status = g_status;
	else if (len == 2 && is_numeric(node->full_cmd[1]))
	{
		exit_status = ft_atoi(node->full_cmd[1]) % 256;
	}
	free_main(mini);
	free(mini->input);
	if (mini->tokens && mini->tokens[0])
		free_array(mini->tokens);
	if (mini->nodes)
		free_nodes(mini->nodes);
	return (ft_putstr_fd("exit\n", 2), exit(exit_status), exit_status);
}

int	ft_env(t_minishell *mini, t_node *node, int len)
{
	t_env	*current;

	current = mini->env;
	len = ft_arraylen(node->full_cmd);
	if (len == 1)
	{
		while (current)
		{
			if (current->is_env)
			{
				ft_putstr_fd(current->name, 1);
				ft_putstr_fd("=", 1);
				ft_putstr_fd(current->content, 1);
				ft_putstr_fd("\n", 1);
				current = current->next;
			}
		}
		return (0);
	}
	else
	{
		print_error(18, node->full_cmd[1]);
		return (127);
	}
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd, 1);
		free(pwd);
	}
	ft_putstr_fd("\n", 1);
}

void	ft_unset(t_minishell *mini, t_node *node, int len)
{
	t_env	*var;
	t_env	*prev;

	len = ft_arraylen(node->full_cmd);
	if (len > 1)
	{
		prev = NULL;
		var = mini->env;
		while (var)
		{
			if (!ft_strcmp(var->name, node->full_cmd[1]))
			{
				if (prev == NULL)
					mini->env = var->next;
				else
					prev->next = var->next;
				free(var->content);
				free(var->name);
				free(var);
				break ;
			}
			prev = var;
			var = var->next;
		}
	}
}

void	execute_builtin(char *s, t_minishell *mini, int i)
{
	g_status = 0;
	if (!ft_strcmp(s, "echo"))
		ft_echo(mini->nodes[i]);
	// else if (!ft_strcmp(s, "cd"))
	// 	ft_cd();
	else if (!ft_strcmp(s, "pwd"))
		ft_pwd();
	// else if (!ft_strcmp(s, "export"))
	// 	ft_export();
	else if (!ft_strcmp(s, "unset"))
		ft_unset(mini, mini->nodes[i], 1);
	else if (!ft_strcmp(s, "env"))
		g_status = ft_env(mini, mini->nodes[i], 1);
	else if (!ft_strcmp(s, "exit"))
	 	g_status = ft_exit(mini, mini->nodes[i]);
}
