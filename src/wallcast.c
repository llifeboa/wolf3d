/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wallcast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 21:47:20 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/11 21:47:22 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	walls_helper(t_main *main, t_wall *data, int i)
{
	data->h_intersect = intersection_horizontal(main, main->position,
											data->ray);
	data->v_intersect = intersection_vertical(main, main->position,
											data->ray);
	data->fish_eye_fix = fish_eye((t_vec3){0, 0, 1},
								(t_vec3){data->cur, 0, 1});
	data->h_intersect_1 = data->h_intersect;
	data->v_intersect_1 = data->v_intersect;
	data->h_intersect = vec3_sub(data->h_intersect, main->position);
	data->v_intersect = vec3_sub(data->v_intersect, main->position);
	data->length_h = sqrtf(data->h_intersect.x * data->h_intersect.x +
				data->h_intersect.z * data->h_intersect.z);
	data->length_v = sqrtf(data->v_intersect.x * data->v_intersect.x +
				data->v_intersect.z * data->v_intersect.z);
	data->length = (data->length_h > data->length_v ?
			data->length_v : data->length_h) * data->fish_eye_fix;
	data->h_or_v = (data->length_h > data->length_v ? 0 : 1);
	data->intersection = data->length_h > data->length_v ?
		data->v_intersect_1 : data->h_intersect_1;
	main->intersections[i] = data->intersection;
	data->length_wall_o = (int)(main->height / (data->length / 64));
	data->length_wall_p = data->length_wall_o > main->height ?
					main->height : data->length_wall_o;
	data->start_paint = (main->height - data->length_wall_p) / 2;
}

void	walls_filler(t_main *main, t_wall *data, int i, int j)
{
	if (data->wall_info.side == WALL_BACK ||
			data->wall_info.side == WALL_FRONT)
		data->color =
			data->src[(int)((((data->length_wall_o - data->length_wall_p) /
			2 + (float)j) / data->length_wall_o * 64.0)) * 64 +
			(data->wall_info.side == WALL_BACK ?
				63 - (((int)(data->intersection.x) % 64)) :
				((int)(data->intersection.x) % 64))];
	else
		data->color =
			data->src[(int)((((data->length_wall_o - data->length_wall_p) /
				2 + (float)j) / data->length_wall_o * 64.0)) * 64 +
			(data->wall_info.side == WALL_LEFT ?
				63 - (((int)(data->intersection.z) % 64)) :
				((int)(data->intersection.z) % 64))];
	data->dist[(data->start_paint + j) * main->sur->w + i] = data->color;
}

void	walls(t_main *main, float cos, float sin)
{
	int			i;
	int			j;
	t_wall		*data;

	i = -1;
	malloc_check((data = (t_wall *)malloc(sizeof(t_wall))));
	data->step = main->aspect_ratio / main->width;
	data->cur = -main->aspect_ratio / 2;
	while (++i < main->width)
	{
		data->ray = rotate_y((t_vec3){data->cur, 32, 1}, cos, sin);
		walls_helper(main, data, i);
		data->dist = (int*)(main->sur->pixels);
		data->wall_info = get_wall_info(main, data->ray,
							data->intersection, data->h_or_v);
		data->src = (int*)(data->wall_info.texture->pixels);
		j = -1;
		while (++j < data->length_wall_p)
			walls_filler(main, data, i, j);
		data->cur += data->step;
	}
	free(data);
	print_map(main);
}
