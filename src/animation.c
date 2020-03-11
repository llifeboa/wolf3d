/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 18:59:13 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/11 18:59:14 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	print_frame(t_main *main, SDL_Surface *frame, int size)
{
	int *dist;
	int	*src;
	int i;
	int j;

	dist = (int*)(main->sur->pixels);
	src = (int*)(frame->pixels);
	i = 0;
	while (i < frame->h * size)
	{
		j = 0;
		while (j < frame->w * size)
		{
			if (src[(i / size * frame->w) + (j / size)] & 0x11000000)
				dist[(main->sur->h - (frame->h * size) + i) *
					main->sur->w + j + main->sur->w - (frame->w * size)] =
					src[(i / size * (frame->w * size) / size) + (j / size)];
			j++;
		}
		i++;
	}
}

void	animation_start(t_main *main, Uint32 start_time)
{
	if (main->weapon->state == CAN_ANIMATITE)
	{
		Mix_PlayChannel(1, main->sound.bowhit, 0);
		main->weapon->state = ANIMATING;
		main->weapon->start_time = start_time;
	}
}

void	animation_update(t_main *main, t_animation *anim, Uint32 cur_time)
{
	Uint32 delta;

	delta = cur_time - anim->start_time;
	if (anim->state)
	{
		if (delta / (anim->duration / anim->frame_count) == anim->frame_count)
		{
			anim->state = CAN_ANIMATITE;
			print_frame(main, anim->frames[0], 6);
		}
		else
		{
			print_frame(main, anim->frames[delta /
				(anim->duration / anim->frame_count)], 6);
		}
	}
	else
	{
		print_frame(main, anim->main_frame, 6);
	}
}
