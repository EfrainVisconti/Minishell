/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:14:27 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/12 14:42:48 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// //linked list for enviroment variables
// typedef struct s_env
// {
// 	char			*name;
// 	char			*content;
// 	int				is_env;
// 	struct s_env	*next;
// }					t_env;

// //struct for nodes resulting from separation by pipes
// typedef struct s_node
// {
// 	char	**full_cmd;
// 	char	*full_path;
// 	int		infile;
// 	int		outfile;
// }			t_node;

// //main struct for the program
// typedef struct s_minishell
// {
// 	t_env		*env;
// 	char		**argenv;
// 	char		**bin_path;
// 	char		*input;
// 	char		**tokens;
// 	int			pid;
// 	t_node		**nodes;
// }					t_minishell;

void	print_aux(t_minishell *mini)
{
	int		i;
	// t_env	*auxe;

	i = 0;
	// auxe = mini->env;
	// while (auxe)
	// {
	// 	ft_printf("%s=%s\n", auxe->name, auxe->content);
	// 	ft_printf("%d\n", auxe->is_env);
	// 	auxe = auxe->next;
	// }
	// ft_printf("--------------------------------------------------\n");
	// while (mini->bin_path[i])
	// {
	// 	ft_printf("%s\n", mini->bin_path[i]);
	// 	i++;
	// }
	// i = 0;
	ft_printf("--------------------------------------------------\n");
	if (mini->input != NULL)
		ft_printf("INPUT: %s\n", mini->input);
	else
		ft_printf("INPUT NULL\n");
	ft_printf("--------------------------------------------------\n");
	if (mini->tokens != NULL)
	{
		while (mini->tokens[i] != NULL)
		{
			ft_printf("TOKEN[%d]: %s\n", i, mini->tokens[i]);
			i++;
		}
	}
	else
		ft_printf("TOKENS NULL\n");
	i = 0;
	ft_printf("--------------------------------------------------\n");
	int j;
	if (mini->nodes != NULL && mini->nodes[i] != NULL && mini->nodes[i]->full_cmd != NULL)
	{
		while (mini->nodes[i] != NULL)
		{
			j = 0;
			while (mini->nodes[i]->full_cmd[j] != NULL)
			{
				ft_printf("%s\n", mini->nodes[i]->full_cmd[j]);
				j++;
			}
			i++;
		}
	}
	else
		ft_printf("NODES NULL\n");
}
