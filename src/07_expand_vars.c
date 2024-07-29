/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   07_expand_vars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 14:56:05 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/29 16:24:32 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>

//TO DO AÑADIR VARIABLE DE ENTORNO ? LLAMADA CON $? QUE ALMACENA SALIDA DE ERROR DEL ULTIMO COMANDO EJECUTADO

int	check_expand_needed(char **tokens)
{
	int	i;
	int	j;

	j = 0;
	while (tokens[j] != NULL)
	{
		i = 0;
		{
			while (tokens[j][i] != '\0')
			{
				if (tokens[j][i] == '$' && !ft_strchr("'\" \t\n\0", tokens[j][i + 1]))
					return (TRUE);
				i++;
			}
		}
		j++;
	}
	return (FALSE);
}

void	start_expand_vars(char **tokens, t_env *env)
{
	int	i;
	int	j;
	int	sq;
	int	dq;

	i = 0;
	j = 0;
	sq = 0;
	dq = 0;
	while ()

}

void	expand_vars(char **tokens, t_env *env)
{
	if (check_expand_needed(tokens) == TRUE)
		start_expand_vars(tokens, env);

}