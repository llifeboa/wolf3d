/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:07:37 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/04 16:47:40 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	update(t_main *main, float cos, float sin, Uint32 t)
{
	walls(main, cos, sin);
	animation_update(main, main->weapon, SDL_GetTicks());
	SDL_UpdateWindowSurface(main->win);
	printf("FPS: %d\n", 1000 / (SDL_GetTicks() - t));
}

void	create_threads(t_main *main, float cos, float sin, t_ray_data *thread)
{
	int i;

	i = 0;
	while (i < THREAD_COUNT)
	{
		thread[i].main = main;
		thread[i].cos = &cos;
		thread[i].sin = &sin;
		thread[i].y = (main->height - i * main->step) - 1;
		pthread_create(&(thread[i].tid), NULL, cast_ray, &thread[i]);
		i++;
	}
}

void	render(t_main *main)
{
	float		sin;
	float		cos;
	t_ray_data	thread[THREAD_COUNT];
	Uint32		t;
	int			i;

	while (main->quit)
	{
		t = SDL_GetTicks();
		print_rect(main, (t_vec3){0, 0, 0},
			(t_vec3){main->width, main->height, 0}, 0);
		while (SDL_PollEvent(&(main->e)))
			controls(main);
		main->angle += main->rotation_speed * main->rotation_dir;
		cos = cosf(main->angle);
		sin = sinf(main->angle);
		move(main, cos, sin);
		create_threads(main, cos, sin, thread);
		i = -1;
		while (++i < THREAD_COUNT)
			pthread_join(thread[i].tid, NULL);
		update(main, cos, sin, t);
	}
}

int		main(void)
{
	t_main	*main;

	main = init();
	render(main);
	SDL_DestroyWindow(main->win);
	SDL_Quit();
	return (0);
}
