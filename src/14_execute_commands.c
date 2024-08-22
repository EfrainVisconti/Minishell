/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:08 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/22 18:38:02 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute_commands(t_minishell *mini)
{
	pid_t	pid;
	int		pipefd[2];
	int		i;
	int		prev_pipe_read;

	prev_pipe_read = -1;
	i = 0;
	if (mini->nbr_nodes == 1 && mini->nodes[0]->full_cmd)
	{
		if (is_builtin(mini->nodes[0]->full_cmd[0])
		&& mini->nodes[0]->is_exec)
			execute_builtin(mini->nodes[0]->full_cmd[0], mini, 0);
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
				else if (prev_pipe_read != -1)
				{
					if (dup2(prev_pipe_read, STDIN_FILENO) == -1)
						print_error(13, NULL);
					close(prev_pipe_read);
				}
				if (mini->nodes[i]->outfile != STDOUT_FILENO)
				{
					if (dup2(mini->nodes[i]->outfile, STDOUT_FILENO) == -1)
						print_error(14, NULL);
					close(mini->nodes[i]->outfile);
				}
				else if (i < mini->nbr_nodes - 1)
				{
					if (dup2(pipefd[WRITE], STDOUT_FILENO) == -1)
						print_error(15, NULL);
				}
				close(pipefd[READ]);
				close(pipefd[WRITE]);
				if (!is_builtin(mini->nodes[i]->full_cmd[0])
				&& mini->nodes[i]->is_exec)
				{
					if (execve(mini->nodes[i]->full_path, mini->nodes[i]->full_cmd, mini->argenv) == -1)
					{
						print_error(12, mini->nodes[i]->full_cmd[0]);
						exit (127);
					}
				}
				else if (is_builtin(mini->nodes[i]->full_cmd[0])
				&& mini->nodes[i]->is_exec)
				{
					execute_builtin(mini->nodes[i]->full_cmd[0], mini, i);
					exit (g_status);
				}
			}
			else
			{
				close(pipefd[WRITE]);
				if (prev_pipe_read != -1)
					close(prev_pipe_read);
				prev_pipe_read = pipefd[READ];
			}
			i++;
		}
		i = 0;
		while (i < mini->nbr_nodes)
		{
			wait(NULL);
			i++;
		}
	}
}
