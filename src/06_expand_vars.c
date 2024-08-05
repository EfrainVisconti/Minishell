/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:05 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/05 20:39:41 by eviscont         ###   ########.fr       */
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
		if (!qs && token[i] == '$' && !ft_strchr(" \t\n\0", token[i + 1]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*creates_new(char *token, t_env *env)
{
	char	*name;
	char	*first;
	char	*second;
	t_env	*var;

	if (check_expand_needed(token) == TRUE)
	{
		name = var_name_exp(token);
		var = find_env_var(&env, name);
		free(name);
		second = from_var_name_to_end(token);
		first = from_beginning_to_dollar(token);
		ft_printf("%s\n", token);
		ft_printf("%s\n", first);
		ft_printf("%s\n", name);
		ft_printf("%s\n", second);
		if (var)
			return (ft_strjoin(ft_strjoin(first, var->content, 3), second, 15));
		else
			return (ft_strjoin(first, second, 15));
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
	new = malloc(sizeof(char *) * arraylen + 1);
	if (!new)
		return (NULL);
	while (tokens[i] != NULL)
	{
		new[i] = creates_new(tokens[i], env);
		i++;
	}
	new[arraylen] = NULL;
	free_array(tokens);
	return (new);
}
