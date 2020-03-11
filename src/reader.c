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

t_map			*add_new_line_to_map(t_map_cell *line, t_map *map)
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

void			get_properties(t_map *map, char *line, int *h)
{
	map->height = 1;
	*h = get_height();
	map->width = get_word_count(line, ' ');
}

void			map_filler(t_map *map, char *line, int h)
{
	t_map_cell *points;

	points = h == map->height ?
		line_to_point_array(1, line, map->width) :
		line_to_point_array(2, line, map->width);
	map = add_new_line_to_map(points, map);
	map->height += 1;
}

void			player_find(t_map *map, char *line, int h, int *check)
{
	if (*check == 1)
		exit_with_error("error: invalid map\n");
	*check = 1;
	map->player_pos = get_pos(map, line);
	map_filler(map, line, h);
}

t_map			*get_map_from_file(int fd)
{
	char		*line;
	t_map		*map;
	int			h;
	int			check;

	malloc_check(map = (t_map*)malloc(sizeof(t_map)));
	if ((get_next_line(fd, &line)) == -1)
		exit_with_error("error: file didnt open");
	get_properties(map, line, &h);
	map_filler(map, line, h);
	check = 0;
	while (get_next_line(fd, &line))
	{
		if (!ft_strchr(line, 'p'))
			map_filler(map, line, h);
		else
			player_find(map, line, h, &check);
	}
	free(line);
	map->height -= 1;
	map_validation(map, check);
	return (map);
}
