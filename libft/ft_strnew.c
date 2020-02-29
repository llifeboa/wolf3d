/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/14 05:02:31 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/14 05:02:35 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnew(size_t size)
{
	char	*str;

	if (size == 18446744073709551615U)
		return (0);
	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	ft_bzero(str, size + 1);
	return (str);
}
