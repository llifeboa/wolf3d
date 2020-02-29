/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 04:38:27 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/14 04:38:29 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int		i;
	int		j;
	int		k;
	int		good;

	if (!ft_strlen(needle))
		return ((char *)haystack);
	i = -1;
	good = 0;
	while (*(haystack + ++i) && !good)
	{
		if (*(haystack + i) == *(needle + 0))
		{
			j = 0;
			k = i;
			good = 1;
			while (*(needle + j))
				if (*(needle + j++) != *(haystack + k++))
					good = 0;
			if (good)
				return ((char *)haystack + i);
		}
	}
	return (0);
}
