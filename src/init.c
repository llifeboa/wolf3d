/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:38:51 by llifeboa          #+#    #+#             */
/*   Updated: 2020/02/29 13:54:27 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

static void		load_textures(t_main *main)
{
	IMG_Init(IMG_INIT_PNG);
	SDL_RWops *rwop;
	rwop = SDL_RWFromFile("img/wolf.png", "r");
	main->textures[0] = IMG_LoadPNG_RW(rwop);
	main->textures[0] = SDL_ConvertSurfaceFormat(main->textures[0], SDL_PIXELFORMAT_ARGB8888, 0);
}

t_main			*init()
{
	t_main *main;

	int fd = open("./maps/level1.map", O_RDONLY);
	main = (t_main*)malloc(sizeof(t_main));
	main->quit = 1;
	main->height = 1080;
	main->width = 1920;
	main->minimap_scale = 0.8;
	main->angle = 0;
	main->rotation_dir = 0;
	main->rotation_speed = 0.02;
	main->move_dir = 0;
	main->move_speed = 4;
	main->position = (t_vec3){64 * 6, 32, 64 * 6};
	main->forward_dir = (t_vec3){0, 0, 1};
	main->aspect_ratio = (float)main->width / main->height;
	main->step = main->height / THREAD_COUNT / 2;
	SDL_Init(SDL_INIT_EVERYTHING);
	main->win = SDL_CreateWindow("wolf3d", SDL_WINDOWPOS_CENTERED,
	SDL_WINDOWPOS_CENTERED, main->width, main->height, SDL_WINDOW_SHOWN);
	main->sur = SDL_GetWindowSurface(main->win);
	main->map = get_map_from_file(fd);
	load_textures(main);
	return (main);
}
