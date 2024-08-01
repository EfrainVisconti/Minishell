/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:05 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/01 15:16:52 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//TO DO AÑADIR VARIABLE DE ENTORNO ? LLAMADA CON $? QUE ALMACENA SALIDA DE ERROR
//DEL ULTIMO COMANDO EJECUTADO

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
		second = from_var_name_to_end(token);
		first = from_beginning_to_dollar(token);
		ft_printf("%s\n", token);
		ft_printf("%s\n", first);
		ft_printf("%s\n", name);
		ft_printf("%s\n", second);
		if (var)
			return (ft_strjoin(ft_strjoin(first, var->content, 2), second, 2));
		else
			return (ft_strjoin(first, second, 2));
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
	return (new);
}
