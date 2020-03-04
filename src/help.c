/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:25:26 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/03 00:06:02 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	exit_with_error(char *message)
{
	ft_putstr_fd(message, 2);
	exit(0);
}

void	malloc_check(void *data)
{
	if (data == NULL)
		exit_with_error("malloc error");
}

int		ft_atoi_with_non_digit_error(const char *str)
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
	if (i == 0 || (i == 1 && (*(str) == '-' ||
	*(str) == '+')) || (i == 2 && !ft_isdigit(*(str + 1))))
		exit_with_error("error: invalid map value");
	return (res * sign);
}
