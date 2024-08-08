/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_set_execution_nodes.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 12:32:48 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/08 19:00:56 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//last check of redirections before execution
int	check_wrong_redir(char **tok)
{
	int	i;

	i = 0;
	while (tok[i] != NULL)
	{
		if (tok[i + 1] && (!ft_strcmp(tok[i], "<") || !ft_strcmp(tok[i], "<<")
				|| !ft_strcmp(tok[i], ">") || !ft_strcmp(tok[i], ">>"))
			&& (!ft_strcmp(tok[i + 1], "<") || !ft_strcmp(tok[i + 1], "<<")
				|| !ft_strcmp(tok[i + 1], ">") || !ft_strcmp(tok[i + 1], ">>")))
			return (FALSE);
		i++;
	}
	if (!ft_strcmp(tok[i - 1], "<") || !ft_strcmp(tok[i - 1], "<<")
		|| !ft_strcmp(tok[i - 1], ">") || !ft_strcmp(tok[i - 1], ">>"))
		return (ERROR);
	return (TRUE);
}

//last check of the pipes before execution
int	pipes_handler(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i] != NULL)
	{
		if (!ft_strcmp(tokens[i], "|"))
		{
			count++;
			if (i == 0 || tokens[i + 1] == NULL || \
				!ft_strcmp(tokens[i - 1], "<") || \
				!ft_strcmp(tokens[i - 1], "<<") || \
				!ft_strcmp(tokens[i - 1], ">") || \
				!ft_strcmp(tokens[i - 1], ">>") || \
				!ft_strcmp(tokens[i - 1], "|"))
				return (ERROR);
		}
		i++;
	}
	return (count);
}

// typedef struct s_node
// {
// 	char	**full_cmd;
// 	char	*full_path;
// 	int		infile;
// 	int		outfile;
// 	int		is_builtin;
// }			t_node;

// char	**quotes_tokenizer_aux(char **tokens, char	*s, int start, int tok)
// {
// 	int		i;
// 	int		q[2];

// 	q[0] = 0;
// 	q[1] = 0;
// 	i = 0;
// 	while (s[i])
// 	{
// 		while (ft_strchr(" \t\n", s[i]) && s[i])
// 			i++;
// 		start = i;
// 		while ((!ft_strchr(" \t\n", s[i]) || q[0] || q[1]) && s[i])
// 		{
// 			q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
// 			q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
// 			i++;
// 		}
// 		if (!s[start])
// 			tokens[tok++] = "\0";
// 		else
// 			tokens[tok++] = ft_substr(s, start, i - start);
// 	}
// 	return (tokens);
// }

// char	**quotes_tokenizer(char *input)
// {
// 	char	**tokens;
// 	int		nbr_tokens;

// 	nbr_tokens = count_tokens(input, 0, 0);
// 	if (nbr_tokens == -1)
// 		return (NULL);
// 	tokens = malloc(sizeof(char *) * (nbr_tokens + 1));
// 	if (!tokens)
// 		return (NULL);
// 	tokens = quotes_tokenizer_aux(tokens, input, 0, 0);
// 	tokens[nbr_tokens] = NULL;
// 	return (tokens);
// }

t_node	*create_exec_nodes_aux(t_minishell *mini)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	new->full_path = ft_s(mini->bin_path[0]);
	return (new);
}

//creates the execution nodes, nbr - 1 is the number of pipes
t_node	**create_exec_nodes(t_minishell *mini, int nbr)
{
	t_node	**nodes;

	nodes = malloc(sizeof(t_node *) * (nbr + 1));
	if (nodes == NULL)
		return (NULL);
	nodes = NULL;
	if (nbr == 1)
	{
		nodes[0] = create_exec_nodes_aux(mini);
		ft_printf("un nodo\n");

	}
	else
	{
		ft_printf("dos nodos\n");
	}
	nodes[nbr + 1] = NULL;
	return (nodes);
}

//initializes the execution nodes after checking if the pipes and
//redirects are valid
void	set_execution_nodes(t_minishell *mini)
{
	int	nbr;
	int	redir;

	redir = check_wrong_redir(mini->tokens);
	nbr = pipes_handler(mini->tokens);
	if (nbr == ERROR)
		print_error(2);
	else if (nbr != ERROR && redir == TRUE)
		mini->nodes = create_exec_nodes(mini, nbr + 1);
	else if (redir == FALSE)
		print_error(8);
	else if (redir == ERROR)
		print_error(9);
}
