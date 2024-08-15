/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:08 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/15 14:06:28 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_commands(t_minishell *mini)
{
	pid_t	pid;

	pid = 0;
	if (mini->nbr_nodes == 1 && mini->nodes[0]->full_cmd)
	{
		if (is_builtin(mini->nodes[0]->full_cmd[0])
		&& mini->nodes[0]->is_exec)
			ft_printf("Exec one Bultin command\n");
		else if (!is_builtin(mini->nodes[0]->full_cmd[0])
		&& mini->nodes[0]->is_exec)
		{
			pid = fork();
			if (pid == -1)
				return ;
			else if (pid == 0)
			{
				if (dup2(mini->nodes[0]->infile, STDIN_FILENO) == -1)
					print_error(13, NULL);
				if (dup2(mini->nodes[0]->outfile, STDOUT_FILENO) == -1)
					print_error(14, NULL);
				close(mini->nodes[0]->infile);
				close(mini->nodes[0]->outfile);
				if (execve(mini->nodes[0]->full_path, mini->nodes[0]->full_cmd, mini->argenv) == -1)
				{
					print_error(12, mini->nodes[0]->full_cmd[0]);
					exit (127);
				}
			}
			else
				waitpid(pid, &g_status, 0);
		}
	}
	else
		ft_printf("TO DO WITH PIPES\n");
}
