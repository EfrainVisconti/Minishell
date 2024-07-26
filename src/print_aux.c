/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_aux.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 21:14:27 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/26 21:31:17 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_aux(t_minishell *mini)
{
	t_minishell *auxm;
	t_env	*auxe;
	int i;

	i = 0;
	auxm = mini;
	auxe = mini->env;
	while (auxe)
	{
		ft_printf("%s=%s\n", auxe->content, auxe->name);
		auxe = auxe->next;
	}
	ft_printf("---------\n");
	while (auxm->bin_path[i])
	{
		ft_printf("%s\n", auxm->bin_path[i]);
		i++;
	}
	ft_printf("---------\n");
	ft_printf("%s\n", auxm->input);
}