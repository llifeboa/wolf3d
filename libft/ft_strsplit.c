/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 06:27:09 by llifeboa          #+#    #+#             */
/*   Updated: 2019/04/15 06:27:11 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		**ft_free_array(char **s, size_t n)
{
	size_t i;

	i = -1;
	if (n != 0)
		while (++i < n)
			free(s[n]);
	free(s);
	return (0);
}

static size_t	ft_splitone(char **newstr, const char *s, char c)
{
	size_t i;

	i = -1;
	while (*(s + ++i) != c && *(s + i) != 0)
		;
	*newstr = ft_strnew(i);
	if (!*newstr)
		return (0);
	ft_strncpy(*newstr, s, i);
	return (i);
}

static size_t	strcount(char const *s, char c)
{
	size_t	flag;
	size_t	in;
	size_t	i;

	in = 0;
	i = -1;
	flag = 0;
	while (*(s + ++i))
	{
		if (*(s + i) != c && flag == 0)
		{
			flag = 1;
			in++;
		}
		if (*(s + i) == c)
			flag = 0;
	}
	return (in);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**array;
	size_t	in;
	size_t	i;
	size_t	flag;

	if (!s)
		return (0);
	in = strcount(s, c);
	i = 0;
	if (!(array = (char**)malloc(sizeof(char*) * (in + 1))))
		return (0);
	array[in] = 0;
	in = 0;
	while (*(s + i))
	{
		if (*(s + i) != c)
		{
			flag = ft_splitone(&array[in++], s + i, c);
			if (!flag)
				return (ft_free_array(array, in));
			i += (*(s + i + flag) == 0) ? flag - 1 : flag;
		}
		i++;
	}
	return (array);
}
