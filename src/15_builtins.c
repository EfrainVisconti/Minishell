/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 16:11:52 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/18 18:33:17 by eviscont         ###   ########.fr       */
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
			ft_putstr_fd(node->full_cmd[i++], node->outfile);
			if (i < len - 1)
				ft_putstr_fd(" ", node->outfile);
		}
	}
	else
	{
		while (node->full_cmd[i])
		{
			ft_putstr_fd(node->full_cmd[i++], node->outfile);
			if (1 < len -1)
				ft_putstr_fd(" ", node->outfile);
		}
		ft_putstr_fd("\n", node->outfile);
	}
}

void	ft_exit(t_minishell *mini, t_node *node)
{
	int	len;

	len = ft_arraylen(node->full_cmd)
	if ()
	free_main(mini);
	free(mini->input);
	if (mini->tokens && mini->tokens[0])
		free_array(mini->tokens);
	if (mini->nodes)
		free_nodes(mini->nodes);
	if (node->full_cmd[1])
	exit (1);
}

void	execute_builtin(char *s, t_minishell *mini, int i)
{
	if (!ft_strcmp(s, "echo"))
		ft_echo(mini->nodes[i]);
	// else if (!ft_strcmp(s, "cd"))
	// 	ft_cd();
	// else if (!ft_strcmp(s, "pwd"))
	// 	ft_pwd();
	// else if (!ft_strcmp(s, "export"))
	// 	ft_export();
	// else if (!ft_strcmp(s, "unset"))
	// 	ft_unset();
	// else if (!ft_strcmp(s, "env"))
	// 	ft_env();
	else if (!ft_strcmp(s, "exit"))
	 	ft_exit(mini, mini->nodes[i]);
}
