/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 07:42:15 by llifeboa          #+#    #+#             */
/*   Updated: 2019/09/09 08:31:31 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned long	res;
	char			sign;
	int				i;

	sign = 1;
	res = 0;
	i = -1;
	while ((*(str + ++i) >= 9 && *(str + i) <= 13) || *(str + i) == ' ')
		;
	if (*(str + i) == '-' || *(str + i) == '+')
		if (*(str + i++) == '-')
			sign = -sign;
	while (ft_isdigit(*(str + i)))
	{
		res = res * 10 + *(str + i++) - 48;
		if (res >= 9223372036854775808U && sign < 0)
			return (0);
		if (res > 9223372036854775807U)
			return (-1);
	}
	return (res * sign);
}
