/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_main_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:44:43 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/30 21:23:19 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	**main_tokenizer(t_minishell *mini)
{
	char	**tokens;

	tokens = quotes_tokenizer(add_spaces_tokenizer(mini->input, 0, 0, ft_strlen(mini->input)));
	if (!tokens)
		print_error(1);
	else
		tokens = expand_vars(tokens, mini->env);
	return (tokens);
}