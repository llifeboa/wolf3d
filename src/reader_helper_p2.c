/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_helper_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 02:11:33 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/12 02:11:34 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

/*
**	int get_height(char *filename)
*/

int				get_height(char *filename)
{
	int		fd;
	int		h;
	int		gnl;
	char	*line;

	h = 0;
	fd = open(filename, O_RDONLY);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl < 0)
			exit_with_error("error: file didnt open\n");
		if (line[0] == '\0')
			exit_with_error("error: invalid map\n");
		h++;
		free(line);
	}
	free(line);
	if (h == 0)
		exit_with_error("error: empty file\n");
	return (h);
}

int				get_word_count(char *line, char sep)
{
	int	word_count;
	int	flag;

	flag = 0;
	word_count = 0;
	while (*line)
	{
		if (*line != sep && !flag)
		{
			word_count++;
			flag = 1;
		}
		if (*line == sep)
			flag = 0;
		line++;
	}
	return (word_count);
}

void			elem_filler(t_map_cell *points, int value, int i)
{
	points[i].front = value;
	points[i].back = value;
	points[i].left = value;
	points[i].right = value;
}

void			push_elem(char **z, t_map_cell *points)
{
	int		i;
	int		wc;
	char	**elem;

	i = -1;
	while (z[++i])
	{
		wc = get_word_count(z[i], ',');
		if (wc == 1 && check_elem(z[i], wc))
			elem_filler(points, ft_atoi_with_non_digit_error(z[i]), i);
		else if (wc == 1 && z[i][0] == 'p')
			elem_filler(points, 0, i);
		else if (wc == 4 && check_elem(z[i], wc))
		{
			elem = ft_strsplit(z[i], ',');
			malloc_check(elem);
			points[i].front = ft_atoi_with_non_digit_error(elem[0]);
			points[i].back = ft_atoi_with_non_digit_error(elem[1]);
			points[i].left = ft_atoi_with_non_digit_error(elem[2]);
			points[i].right = ft_atoi_with_non_digit_error(elem[3]);
			free_split(elem);
		}
		else
			exit_with_error("error: wrong map");
	}
}

t_map_cell		*line_to_point_array(int flag, char *line, int word_count)
{
	int			cur_word_count;
	char		**z;
	t_map_cell	*points;

	cur_word_count = get_word_count(line, ' ');
	if (cur_word_count != word_count)
		exit_with_error("error: wrond map");
	z = ft_strsplit(line, ' ');
	malloc_check(z);
	free(line);
	if (!check_line(z, flag, word_count))
		exit_with_error("error: wrong map");
	points = (t_map_cell*)malloc(sizeof(t_map_cell) * (word_count + 1));
	malloc_check(points);
	push_elem(z, points);
	free_split(z);
	return (points);
}
