/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 06:58:44 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/12 06:58:46 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	unsigned int	i;
	unsigned int	slen;
	unsigned int	start;
	unsigned int	end;
	char			*str;

	if (!s)
		return (0);
	if (!(*s))
		return (ft_strnew(0));
	slen = ft_strlen(s);
	start = 0;
	end = slen;
	i = 0;
	while (s[start] == ' ' || s[start] == '\n' || s[start] == '\t')
		if (!s[++start])
			break ;
	while (s[end] == ' ' || s[end] == '\n' || s[end] == '\t' || !s[end])
		if (--end <= 0)
			break ;
	str = ft_strnew(start > end ? 0 : end - start + 1);
	if (str && start <= end)
		while (start + i++ <= end)
			str[i - 1] = s[start + i - 1];
	return (str);
}
