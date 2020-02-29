/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:03:59 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/14 06:04:01 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*new;
	int		i;

	if (!s || !f)
		return (0);
	new = ft_strnew(ft_strlen(s));
	if (!new)
		return (0);
	i = -1;
	while (*(s + ++i))
		*(new + i) = f(*(s + i));
	return (new);
}
