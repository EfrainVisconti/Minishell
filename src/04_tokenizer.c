/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_tokenizer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 21:35:30 by usuario           #+#    #+#             */
/*   Updated: 2024/07/25 22:06:33 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	count_tokens(char *s)
{
	int		q[2];
	int		i[2];

	q[0] = 0;
	q[1] = 0;
	i[0] = 0;
	i[1] = 0;
	while (s[i[0]] != '\0')
	{
		if (!ft_strchr(" \t\r\n\v", s[i[0]]))
		{
			i[1]++;
			while ((!ft_strchr(" \t\r\n\v", s[i[0]]) || q[0]) && s[i[0]] != '\0')
			{
				if (!q[1] && (s[i[0]] == '\"' || s[i[0]] == '\''))
					q[1] = s[i[0]];
				q[0] = (q[0] + (s[i[0]] == q[1])) % 2;
				q[1] *= q[0] != 0;
				i[0]++;
			}
		}
		else
			i[0]++;
	}
	return (i[1]);
}

// // tokenize command line input
// void	tokens_init(t_minishell *mini)
// {
// 	char	*input;
// 	char	**tokens;

// 	input = mini->input;


// }