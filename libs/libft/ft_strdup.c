/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eviscont <eviscont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 13:12:25 by eviscont          #+#    #+#             */
/*   Updated: 2024/08/07 17:55:50 by eviscont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s, int mode)
{
	size_t	i;
	size_t	size;
	char	*d;

	i = 0;
	size = ft_strlen((char *)s) + 1;
	d = (char *)malloc(size);
	if (d == 0)
		return (NULL);
	while (s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	d[i] = '\0';
	if (mode == 1)
		free((char *)s);
	return (d);
}
