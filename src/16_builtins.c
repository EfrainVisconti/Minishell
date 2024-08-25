/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:01:16 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/25 19:28:33 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_echo(t_node *node, int fd)
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
			ft_putstr_fd(node->full_cmd[i], fd);
			if (i++ < len - 1)
				ft_putstr_fd(" ", fd);
		}
	}
	else
	{
		while (node->full_cmd[i])
		{
			ft_putstr_fd(node->full_cmd[i], fd);
			if (i++ < len - 1)
				ft_putstr_fd(" ", fd);
		}
		ft_putstr_fd("\n", fd);
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

int	ft_env(t_minishell *mini, t_node *node, int len, int fd)
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
				ft_putstr_fd(current->name, fd);
				ft_putstr_fd("=", fd);
				ft_putstr_fd(current->content, fd);
				ft_putstr_fd("\n", fd);
			}
			current = current->next;
		}
		return (0);
	}
	else
	{
		print_error(18, node->full_cmd[1]);
		return (127);
	}
}

void	ft_pwd(int fd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd != NULL)
	{
		ft_putstr_fd(pwd, fd);
		free(pwd);
	}
	ft_putstr_fd("\n", fd);
}
