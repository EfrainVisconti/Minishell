/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_set_infile_outfile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:34:26 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/23 15:53:31 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_heredoc(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (!ft_strcmp(tokens[i], "<<"))
			ft_printf("TO DO HEREDOC\n");
		i++;
	}
}

int	first_case_aux(char **tok, int *out_fd, int i)
{
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	*out_fd = open(tok[i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (*out_fd == -1)
	{
		print_error(10, NULL);
		return (ERROR);
	}
	return (TRUE);
}

int	second_case_aux(char **tok, int *out_fd, int i)
{
	if (*out_fd != STDOUT_FILENO)
		close(*out_fd);
	*out_fd = open(tok[i], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (*out_fd == -1)
	{
		print_error(10, NULL);
		return (ERROR);
	}
	return (TRUE);
}

int	third_case_aux(char **tok, int *in_fd, int i)
{
	if (*in_fd != STDIN_FILENO)
		close(*in_fd);
	*in_fd = open(tok[i], O_RDONLY);
	if (*in_fd == -1)
	{
		print_error(11, tok[i + 1]);
		return (ERROR);
	}
	return (TRUE);
}

int	set_infile_outfile(t_node *node, char **tok, int out_fd, int in_fd)
{
	int	i;

	i = -1;
	check_heredoc(tok);
	while (tok[++i] != NULL)
	{
		if (!ft_strcmp(tok[i], ">") && tok[i + 1])
		{
			if (first_case_aux(tok, &out_fd, ++i) == ERROR)
				return (ERROR);
		}
		else if (!ft_strcmp(tok[i], ">>") && tok[i + 1])
		{
			if (second_case_aux(tok, &out_fd, ++i) == ERROR)
				return (ERROR);
		}
		else if (!ft_strcmp(tok[i], "<") && tok[i + 1])
		{
			if (third_case_aux(tok, &in_fd, ++i) == ERROR)
				return (ERROR);
		}
	}
	node->infile = in_fd;
	node->outfile = out_fd;
	return (TRUE);
}
