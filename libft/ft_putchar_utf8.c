/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_utf8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 23:20:46 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/11 23:20:48 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		set_octets_mask(char *octets, int len)
{
	if (len == 1)
		octets[0] = 0;
	else if (len == 2)
	{
		octets[0] = 0b11000000;
		octets[1] = 0b10000000;
	}
	else if (len == 3)
	{
		octets[0] = 0b11100000;
		octets[1] = 0b10000000;
		octets[2] = 0b10000000;
	}
	else if (len == 4)
	{
		octets[0] = 0b11100000;
		octets[1] = 0b10000000;
		octets[2] = 0b10000000;
	}
}

static int		set_octets(char *octets, int c)
{
	int len;

	if (c >= 0x0 && c <= 0x7F)
		len = 1;
	else if (c >= 0x80 && c <= 0x7FF)
		len = 2;
	else if (c >= 0x800 && c <= 0xFFFF)
		len = 3;
	else if (c >= 0x10000 && c <= 0x10FFFF)
		len = 4;
	else
		return (0);
	set_octets_mask(octets, len);
	return (len);
}

static void		display(char *octets, int fd, int len)
{
	int i;

	i = 0;
	while (i < len)
	{
		write(fd, &octets[i], 1);
		i++;
	}
}

void			ft_putchar_utf8(int c, int fd)
{
	int		len;
	char	octets[4];

	len = set_octets(octets, c);
	if (len == 1)
		octets[0] = c;
	else if (len == 2)
	{
		octets[0] = octets[0] | ((c >> 6) & 0b00011111);
		octets[1] = octets[1] | (c & 0b00111111);
	}
	else if (len == 3)
	{
		octets[0] = octets[0] | ((c >> 12) & 0b00001111);
		octets[1] = octets[1] | ((c >> 6) & 0b00111111);
		octets[2] = octets[2] | (c & 0b00111111);
	}
	else if (len == 4)
	{
		octets[0] = octets[0] | ((c >> 18) & 0b00000111);
		octets[1] = octets[1] | ((c >> 12) & 0b00111111);
		octets[2] = octets[2] | ((c >> 6) & 0b00111111);
		octets[3] = octets[3] | (c & 0b00111111);
	}
	display(octets, fd, len);
}
