/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 21:02:27 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/11 21:02:28 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

t_wall_info		get_wall_info(t_main *main,
					t_vec3 ray, t_vec3 intersection, int h_or_v)
{
	unsigned int	texture_id;
	int				side;

	if (h_or_v)
	{
		side = ray.z > 0 ? WALL_FRONT : WALL_BACK;
		texture_id = ray.z > 0 ?
			main->map->map_cells[(int)(intersection.z + ray.z) / 64]
				[(int)intersection.x / 64].front :
			main->map->map_cells[(int)(intersection.z + ray.z) / 64]
				[(int)intersection.x / 64].back;
	}
	else
	{
		side = ray.x > 0 ? WALL_LEFT : WALL_RIGHT;
		texture_id = ray.x > 0 ?
		main->map->map_cells[(int)(intersection.z) / 64]
			[(int)(intersection.x + ray.x) / 64].left :
		main->map->map_cells[(int)(intersection.z) / 64]
				[(int)(intersection.x + ray.x) / 64].right;
	}
	if (!main->images.textures[texture_id])
		texture_id = 2;
	return (t_wall_info){main->images.textures[texture_id], side};
}

t_vec3			intersection_vertical(t_main *main,
					t_vec3 origin, t_vec3 direction)
{
	t_intersection data;

	data.dir = direction.x > 0 ? 1 : -1;
	data.x = (((int)origin.x / 64) + (data.dir > 0 ? 1 : 0)) * 64;
	data.point_1 = (data.x - origin.x) * direction.z / direction.x + origin.z;
	if (data.point_1 > (main->map->height - 1) * 64 || data.point_1 < 64)
		return (t_vec3){data.x, 32, data.point_1};
	if (main->map->map_cells[(int)(data.point_1 / 64)]
			[(int)((data.x + data.dir) / 64)].front > 0)
		return (t_vec3){data.x, 32, data.point_1};
	data.x += 64 * data.dir;
	data.point_2 = (data.x - origin.x) * direction.z / direction.x + origin.z;
	data.step = data.point_2 - data.point_1;
	if (data.point_2 > (main->map->height - 1) * 64 || data.point_2 < 64)
		return (t_vec3){data.x, 32, data.point_2};
	while (!(main->map->map_cells[(int)(data.point_2 / 64)]
		[(int)((data.x + data.dir) / 64)].front))
	{
		data.point_2 += data.step;
		data.x += 64 * data.dir;
		if (data.point_2 > (main->map->height - 1) * 64 || data.point_2 < 65)
			break ;
	}
	return (t_vec3){data.x, 32, data.point_2};
}

t_vec3			intersection_horizontal(t_main *main,
					t_vec3 origin, t_vec3 direction)
{
	t_intersection data;

	data.dir = direction.z > 0 ? 1 : -1;
	data.x = (((int)origin.z / 64) + (data.dir > 0 ? 1 : 0)) * 64;
	data.point_1 = (data.x - origin.z) * direction.x / direction.z + origin.x;
	if (data.point_1 > (main->map->width - 1) * 64 || data.point_1 < 64)
		return (t_vec3){data.point_1, 32, data.x};
	if (main->map->map_cells[(int)((data.x + data.dir) / 64)]
			[(int)(data.point_1 / 64)].front > 0)
		return (t_vec3){data.point_1, 32, data.x};
	data.x += 64 * data.dir;
	data.point_2 = (data.x - origin.z) * direction.x / direction.z + origin.x;
	if (data.point_2 > (main->map->width - 1) * 64 || data.point_2 < 64)
		return (t_vec3){data.point_2, 32, data.x};
	data.step = data.point_2 - data.point_1;
	while (!main->map->map_cells[(int)((data.x + data.dir) / 64)]
		[(int)(data.point_2 / 64)].front)
	{
		data.point_2 += data.step;
		data.x += 64 * data.dir;
		if (data.point_2 > (main->map->width - 1) * 64 || data.point_2 < 64)
			break ;
	}
	return (t_vec3){data.point_2, 32, data.x};
}
