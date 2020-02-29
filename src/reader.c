/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:19:16 by llifeboa          #+#    #+#             */
/*   Updated: 2020/02/26 22:17:00 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

/*
	** int check_line(char **str, int flag, int w_count)
	** str - array from split
	** flag - option for start/middle/end line
	** 		1 = start/end
	**		2 = middle
	**	w_count - count of elements
*/

static int					check_line(char **str, int flag, int w_count)
{
	int i;
	int num = 

	i = 0;
	if (flag == 1)
		while (str[i])
		{
			if (ft_atoi_with_non_digit_error(str[i]) == 0)
				return (0);
			i++;
		}
	else if (flag == 2)
		if (ft_atoi_with_non_digit_error(str[i]) == 0 || ft_atoi_with_non_digit_error(str[w_count - 1]) == 0)
			return (0);
	return (1);
}
/*
	** int get_height(char *filename)
*/

static int					get_height()
{
	int fd;
	int h;
	int	gnl;
	char *line;

	h = 0;
	fd = open("./maps/level1.map", O_RDONLY);
	while ((gnl = get_next_line(fd, &line)))
	{
		if (gnl < 0)
			exit_with_error("error: file didnt open");
		h++;
	}
	return (h);
}

static int			get_word_count(char *line)
{
	int	word_count;
	int	flag;

	flag = 0;
	word_count = 0;
	while (*line)
	{
		if (*line != ' ' && !flag)
		{
			word_count++;
			flag = 1;
		}
		if (*line == ' ')
			flag = 0;
		line++;
	}
	return (word_count);
}

static t_map_cell	*line_to_point_array(int flag, char *line, int word_count)
{
	int			cur_word_count;
	char		**z;
	t_map_cell	*points;
	int			i;

	i = -1;
	cur_word_count = get_word_count(line);
	if (cur_word_count != word_count)
		exit_with_error("error: wrond map");
	z = ft_strsplit(line, ' ');
	malloc_check(z);
	free(line);
	if (!check_line(z, flag, word_count))
		exit_with_error("error: map error");
	points = (t_map_cell*)malloc(sizeof(t_map_cell) * (word_count + 1));
	malloc_check(points);
	while (z[++i])
	{
		points[i].front = ft_atoi_with_non_digit_error(z[i]);
		free(z[i]);
	}
	free(z);
	return (points);
}

static t_map	*add_new_line_to_map(t_map_cell *line, t_map *map)
{
	t_map_cell		**new_map;
	int			i;

	i = 0;
	if (map->height == 1)
	{
		map->map_cells = (t_map_cell**)malloc(sizeof(t_map_cell*) * map->height);
		malloc_check(map->map_cells);
		map->map_cells[0] = line;
	}
	else
	{
		new_map = (t_map_cell**)malloc(sizeof(t_map_cell*) * map->height);
		malloc_check(map->map_cells);
		while (i < map->height - 1)
		{
			new_map[i] = map->map_cells[i];
			i++;
		}
		new_map[i] = line;
		free(map->map_cells);
		map->map_cells = new_map;
	}
	return (map);
}

t_map		*get_map_from_file(int fd)
{
	char		*line;
	int			gnl_res;
	t_map		*map;
	t_map_cell		*points;
	int			h;

	malloc_check(map = (t_map*)malloc(sizeof(t_map)));
	map->height = 1;
	h = get_height();
	gnl_res = get_next_line(fd, &line);
	if (gnl_res == -1)
		exit_with_error("error: file didnt open");
	map->width = get_word_count(line);
	points = line_to_point_array(1, line, map->width);
	map = add_new_line_to_map(points, map);
	map->height += 1;
	while ((gnl_res = get_next_line(fd, &line)))
	{
		if (gnl_res == -1)
			exit_with_error("error: file didnt open");
		if (h == map->height)
			points = line_to_point_array(1, line, map->width);
		else
			points = line_to_point_array(2, line, map->width);
		map = add_new_line_to_map(points, map);
		printf("h = %d \t height = %d", h, map->height);
		map->height += 1;
	}
	free(line);
	map->height -= 1;
	return (map);
}
