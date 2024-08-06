/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_main_tokenizer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 19:44:43 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/06 13:59:11 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	remove_quotes_aux(char *s)
{
	int		i;
	int		j;
	int		len;
	char	q;

	len = ft_strlen(s);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (s[i] == '\'' || s[i] == '"')
		{
			q = s[i];
			i++;
			while (i < len && s[i] != q)
				s[j++] = s[i++];
			i++;
		}
		else
			s[j++] = s[i++];
	}
	s[j] = '\0';
}

//checks if there is " or ' in that token
int	has_quotes(char	*str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

//start the process of removing main quotes
void	remove_quotes(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (has_quotes(tokens[i]) == 1)
			remove_quotes_aux(tokens[i]);
		i++;
	}
}

//checks if there is at least one expansion
int	look_for_expansion(char **tokens)
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

//tokenizes the input to be interpreted as in bash
char	**set_tokens(t_minishell *mini, char *input)
{
	char	**tok;
	char	*input_spaces;
	int		len;

	tok = NULL;
	len = ft_strlen(input);
	if (input != NULL)
		input_spaces = add_spaces_tokenizer(input, -1, 0, len);
	if (input_spaces != NULL)
	{
		tok = quotes_tokenizer(input_spaces);
		free(input_spaces);
		if (tok == NULL)
			return (print_error(1), NULL);
		if (look_for_expansion(tok) == TRUE)
		{
			tok = expand_vars(tok, mini->env);
		}
		remove_quotes(tok);
	}
	return (tok);
}
