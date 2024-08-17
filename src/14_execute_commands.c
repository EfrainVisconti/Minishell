/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:08 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/17 15:04:32 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_commands(t_minishell *mini)
{
	pid_t	pid;
	int		pipefd[2];
	int		i;

	i = 0;
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
				if (mini->nodes[0]->infile != STDIN_FILENO)
				{
					if (dup2(mini->nodes[0]->infile, STDIN_FILENO) == -1)
						print_error(13, NULL);
					close(mini->nodes[0]->infile);
				}
				if (mini->nodes[0]->outfile != STDOUT_FILENO)
				{
					if (dup2(mini->nodes[0]->outfile, STDOUT_FILENO) == -1)
						print_error(14, NULL);
					close(mini->nodes[0]->outfile);
				}
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
	else if (mini->nbr_nodes > 1)
	{
		while (mini->nodes[i])
		{
			if (pipe(pipefd) == -1)
				return ;
			pid = fork();
			if (pid == -1)
				return ;
			else if (pid == 0)
			{
				if (mini->nodes[i]->infile != STDIN_FILENO)
				{
					if (dup2(mini->nodes[i]->infile, STDIN_FILENO) == -1)
						print_error(13, NULL);
					close(mini->nodes[i]->infile);
				}
				else if (mini->nodes[i]->infile == STDIN_FILENO && i != 0)
				{

				}
				if (mini->nodes[i]->outfile != STDOUT_FILENO)
				{
					if (dup2(mini->nodes[i]->outfile, STDOUT_FILENO) == -1)
						print_error(13, NULL);
					close(mini->nodes[i]->outfile);
				}
				if (i < mini->nbr_nodes - 1)
				{
					if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
						print_error(15, NULL);
				}
				close(pipefd[READ]);
				close(pipefd[WRITE]);
				if (execve(mini->nodes[i]->full_path, mini->nodes[i]->full_cmd, mini->argenv) == -1)
				{
					print_error(12, mini->nodes[i]->full_cmd[0]);
					exit (127);
				}
			}
			else
			{
				waitpid(pid, &g_status, 0);
				close(pipefd[WRITE]);
				if (dup2(pipefd[READ], STDIN_FILENO) == -1)
				 	print_error(16, NULL);
				 close(pipefd[READ]);
			}
			i++;
		}
	}
}
