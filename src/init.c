/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:38:51 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/03 00:06:04 by llifeboa         ###   ########.fr       */
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
	rwop = SDL_RWFromFile("img/animation/bow/0-0.png", "r");
	main->textures[1] = IMG_LoadPNG_RW(rwop);
	main->textures[1] = SDL_ConvertSurfaceFormat(main->textures[1], SDL_PIXELFORMAT_ARGB8888, 0);
	rwop = SDL_RWFromFile("img/animation/bow/0-1.png", "r");
	main->textures[2] = IMG_LoadPNG_RW(rwop);
	main->textures[2] = SDL_ConvertSurfaceFormat(main->textures[2], SDL_PIXELFORMAT_ARGB8888, 0);
	rwop = SDL_RWFromFile("img/animation/bow/0-2.png", "r");
	main->textures[3] = IMG_LoadPNG_RW(rwop);
	main->textures[3] = SDL_ConvertSurfaceFormat(main->textures[3], SDL_PIXELFORMAT_ARGB8888, 0);
	rwop = SDL_RWFromFile("img/animation/bow/0-3.png", "r");
	main->textures[4] = IMG_LoadPNG_RW(rwop);
	main->textures[4] = SDL_ConvertSurfaceFormat(main->textures[4], SDL_PIXELFORMAT_ARGB8888, 0);
	rwop = SDL_RWFromFile("img/animation/bow/0-4.png", "r");
	main->textures[5] = IMG_LoadPNG_RW(rwop);
	main->textures[5] = SDL_ConvertSurfaceFormat(main->textures[5], SDL_PIXELFORMAT_ARGB8888, 0);
	rwop = SDL_RWFromFile("img/animation/bow/0-5.png", "r");
	main->textures[6] = IMG_LoadPNG_RW(rwop);
	main->textures[6] = SDL_ConvertSurfaceFormat(main->textures[6], SDL_PIXELFORMAT_ARGB8888, 0);
	rwop = SDL_RWFromFile("img/animation/bow/0-6.png", "r");
	main->textures[7] = IMG_LoadPNG_RW(rwop);
	main->textures[7] = SDL_ConvertSurfaceFormat(main->textures[7], SDL_PIXELFORMAT_ARGB8888, 0);
	rwop = SDL_RWFromFile("img/animation/bow/0-7.png", "r");
	main->textures[8] = IMG_LoadPNG_RW(rwop);
	main->textures[8] = SDL_ConvertSurfaceFormat(main->textures[8], SDL_PIXELFORMAT_ARGB8888, 0);

}

t_animation *init_animation(t_main *main)
{
	t_animation *result;

	result = (t_animation*)malloc(sizeof(t_animation));
	result->frame_count = 8;
	result->duration = 500;
	result->state = 0;
	result->frames = (SDL_Surface**)malloc(sizeof(SDL_Surface*));
	result->frames[0] = main->textures[4];
	result->frames[1] = main->textures[5];
	result->frames[2] = main->textures[6];
	result->frames[3] = main->textures[7];
	result->frames[4] = main->textures[8];
	result->frames[5] = main->textures[1];
	result->frames[6] = main->textures[2];
	result->frames[7] = main->textures[3];
	result->main_frame = main->textures[4];
	return (result);
}

t_main			*init()
{
	t_main *main;

	int fd = open("./maps/level1.map", O_RDONLY);
	main = (t_main*)malloc(sizeof(t_main));
	main->quit = 1;
	main->height = 1080;
	main->width = 1920;
	main->minimap_scale = 0.5;
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
	malloc_check(main->intersections = (t_vec3*)malloc(sizeof(t_vec3) * (main->width)));
	load_textures(main);
	main->weapon = init_animation(main);
	return (main);
}
