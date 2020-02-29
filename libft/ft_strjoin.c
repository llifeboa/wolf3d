/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 05:44:51 by llifeboa          #+#    #+#             */
/*   Updated: 2019/09/08 06:44:35 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			len1;
	size_t			len2;
	char			*new;
	unsigned int	i;

	i = -1;
	if (s1 && s2)
	{
		len1 = ft_strlen(s1);
		len2 = ft_strlen(s2);
		new = ft_strnew(len1 + len2);
		if (new)
		{
			while (++i < len1)
				new[i] = s1[i];
			i = -1;
			while (++i < len2)
				new[len1 + i] = s2[i];
			return (new);
		}
	}
	return (0);
}
