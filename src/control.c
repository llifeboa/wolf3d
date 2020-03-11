/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:15:09 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/04 06:33:18 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	move(t_main *main, float cos, float sin)
{
	t_vec3 dir_vec;
	t_vec3 prev_position;

	prev_position = main->position;
	dir_vec = rotate_y(main->forward_dir, cos, sin);
	main->position = (t_vec3){main->position.x + dir_vec.x *
		main->move_speed * main->move_dir, main->position.y, main->position.z};
	if (main->map->map_cells[(int)main->position.z / 64]
			[(int)main->position.x / 64].front)
		main->position = prev_position;
	prev_position = main->position;
	main->position = (t_vec3){main->position.x, main->position.y,
		main->position.z + dir_vec.z * main->move_speed * main->move_dir};
	if (main->map->map_cells[(int)main->position.z / 64]
		[(int)main->position.x / 64].front)
		main->position = prev_position;
}

void	keydown(t_main *main)
{
	audio_contol(main);
	if (main->e.key.keysym.sym == SDLK_ESCAPE)
		main->quit = 0;
	if (main->e.key.keysym.sym == SDLK_d)
		main->rotation_dir = 1;
	if (main->e.key.keysym.sym == SDLK_a)
		main->rotation_dir = -1;
	if (main->e.key.keysym.sym == SDLK_w)
		main->move_dir = 1;
	if (main->e.key.keysym.sym == SDLK_s)
		main->move_dir = -1;
	if (main->e.key.keysym.sym == SDLK_p)
		animation_start(main, SDL_GetTicks());
}

void	controls(t_main *main)
{
	if (main->e.type == SDL_QUIT)
		main->quit = 0;
	if (main->e.type == SDL_KEYDOWN)
		keydown(main);
	if (main->e.type == SDL_KEYUP)
	{
		if (main->e.key.keysym.sym == SDLK_d ||
				main->e.key.keysym.sym == SDLK_a)
			main->rotation_dir = 0;
		if (main->e.key.keysym.sym == SDLK_w ||
				main->e.key.keysym.sym == SDLK_s)
			main->move_dir = 0;
	}
}
