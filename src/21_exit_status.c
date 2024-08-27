/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   20_exit_status.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 14:59:59 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/26 19:48:44 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	set_exit_status(t_minishell *mini)
{
	t_env	*current;

	current = mini->env;
	while (current->next)
		current = current->next;
	current->next = new_env_node("?", "0", 0, 0);
}

void	update_exit_status(t_minishell *mini)
{
	t_env	*exit_status;

	exit_status = find_env_var(&(mini->env), "?");
	free(exit_status->content);
	if (g_status >= 256)
		exit_status->content = ft_itoa(g_status / 256);
	else
		exit_status->content = ft_itoa(g_status);
}
