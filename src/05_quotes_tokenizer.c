/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_quotes_tokenizer.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:35:30 by usuario           #+#    #+#             */
/*   Updated: 2024/08/05 20:43:46 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//count how many tokens and if there are open quotes
int	count_tokens(char *s, int i, int tokens)
{
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	while (s[i])
	{
		if (!ft_strchr(" \t\n", s[i]))
		{
			tokens++;
			while ((!ft_strchr(" \t\n", s[i]) || q[0]) && s[i])
			{
				if (!q[1] && (s[i] == '\"' || s[i] == '\''))
					q[1] = s[i];
				q[0] = (q[0] + (s[i] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i++;
			}
			if (q[0])
				return (-1);
		}
		else
			i++;
	}
	return (tokens);
}

//creates tokens within the array **tokens
char	**quotes_tokenizer_aux(char **tokens, char	*s, int start, int tok)
{
	int		i;
	int		q[2];

	q[0] = 0;
	q[1] = 0;
	i = 0;
	while (s[i])
	{
		while (ft_strchr(" \t\n", s[i]) && s[i])
			i++;
		start = i;
		while ((!ft_strchr(" \t\n", s[i]) || q[0] || q[1]) && s[i])
		{
			q[0] = (q[0] + (!q[1] && s[i] == '\'')) % 2;
			q[1] = (q[1] + (!q[0] && s[i] == '\"')) % 2;
			i++;
		}
		if (!s[start])
			tokens[tok++] = "\0";
		else
			tokens[tok++] = ft_substr(s, start, i - start);
	}
	return (tokens);
}

//tokenize taking quotes into account
char	**quotes_tokenizer(char *input)
{
	char	**tokens;
	int		nbr_tokens;

	nbr_tokens = count_tokens(input, 0, 0);
	if (nbr_tokens == -1)
		return (NULL);
	tokens = malloc(sizeof(char *) * (nbr_tokens + 1));
	if (!tokens)
		return (NULL);
	tokens = quotes_tokenizer_aux(tokens, input, 0, 0);
	tokens[nbr_tokens] = NULL;
	return (tokens);
}
