/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_set_infile_outfile.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 17:34:26 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/12 21:12:32 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	check_heredoc(t_minishell *mini)
{
	int i;

	i = 0;
	while (mini->tokens[i] != NULL)
	{
		if (!ft_strcmp(mini->tokens[i], "<<"))
			ft_printf("TO DO HEREDOC\n");
		i++;
	}
}

int	set_infile_outfile(t_minishell *mini, t_node *node, char **tok)
{
	int	i;
	int	out_fd;
	int in_fd;

	i = 0;
	in_fd = node->infile;
	out_fd = node->outfile;
	check_heredoc(mini);
	while (tok[i] != NULL)
	{
		if (!ft_strcmp(tok[i], ">") && tok[i + 1])
		{
			if (out_fd != STDOUT_FILENO)
				close(out_fd);
			out_fd = open(tok[++i], O_CREAT | O_WRONLY | O_TRUNC, 0666);
			if (out_fd == -1)
			{
				print_error(10, NULL);
				return (ERROR);
			}
		}
		else if (!ft_strcmp(tok[i], ">>") && tok[i + 1])
		{
			if (out_fd != STDOUT_FILENO)
				close(out_fd);
			out_fd = open(tok[++i], O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (out_fd == -1)
			{
				print_error(10, NULL);
				return (ERROR);
			}
		}
		else if (!ft_strcmp(tok[i], "<") && tok[i + 1])
        {
            if (in_fd != STDIN_FILENO)
				close(in_fd);
            in_fd = open(tok[++i], O_RDONLY);
            if (in_fd == -1)
            {
                print_error(11, tok[i]);
                return (ERROR);
            }
        }
		i++;
	}
	node->infile = in_fd;
	node->outfile = out_fd;
	return (TRUE);
}
