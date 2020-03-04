/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 16:15:09 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/03 00:06:00 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	controls(t_main *main)
{
	if(main->e.type == SDL_QUIT)
		main->quit = 0;	
	if(main->e.type == SDL_KEYDOWN)
	{
		audio_contol(main);
		if (main->e.key.keysym.sym == SDLK_ESCAPE)
			main->quit = 0;
		else if (main->e.key.keysym.sym == SDLK_d)
			main->rotation_dir = 1;
		else if (main->e.key.keysym.sym == SDLK_a)
			main->rotation_dir = -1;
		else if (main->e.key.keysym.sym == SDLK_w)
			main->move_dir = 1;
		else if (main->e.key.keysym.sym == SDLK_s)
			main->move_dir = -1;
		else if (main->e.key.keysym.sym == SDLK_p)
			animation_start(main, SDL_GetTicks());
	}
	if(main->e.type == SDL_KEYUP)
	{
		if (main->e.key.keysym.sym == SDLK_d)
			main->rotation_dir = 0;
		else if (main->e.key.keysym.sym == SDLK_a)
			main->rotation_dir = 0;
		else if (main->e.key.keysym.sym == SDLK_w)
			main->move_dir = 0;
		else if (main->e.key.keysym.sym == SDLK_s)
			main->move_dir = 0;
	}
}