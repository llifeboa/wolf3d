/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 19:04:32 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/11 19:04:33 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void		print_rect(t_main *main, t_vec3 p, t_vec3 s, float color)
{
	int *dist;
	int i;
	int j;

	dist = main->sur->pixels;
	i = 0;
	if (p.x > main->width)
		p.x = main->width - 1;
	else if (p.x < 0)
		p.x = 0;
	if (p.y > main->width)
		p.y = main->width - 1;
	else if (p.y < 0)
		p.y = 0;
	while (i < (int)(s.y))
	{
		j = 0;
		while (j < (int)(s.x))
		{
			dist[((int)p.y + i) * main->sur->w + (int)p.x + j] = color;
			j++;
		}
		i++;
	}
}

static void	minimap_draw(t_main *main, float size)
{
	int i;
	int j;

	i = 0;
	while (i < main->map->height)
	{
		j = 0;
		while (j < main->map->width)
		{
			print_rect(main,
			(t_vec3){j * size, i * size, 0},
			(t_vec3){size, size, 0},
			main->map->map_cells[i][j].front > 0 ? 0 : 0xffffff);
			j++;
		}
		i++;
	}
}

void		print_map(t_main *main)
{
	int		i;
	float	size;

	i = 0;
	size = 64 * main->minimap_scale;
	if (size < 0)
		size = 1;
	minimap_draw(main, size);
	print_rect(main, (t_vec3){main->position.x * main->minimap_scale,
	main->position.z * main->minimap_scale, 0}, (t_vec3){4, 4, 0}, 0xff0000);
	i = 0;
	while (i < main->width)
	{
		print_rect(main,
		(t_vec3){(int)main->intersections[i].x * main->minimap_scale,
		(int)main->intersections[i].z * main->minimap_scale, 0},
		(t_vec3){2, 2, 0}, 0xff00ff);
		i++;
	}
}
