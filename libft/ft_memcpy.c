/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 12:13:55 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/14 03:32:22 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst2;
	char	*src2;

	if (!dst && !src)
		return (0);
	dst2 = (char *)dst;
	src2 = (char *)src;
	i = 0;
	while (++i <= n)
		*(dst2 + i - 1) = *(src2 + i - 1);
	return (dst);
}
