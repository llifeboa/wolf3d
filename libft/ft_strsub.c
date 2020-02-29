/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:31:42 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/12 05:31:44 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*sub;

	i = start;
	sub = 0;
	if (s)
	{
		sub = ft_strnew(len);
		if (sub)
		{
			while (i < start + len)
			{
				sub[i - start] = s[i];
				i++;
			}
			return (sub);
		}
	}
	return (0);
}
