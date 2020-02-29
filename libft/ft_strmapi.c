/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 06:05:32 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/14 06:05:33 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		*(new + i) = f(i, *(s + i));
	return (new);
}
