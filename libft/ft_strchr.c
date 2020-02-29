/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:47:20 by llifeboa          #+#    #+#             */
/*   Updated: 2019/07/29 22:24:33 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	size_t	len;

	i = -1;
	len = ft_strlen(s);
	while (++i < len + 1)
	{
		if (*(s + i) == (char)c)
			return ((char *)s + i);
	}
	return (0);
}
