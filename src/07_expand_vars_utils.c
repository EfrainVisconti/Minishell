/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_vars2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 15:54:39 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/01 16:01:06 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//gets the remaining part after expanding the variable
char	*from_var_name_to_end(char *s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(s);
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			i++;
			while (tmp[i] && s[i] != ' ' && tmp[i] != '\n' && tmp[i] != '\t'
				&& tmp[i] != '\'' && tmp[i] != '"')
				i++;
			return (&tmp[i]);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

//obtains the part from the beginning to the expansion dollar
char	*from_beginning_to_dollar(char	*s)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strdup(s);
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
	char	*tmp;

	start = 0;
	i = 0;
	tmp = ft_strdup(s);
	while (tmp[i])
	{
		if (tmp[i] == '$')
		{
			i++;
			start = i;
			while (tmp[i] && tmp[i] != ' ' && tmp[i] != '\n' && tmp[i] != '\t'
				&& tmp[i] != '\'' && tmp[i] != '"')
				i++;
			tmp[i] = '\0';
			return (&tmp[start]);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}
