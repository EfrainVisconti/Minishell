/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:17:11 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/10 18:35:39 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2, int mode)
{
	char			*res;
	unsigned int	i;
	unsigned int	j;

	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	i = 0;
	j = 0;
	if (res == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		res[i + j] = s2[j];
		j++;
	}
	res[i + j] = '\0';
	if (mode % 3 == 0)
		free((char *)s1);
	if (mode % 5 == 0)
		free((char *)s2);
	return (res);
}
