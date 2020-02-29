/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlenchar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 18:34:07 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/19 18:34:10 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strlenchar(const char *str, char fnd)
{
	int i;

	i = -1;
	while (*(str + ++i))
		if (*(str + i) == fnd)
			return (i);
	if (*(str + i) == fnd)
		return (i);
	return (-1);
}
