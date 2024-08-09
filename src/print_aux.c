/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: usuario <usuario@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:14:27 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/09 15:36:19 by usuario          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_aux(t_minishell *mini)
{
	int		i;
	// t_env	*auxe;

	// i = 0;
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
	i = 0;
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
}
