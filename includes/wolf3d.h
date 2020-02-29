/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:31:15 by llifeboa          #+#    #+#             */
/*   Updated: 2020/02/28 03:16:53 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	WOLF3D_H
#define	WOLF3D_H
#define THREAD_COUNT 10
#include <libft.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <vec3.h>
#include <pthread.h>
# include <fcntl.h>

typedef struct		s_map_cell
{
	unsigned int	front;
	unsigned int	back;
	unsigned int	left;
	unsigned int	right;
}					t_map_cell;

typedef struct		s_map
{
	t_map_cell		**map_cells;
	int				width;
	int				height;
}					t_map;

typedef struct		s_main
{
	SDL_Window		*win;
	SDL_Surface		*sur;
	SDL_Event		e;
	SDL_Surface		*textures[1];
	int				width;
	int				height;
	int				step;
	float			aspect_ratio;
	int				quit;
	float			angle;
	int				rotation_dir;
	int				move_dir;
	float			rotation_speed;
	float			move_speed;
	t_vec3			position;
	t_vec3			forward_dir;
	t_vec3			right_dir;
	t_map			*map;
	float			minimap_scale;
}					t_main;

typedef struct		s_ray_data
{
	t_main			*main;
	int				y;
	float			*cos;
	float			*sin;
	pthread_t		tid;
}					t_ray_data;

typedef struct		s_camera
{
	t_vec3			position;
	t_vec3			dir;
}					t_camera;
typedef struct		s_ray
{
	t_vec3			origin;
	t_vec3			direction;
}					t_ray;

void				exit_with_error(char *message);
void				malloc_check(void *data);
void				controls(t_main *main);
t_main				*init();
void				*cast_ray(void *param);
t_map				*get_map_from_file(int fd);
int					ft_atoi_with_non_digit_error(const char *str);
#endif