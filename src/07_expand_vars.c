/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:05 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/14 12:27:33 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_expand_needed(char *token, int *nbr)
{
	int	i;
	int	qs;
	int	qd;

	qd = 0;
	qs = 0;
	i = 0;
	while (token[i] != '\0')
	{
		handle_quotes(token[i], &qs, &qd);
		if (!qs && token[i] == '$')
		{
			if ((token[i + 1] == '"' || token[i + 1] == '\'')
				&& ft_strchr(" \t\n", token[i + 2]))
				i++;
			else if (!ft_strchr(" \t\n", token[i + 1]))
				(*nbr)++;
		}
		i++;
	}
	return (*nbr);
}

char	*creates_new_aux(char *token, t_env *env, t_env *var, int *nbr)
{
	char	*s;
	char	*f;
	char	*n;
	char	*name;

	n = ft_strdup(token, 0);
	while (*nbr > 0)
	{
		name = var_name_exp(n);
		var = find_env_var(&env, name);
		free(name);
		s = from_var_name_to_end(n);
		f = from_beginning_to_dollar(n);
		free(n);
		if (var)
			n = ft_strdup(ft_strjoin(ft_strjoin(f, var->content, 3), s, 15), 1);
		else
			n = ft_strdup(ft_strjoin(f, s, 15), 1);
		(*nbr)--;
	}
	return (n);
}

char	*creates_new(char *token, t_env *env)
{
	int		nbr;
	t_env	*var;

	nbr = 0;
	var = NULL;
	if (check_expand_needed(token, &nbr))
	{
		token = creates_new_aux(token, env, var, &nbr);
	}
	else
		token = ft_strdup(token, 0);
	return (token);
}

char	**expand_vars(char **tokens, t_env *env)
{
	int		i;
	int		arraylen;
	char	**new;

	i = 0;
	arraylen = ft_arraylen(tokens);
	new = malloc(sizeof(char *) * (arraylen + 1));
	if (!new)
		return (NULL);
	while (tokens[i] != NULL)
	{
		new[i] = creates_new(tokens[i], env);
		i++;
	}
	new[i] = NULL;
	free_array(tokens);
	return (new);
}
