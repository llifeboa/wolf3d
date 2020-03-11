/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   audio_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 03:40:01 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/04 06:33:17 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	audio_contol(t_main *main)
{
	if (!Mix_Playing(2))
	{
		if (main->e.key.keysym.sym == SDLK_w)
			Mix_PlayChannel(2, main->sound.step, 0);
		if (main->e.key.keysym.sym == SDLK_s)
			Mix_PlayChannel(2, main->sound.step, 0);
		if (main->e.key.keysym.sym == SDLK_d)
			Mix_PlayChannel(2, main->sound.step, 0);
		if (main->e.key.keysym.sym == SDLK_a)
			Mix_PlayChannel(2, main->sound.step, 0);
	}
}
