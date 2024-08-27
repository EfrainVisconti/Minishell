/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_execute_commands.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 14:45:08 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/27 14:16:12 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	child_execution(t_minishell *min, t_node *node, int aux)
{
	if (!is_builtin(node->full_cmd[0])
		&& node->is_exec)
	{
		if (execve(node->full_path, node->full_cmd, min->argenv) == -1)
		{
			print_error(12, node->full_cmd[0]);
			exit (127);
		}
	}
	else if (is_builtin(node->full_cmd[0])
		&& node->is_exec)
	{
		execute_builtin(node->full_cmd[0], min, aux);
		exit (g_status);
	}
}

void	child_process(t_minishell *min, t_node *node, int aux[2], int pipefd[2])
{
	if (node->infile != STDIN_FILENO)
	{
		if (dup2(node->infile, STDIN_FILENO) == -1)
			print_error(13, NULL);
		close(node->infile);
	}
	else if (aux[1] != -1)
	{
		if (dup2(aux[1], STDIN_FILENO) == -1)
			print_error(13, NULL);
		close(aux[1]);
	}
	if (node->outfile != STDOUT_FILENO)
	{
		if (dup2(node->outfile, STDOUT_FILENO) == -1)
			print_error(14, NULL);
		close(node->outfile);
	}
	else if (aux[0] < min->nbr_nodes - 1)
		dup2(pipefd[WRITE], STDOUT_FILENO);
	close(pipefd[READ]);
	close(pipefd[WRITE]);
	child_execution(min, node, aux[0]);
}

void	excecute_pipe_sequence(t_minishell *mini, int pipefd[2])
{
	int	aux[2];

	aux[0] = -1;
	aux[1] = -1;
	while (mini->nodes[++aux[0]])
	{
		if (pipe(pipefd) == -1)
			return ;
		mini->nodes[aux[0]]->n_pid = fork();
		if (mini->nodes[aux[0]]->n_pid == -1)
			return ;
		else if (mini->nodes[aux[0]]->n_pid == 0)
			child_process(mini, mini->nodes[aux[0]], aux, pipefd);
		else
		{
			close(pipefd[WRITE]);
			if (aux[1] != -1)
				close(aux[1]);
			aux[1] = pipefd[READ];
		}
	}
	aux[0] = -1;
	while (++aux[0] < mini->nbr_nodes)
		waitpid(mini->nodes[aux[0]]->n_pid, &g_status, 0);
}

void	execute_simple_command(t_minishell *mini, t_node *node, pid_t pid)
{
	pid = fork();
	if (pid == -1)
		return ;
	else if (pid == 0)
	{
		if (node->infile != STDIN_FILENO)
		{
			if (dup2(node->infile, STDIN_FILENO) == -1)
				print_error(13, NULL);
			close(node->infile);
		}
		if (node->outfile != STDOUT_FILENO)
		{
			if (dup2(node->outfile, STDOUT_FILENO) == -1)
				print_error(14, NULL);
			close(node->outfile);
		}
		if (execve(node->full_path, node->full_cmd, mini->argenv) == -1)
		{
			print_error(12, node->full_cmd[0]);
			exit (127);
		}
	}
	else
		waitpid(pid, &g_status, 0);
}

void	execute_commands(t_minishell *mini)
{
	pid_t	pid;
	int		pipefd[2];

	pid = 0;
	mini->signal = TRUE;
	init_signals(&((*mini).signal));
	if (mini->nbr_nodes == 1 && mini->nodes[0]->full_cmd)
	{
		if (is_builtin(mini->nodes[0]->full_cmd[0])
			&& mini->nodes[0]->is_exec)
			execute_builtin(mini->nodes[0]->full_cmd[0], mini, 0);
		else if (!is_builtin(mini->nodes[0]->full_cmd[0])
			&& mini->nodes[0]->is_exec)
			execute_simple_command(mini, mini->nodes[0], pid);
	}
	else if (mini->nbr_nodes > 1)
		excecute_pipe_sequence(mini, pipefd);
}
