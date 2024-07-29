/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   06_add_spaces_tokenizer.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 21:06:45 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/29 16:17:48 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//handle quote status
void	handle_quotes(char c, int *sq, int *dq)
{
    if (c == '\'' && !(*dq))
        *sq = !(*sq);
	else if (c == '"' && !(*sq))
        *dq = !(*dq);
}

//auxiliary
int add_spaces_aux(char *input, char *result, int i, int j)
{
    if (i > 0 && result[j - 1] != ' ')
        result[j++] = ' ';
    result[j++] = input[i];
    if ((input[i] == '>' || input[i] == '<') && input[i + 1] == input[i])
        result[j++] = input[++i];
    if (input[i + 1] != ' ' && input[i + 1] != '\0')
        result[j++] = ' ';
    return j;
}

//adds spaces to separate operators |, <<, >>, <, >
char	*add_spaces_tokenizer(char *input, int i, int j, int len)
{
	char	*new;
	int	sq;
	int	dq;

	sq = 0; //simple
	dq = 0; //double
	new = malloc(sizeof(char) * (len * 2));
	if (!new)
		return (NULL);
	while (i < len)
	{
		handle_quotes(input[i], &sq, &dq);
        if (!sq && !dq && ft_strchr("|<>", input[i]))
		{
            j = add_spaces_aux(input, new, i, j);
            if (ft_strchr("|<>", input[i]) && input[i+1] == input[i])
                i++;
        }
		else
            new[j++] = input[i];
        i++;
    }
    new[j] = '\0';
	return (new);
}
