/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 05:12:41 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/14 05:12:43 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;
	size_t		k;
	int			found;

	i = -1;
	found = 1;
	if (!ft_strlen(needle))
		return ((char *)haystack);
	while (*(haystack + ++i) && i < len)
	{
		j = 0;
		if (*(haystack + i) == *(needle + 0))
		{
			k = i;
			found = 1;
			while (*(haystack + k) && *(needle + j) && j < len && k < len)
				if (*(haystack + k++) != *(needle + j++))
					found = 0;
			if (found && !*(needle + j))
				return ((char *)haystack + i);
		}
	}
	return (0);
}
