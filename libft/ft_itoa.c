/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 08:31:41 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/14 08:31:42 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		itoaiter(char *s, long a, int pos)
{
	s[pos] = (a % 10) + 48;
	return (a / 10);
}

char			*ft_itoa(int n)
{
	int		len;
	char	*str;
	int		i;
	long	buf;

	i = n < 0 ? 1 : 0;
	len = ft_intlen(n);
	buf = n < 0 ? (long)n * -1 : (long)n;
	str = ft_strnew(len);
	if (str)
	{
		if (i)
			str[0] = '-';
		while (i - 1 != --len)
			buf = itoaiter(str, buf, len);
		return (str);
	}
	return (0);
}
