/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:05 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/07 15:11:26 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//TO DO AÑADIR VARIABLE DE ENTORNO ? LLAMADA CON $? QUE ALMACENA SALIDA DE ERROR
//DEL ULTIMO COMANDO EJECUTADO

int	check_expand_needed(char *token)
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
			if (token[i + 1] == '"')
				return (FALSE);
			else if (!ft_strchr(" \t\n", token[i + 1]))
				return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

char	*creates_new(char *token, t_env *env)
{
	char	*name;
	char	*first;
	char	*sec;
	t_env	*var;

	if (check_expand_needed(token) == TRUE)
	{
		name = var_name_exp(token);
		var = find_env_var(&env, name);
		free(name);
		sec = from_var_name_to_end(token);
		first = from_beginning_to_dollar(token);
		if (var)
			return (ft_strjoin(ft_strjoin(first, var->content, 3), sec, 15));
		else
			return (ft_strjoin(first, sec, 15));
	}
	else
		token = ft_strdup(token);
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
