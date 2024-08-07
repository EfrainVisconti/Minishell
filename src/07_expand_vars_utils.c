/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_vars_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:39 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/07 18:03:08 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//gets the remaining part after expanding the variable
char	*from_var_name_to_end(char *s)
{
	int	i;
	int	start;
	int	len;

	len = ft_strlen(s);
	start = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			i++;
			while (s[i] && s[i] != ' ' && s[i] != '\n' && s[i] != '\t'
				&& s[i] != '\'' && s[i] != '"')
				i++;
			start = i;
			return (ft_substr(s, start, len));
		}
		i++;
	}
	return (NULL);
}

//obtains the part from the beginning to the expansion dollar
char	*from_beginning_to_dollar(char	*s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(s, 0);
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			tmp[i] = '\0';
			return (&tmp[0]);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

//extracts the name of the variable to expand
char	*var_name_exp(char *s)
{
	int		start;
	int		i;

	start = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '$')
		{
			start = i + 1;
			while (s[i] && s[i] != ' ' && s[i] != '\n' && s[i] != '\t'
				&& s[i] != '\'' && s[i] != '"')
				i++;
			return (ft_substr(s, start, i - start));
		}
		i++;
	}
	return (NULL);
}
