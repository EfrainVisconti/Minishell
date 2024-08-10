/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:05 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/10 18:35:49 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//TO DO AÑADIR VARIABLE DE ENTORNO ? LLAMADA CON $? QUE ALMACENA SALIDA DE ERROR
//DEL ULTIMO COMANDO EJECUTADO

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
			if ((token[i + 1] == '"' || token[i + 1] == '\'') && ft_strchr(" \t\n", token[i + 2]))
				i++;
			else if (!ft_strchr(" \t\n", token[i + 1]))
				(*nbr)++;
		}
		i++;
	}
	return (*nbr);
}

static char	*creates_new_aux(char *token, t_env *env, t_env *var, int *nbr)
{
	char	*sec;
	char	*first;
	char	*new;
	char	*name;

	new = ft_strdup(token, 0);
	while (*nbr > 0)
	{
		name = var_name_exp(new);
		var = find_env_var(&env, name);
		free(name);
		sec = from_var_name_to_end(new);
		first = from_beginning_to_dollar(new);
		free(new);
		if (var)
			new = ft_strdup(ft_strjoin(ft_strjoin(first, var->content, 3), sec, 15), 1);
		else
			new = ft_strdup(ft_strjoin(first, sec, 15), 1);
		(*nbr)--;
	}
	return (new);
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
