/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_set_execution_nodes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:32:48 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/23 15:32:26 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**get_next_node(char **tmp, char ***next)
{
	int		count;
	int		i;
	char	**elements;

	count = 0;
	i = 0;
	while (tmp[count] && ft_strcmp(tmp[count], "|"))
		count++;
	elements = malloc(sizeof(char *) * (count + 1));
	if (!elements)
		return (NULL);
	while (i < count)
	{
		elements[i] = tmp[i];
		i++;
	}
	elements[i] = NULL;
	tmp += count;
	if (*tmp && !ft_strcmp(*tmp, "|"))
		tmp++;
	*next = tmp;
	return (elements);
}

//set_full_cmd can return NULL
t_node	*create_exec_nodes_aux(t_minishell *mini, char **tokens)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return (NULL);
	new->infile = STDIN_FILENO;
	new->outfile = STDOUT_FILENO;
	new->full_cmd = set_full_cmd(tokens, 0, 0);
	new->full_path = set_full_path(new, mini->bin_path);
	if (set_infile_outfile(new, tokens, new->outfile, new->infile) == ERROR)
		new->is_exec = FALSE;
	else
		new->is_exec = TRUE;
	free(tokens);
	return (new);
}

//creates the execution nodes, nbr - 1 is the number of pipes
t_node	**create_exec_nodes(t_minishell *mini, int nbr)
{
	t_node	**nodes;
	int		i;
	char	**tmp;
	char	**next;

	i = 0;
	nodes = malloc(sizeof(t_node *) * (nbr + 1));
	if (nodes == NULL)
		return (NULL);
	mini->nbr_nodes = nbr;
	tmp = mini->tokens;
	while (nbr > 0)
	{
		tmp = get_next_node(tmp, &next);
		nodes[i] = create_exec_nodes_aux(mini, tmp);
		tmp = next;
		i++;
		nbr--;
	}
	nodes[i] = NULL;
	return (nodes);
}

//initializes the execution nodes after checking if the pipes and
//redirects are valid
int	set_execution_nodes(t_minishell *mini)
{
	int	nbr;
	int	redir;

	redir = check_wrong_redir(mini->tokens);
	nbr = pipes_handler(mini->tokens);
	if (nbr == ERROR)
		return (print_error(2, NULL), FALSE);
	else if (redir == FALSE)
		return (print_error(8, NULL), FALSE);
	else if (redir == ERROR)
		return (print_error(9, NULL), FALSE);
	else if (nbr != ERROR && redir == TRUE)
		mini->nodes = create_exec_nodes(mini, nbr + 1);
	return (TRUE);
}
