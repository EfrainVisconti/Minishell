/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 12:12:13 by eviscont          #+#    #+#             */
/*   Updated: 2024/07/30 16:34:25 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_error(int id)
{
	if (id == 1)
		ft_putstr_fd("error: open quotes\n", 2);
	if (id == 2)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	if (id == 3)
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	if (id == 4)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
}

int	ft_arraylen(char **array)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (array[i++] != NULL)
		len++;
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	idx;

	idx = 0;
	while ((s1[idx] == s2[idx]) && (s1[idx] != '\0' && s2[idx] != '\0'))
		idx++;
	return ((unsigned char)s1[idx] - (unsigned char)s2[idx]);
}

char	*ft_strcpy(char	*s1, char *s2)
{
	int i;

	i = 0;
	while (s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
