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

void			sound_init(t_main *main)
{
	Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096);
	main->sound.track = Mix_LoadMUS("audio/music/calm3.ogg");
	main->sound.bowhit = Mix_LoadWAV("audio/fx/bow.ogg");
	main->sound.step = Mix_LoadWAV("audio/fx/stone3.ogg");
	Mix_AllocateChannels(10);
	Mix_VolumeChunk(main->sound.bowhit, 15);
	Mix_VolumeMusic(25);
	Mix_PlayMusic(main->sound.track, 15);
}

static void		load_textures(t_main *main)
{

	malloc_check(main->images.textures[1] = IMG_Load("img/textures/wolf.png"));
	malloc_check(main->images.textures[2] = IMG_Load("img/textures/wood.png"));
	malloc_check(main->images.textures[3] = IMG_Load("img/textures/eagle.png"));
	malloc_check(main->images.textures[4] = IMG_Load("img/textures/pikuma.png"));
	malloc_check(main->images.textures[5] = IMG_Load("img/textures/bluestone.png"));
}

static void		load_animations_bow(t_main *main)
{
	
	malloc_check(main->images.animation[0][0] = IMG_Load("img/animation/bow/0-7.png"));
	malloc_check(main->images.animation[0][1] = IMG_Load("img/animation/bow/0-0.png"));
	malloc_check(main->images.animation[0][2] = IMG_Load("img/animation/bow/0-1.png"));
	malloc_check(main->images.animation[0][3] = IMG_Load("img/animation/bow/0-2.png"));
	malloc_check(main->images.animation[0][4] = IMG_Load("img/animation/bow/0-3.png"));
	malloc_check(main->images.animation[0][5] = IMG_Load("img/animation/bow/0-4.png"));
	malloc_check(main->images.animation[0][6] = IMG_Load("img/animation/bow/0-5.png"));
	malloc_check(main->images.animation[0][7] = IMG_Load("img/animation/bow/0-6.png"));
}

static void		load_animations(t_main *main)
{
	load_animations_bow(main);
}

t_animation *init_animation(t_main *main)
{
	t_animation *result;

	result = (t_animation*)malloc(sizeof(t_animation));
	result->frame_count = 8;
	result->duration = 800;
	result->state = 0;
	result->frames = (SDL_Surface**)malloc(sizeof(SDL_Surface*) * result->frame_count);
	result->frames[0] = main->images.animation[0][4];
	result->frames[1] = main->images.animation[0][5];
	result->frames[2] = main->images.animation[0][6];
	result->frames[3] = main->images.animation[0][7];
	result->frames[4] = main->images.animation[0][0];
	result->frames[5] = main->images.animation[0][1];
	result->frames[6] = main->images.animation[0][2];
	result->frames[7] = main->images.animation[0][3];
	result->main_frame = main->images.animation[0][4];
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
	IMG_Init(IMG_INIT_PNG);
	load_textures(main);
	load_animations(main);
	main->weapon = init_animation(main);
	sound_init(main);
	return (main);
}
