/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:38:51 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/07 22:01:52 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void			load_animations(t_main *main)
{
	load_animations_bow(main);
}

void			var_init(t_main *main)
{
	main->quit = 1;
	main->height = 1080;
	main->width = 1920;
	main->minimap_scale = 0.5;
	main->angle = 0;
	main->rotation_dir = 0;
	main->rotation_speed = 0.02;
	main->move_dir = 0;
	main->move_speed = 4;
	main->position = main->map->player_pos;
	main->forward_dir = (t_vec3){0, 0, 1};
	main->aspect_ratio = (float)main->width / main->height;
	main->step = main->height / THREAD_COUNT / 2;
}

void			init_sdl(t_main *main)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	main->win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, main->width, main->height, SDL_WINDOW_SHOWN);
	main->sur = SDL_GetWindowSurface(main->win);
}

t_main			*init(char *filename)
{
	t_main	*main;
	int		fd;

	fd = open(filename, O_RDONLY);
	main = (t_main*)malloc(sizeof(t_main));
	main->map = get_map_from_file(fd, filename);
	var_init(main);
	init_sdl(main);
	malloc_check(main->intersections =
		(t_vec3*)malloc(sizeof(t_vec3) * (main->width)));
	load_media(main);
	return (main);
}
