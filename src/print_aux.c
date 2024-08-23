/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:14:27 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/23 15:11:19 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// void	print_aux(t_minishell *mini)
// {
// 	int		i;
// 	// t_env	*auxe;

// 	i = 0;
// 	// auxe = mini->env;
// 	// while (auxe)
// 	// {
// 	// 	ft_printf("%s=%s\n", auxe->name, auxe->content);
// 	// 	ft_printf("%d\n", auxe->is_env);
// 	// 	auxe = auxe->next;
// 	// }
// 	// ft_printf("--------------------------------------------------\n");
// 	// while (mini->bin_path[i])
// 	// {
// 	// 	ft_printf("%s\n", mini->bin_path[i]);
// 	// 	i++;
// 	// }
// 	// i = 0;
// 	ft_printf("--------------------------------------------------\n");
// 	if (mini->input != NULL)
// 		ft_printf("INPUT: %s\n", mini->input);
// 	else
// 		ft_printf("INPUT NULL\n");
// 	ft_printf("--------------------------------------------------\n");
// 	if (mini->tokens != NULL)
// 	{
// 		while (mini->tokens[i] != NULL)
// 		{
// 			ft_printf("TOKEN[%d]: %s\n", i, mini->tokens[i]);
// 			i++;
// 		}
// 	}
// 	else
// 		ft_printf("TOKENS NULL\n");
// 	ft_printf("--------------------------------------------------\n");
// 	ft_printf("Number of nodes: %d\n", mini->nbr_nodes);
// 	i = 0;
// 	ft_printf("--------------------------------------------------\n");
// 	int j;
// 	if (mini->nodes != NULL && mini->nodes[i] != NULL)
// 	{
// 		while (mini->nodes[i] != NULL)
// 		{
// 			j = 0;
// 			if (mini->nodes[i]->full_cmd != NULL)
// 			{
// 				ft_printf("Full cmd: ");
// 				while (mini->nodes[i]->full_cmd[j] != NULL)
// 				{
// 					ft_printf("%s ", mini->nodes[i]->full_cmd[j]);
// 					j++;
// 				}
// 				ft_printf("\n");
// 			}
// 			else
// 				ft_printf("Full cmd NULL\n");
// 			if (mini->nodes[i]->full_path != NULL)
// 				ft_printf("Bin path: %s\n", mini->nodes[i]->full_path);
// 			else
// 				ft_printf("Bin path NULL\n");
// 			ft_printf("infile: %d\n", mini->nodes[i]->infile);
// 			ft_printf("outfile: %d\n", mini->nodes[i]->outfile);
// 			ft_printf("is executable: %d\n", mini->nodes[i]->is_exec);
// 			i++;
// 		}
// 	}
// 	else
// 		ft_printf("NODES NULL\n");
// }
