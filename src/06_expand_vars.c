/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:05 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/30 21:12:10 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//TO DO AÑADIR VARIABLE DE ENTORNO ? LLAMADA CON $? QUE ALMACENA SALIDA DE ERROR DEL ULTIMO COMANDO EJECUTADO

char	*from_var_name_to_end(char *s)
{
    int i;

	i = 0;
    while (s[i])
    {
        if (s[i] == '$')
		{
			i++;
			while (s[i] && s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
				i++;
			return (&s[i]);
		}
        i++;
    }
    return (NULL);
}

char	*from_beginning_to_dollar(char	*s)
{
	int	i;

	i = 0;
	while (s[i])
    {
        if (s[i] == '$')
		{
			s[i] = '\0';
			return (&s[i]);
		}
		i++;
	}
	return (NULL);
}

char *var_name_exp(char *s)
{
	int start;
    int i;

	start = 0;
	i = 0;
    while (s[i])
    {
        if (s[i] == '$')
		{
			i++;
			start = i;
			while (s[i] && s[i] != ' ' && s[i] != '\n' && s[i] != '\t')
				i++;
			s[i] = '\0';
			return &s[start];
		}
        i++;
    }
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
		if (!qd && token[i] == '$' && !ft_strchr(" \t\n\0", token[i + 1]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

char	*creates_new(char *token, t_env *env)
{
	char	*name;
	t_env	*var;

	if (check_expand_needed(token) == TRUE)
	{
		name = var_name_exp(token);
		var = find_env_var(&env, name);
		if (var)
			return ft_strjoin(from_beginning_to_dollar(token), var->content);
		else
			return ft_strjoin(from_beginning_to_dollar(token), var->content);
	}
	return (token);
}

char	**start_expand_vars(char **tokens, t_env *env)
{
	int	i;
	int	arraylen;
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

char	**expand_vars(char **tokens, t_env *env)
{
	int	i;
	char	**new;

	i = 0;
	while (tokens[i] != NULL)
	{
		if (check_expand_needed(tokens[i]) == TRUE)
		{
			new = start_expand_vars(tokens, env);
			break ;
		}
		i++;
	}
	return (new);
}