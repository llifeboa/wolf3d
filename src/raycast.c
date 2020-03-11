/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:08:22 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/11 20:08:24 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	cast_helper(t_cast *cast, int j)
{
	cast->left_ray.origin = cast->data->main->position;
	cast->left_ray.direction = (t_vec3){-0.5 *
		cast->data->main->aspect_ratio, -0.5 +
		(float)(cast->data->main->height - cast->data->y + j) /
		cast->data->main->height, 1};
	cast->left_ray.direction = rotate_y(cast->left_ray.direction,
		*(cast->data->cos), *(cast->data->sin));
	cast->left_intersection = plane_intersection_opt(cast->left_ray);
	cast->right_ray.origin = cast->data->main->position;
	cast->right_ray.direction =
		(t_vec3){0.5 * cast->data->main->aspect_ratio,
		-0.5 + (float)(cast->data->main->height - cast->data->y + j) /
		cast->data->main->height, 1};
	cast->right_ray.direction =
		rotate_y(cast->right_ray.direction,
		*(cast->data->cos), *(cast->data->sin));
	cast->right_intersection = plane_intersection_opt(cast->right_ray);
	cast->step =
		vec3_div(vec3_sub(cast->right_intersection,
		cast->left_intersection),
		cast->data->main->width);
	cast->point = cast->left_intersection;
}

void	cast_color(t_cast *cast, int i, int j)
{
	cast->color = cast->src[64 * (63 - ((int)(cast->point.z > 0 ?
		cast->point.z : -cast->point.z) % 64)) +
		((int)(cast->point.x > 0 ?
		cast->point.x : -cast->point.x) % 64)];
	cast->dist[(cast->data->y - j) * cast->data->main->sur->w + i] =
		cast->color;
	cast->point.z += cast->step.z;
	cast->point.x += cast->step.x;
}

void	*cast_ray(void *param)
{
	int		i;
	int		j;
	t_cast	*cast;

	j = 0;
	malloc_check((cast = (t_cast *)malloc(sizeof(t_cast))));
	cast->data = (t_ray_data*)param;
	cast->dist = (int*)(cast->data->main->sur->pixels);
	cast->src = (int*)(cast->data->main->images.textures[1]->pixels);
	while (j < cast->data->main->step)
	{
		cast_helper(cast, j);
		i = 0;
		while (i < cast->data->main->width)
		{
			cast_color(cast, i, j);
			i++;
		}
		j++;
	}
	free(cast);
	pthread_exit(0);
}
