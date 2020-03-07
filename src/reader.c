/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 19:19:16 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/05 13:35:45 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void			map_validation(t_map *map)
{
	if (map->height < 3 || map->width < 3)
		exit_with_error("error: invalid map!\n");
}

static void			free_split(char **split)
{
	int i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

static t_vec3		get_pos(t_map *map, char *line)
{
	t_vec3 pos;
	char **find_player;
	int x;

	find_player = ft_strsplit(line, ' ');
	x = 0;
	while (find_player[x])
	{
		if (find_player[x][0] == 'p')
			break ;
		x++;
	}
	pos.x = x;
	pos.y = 1;
	pos.z = map->height;
	free_split(find_player);
	return (pos);
}

/*
**	int check_elem(char *s, int wc)
**	s - current elem
**	wc - elements count
*/

static int			check_elem(char *s, int wc)
{
	char	**elem;
	int		i;
	int		value;
	int		check;

	elem = ft_strsplit(s, ',');
	malloc_check(elem);
	i = 0;
	check = 1;
	if (wc == 1)
	{
		if (elem[i][0] != 'p')
			value = ft_atoi_with_non_digit_error(elem[i]);
		if (!(value >= 0 && value <= 10) || !(value != 112))
			check = 0;
	}
	else
	{
		while (i < wc)
		{
			value = ft_atoi_with_non_digit_error(elem[i]);
			if (!(value > 0 && value <= 10))
				check = 0;
			i++;
		}
	}
	free_split(elem);
	return (check);
}

/*
**	int check_line(char **str, int flag, int w_count)
**		str - array from split
**		flag - option for start/middle/end line
**	 		1 = start/end
**			2 = middle
**		w_count - count of elements
*/

static int			check_line(char **str, int flag, int w_count)
{
	int i;

	i = 0;
	if (flag == 1)
		while (str[i])
		{
			if (ft_atoi_with_non_digit_error(str[i]) == 0 || str[i][0] == 'p')
				return (0);
			i++;
		}
	else if (flag == 2)
		if (ft_atoi_with_non_digit_error(str[i]) == 0 ||
			ft_atoi_with_non_digit_error(str[w_count - 1]) == 0 ||
			str[i][0] == 'p' || str[w_count - 1][0] == 'p')
			return (0);
	return (1);
}

/*
**	int get_height(char *filename)
*/

static int			get_height(void)
{
	int		fd;
	int		h;
	int		gnl;
	char	*line;

	h = 0;
	fd = open("./maps/level1.map", O_RDONLY);
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

static int			get_word_count(char *line, char sep)
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

void				push_elem(char **z, t_map_cell *points)
{
	int		i;
	int		wc;
	char	**elem;

	i = -1;
	while (z[++i])
	{
		wc = get_word_count(z[i], ',');
		if (wc == 1 && check_elem(z[i], wc))
		{
			points[i].front = ft_atoi_with_non_digit_error(z[i]);
			points[i].back = ft_atoi_with_non_digit_error(z[i]);
			points[i].left = ft_atoi_with_non_digit_error(z[i]);
			points[i].right = ft_atoi_with_non_digit_error(z[i]);
		}
		else if (wc == 1 && z[i][0] == 'p')
		{
			points[i].front = 0;
			points[i].back = 0;
			points[i].left = 0;
			points[i].right = 0;
		}
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
		// free(z[i]);
	}
}

static t_map_cell	*line_to_point_array(int flag, char *line, int word_count)
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

static t_map		*add_new_line_to_map(t_map_cell *line, t_map *map)
{
	t_map_cell	**new_map;
	int			i;

	i = 0;
	if (map->height == 1)
	{
		map->map_cells = (t_map_cell**)
		malloc(sizeof(t_map_cell*));
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

t_map				*get_map_from_file(int fd)
{
	char		*line;
	int			gnl_res;
	t_map		*map;
	t_map_cell	*points;
	int			h;
	int			check;

	malloc_check(map = (t_map*)malloc(sizeof(t_map)));
	map->height = 1;
	h = get_height();
	if ((gnl_res = get_next_line(fd, &line)) == -1)
		exit_with_error("error: file didnt open");
	map->width = get_word_count(line, ' ');
	points = line_to_point_array(1, line, map->width);
	map = add_new_line_to_map(points, map);
	map->height += 1;
	check = 0;
	while ((gnl_res = get_next_line(fd, &line)))
	{
		if (!ft_strchr(line, 'p'))
		{
			points = h == map->height ? line_to_point_array(1, line, map->width) :
			line_to_point_array(2, line, map->width);
			map = add_new_line_to_map(points, map);
			map->height += 1;
		}
		else
		{
			if (check == 1)
				exit_with_error("error: invalid map 1\n");
			check = 1;
			map->player_pos = get_pos(map, line);
			points = line_to_point_array(2, line, map->width);
			map = add_new_line_to_map(points, map);
			map->height += 1;
		}
	}
	free(line);
	map->height -= 1;
	map_validation(map);
	return (map);
}
