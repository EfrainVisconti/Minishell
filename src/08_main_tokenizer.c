/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_main_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:44:43 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/31 18:10:28 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	look_for_expansion(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (check_expand_needed(tokens[i]) == TRUE)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	**main_tokenizer(t_minishell *mini)
{
	char	**tok;
	int		len;

	len = ft_strlen(mini->input);
	tok = quotes_tokenizer(add_spaces_tokenizer(mini->input, 0, 0, len));
	if (!tok)
		print_error(1);
	if (look_for_expansion(tok) == TRUE)
		tok = expand_vars(tok, mini->env);
	return (tok);
}
