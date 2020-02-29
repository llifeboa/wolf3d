/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 13:25:10 by llifeboa          #+#    #+#             */
/*   Updated: 2019/10/14 05:35:15 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>

static int		line_filler(char *str, char **line)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	i = 0;
	if (ft_strchr(str, 10))
	{
		tmp = ft_strdup(str);
		ft_strcpy(str, ft_strchr(str, 10) + 1);
		while (tmp[i] != '\n' && tmp[i] != 0)
			i++;
		tmp[i] = tmp[i] == 10 ? 0 : tmp[i];
		tmp2 = *line;
		*line = ft_strjoin(*line, tmp);
		free(tmp);
		free(tmp2);
		return (1);
	}
	tmp = *line;
	*line = ft_strjoin(*line, str);
	free(tmp);
	ft_bzero(str, BUFF_SIZE);
	return (0);
}

int				get_next_line(const int fd, char **line)
{
	static char		*buf[15000];

	if (fd < 0 || fd > 15000 || line == NULL ||
			BUFF_SIZE <= 0 || read(fd, buf[fd], 0) < 0)
		return (-1);
	if (!buf[fd])
		buf[fd] = ft_strnew(BUFF_SIZE);
	*line = ft_strnew(0);
	if (*buf[fd])
		if (line_filler(buf[fd], line))
			return (1);
	ft_bzero(buf[fd], BUFF_SIZE);
	while (read(fd, buf[fd], BUFF_SIZE))
		if (line_filler(buf[fd], line))
			return (1);
	return (**line == 0 ? 0 : 1);
}
