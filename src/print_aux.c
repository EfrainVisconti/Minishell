/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:14:27 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/07 11:55:38 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_aux(t_minishell *mini)
{
	int			i;

	i = 0;
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
}
