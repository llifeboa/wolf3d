/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 14:31:15 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/04 12:55:41 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# define THREAD_COUNT 10
# include <libft.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <SDL2/SDL_ttf.h>
# include <SDL2/SDL_mixer.h>
# include <vec3.h>
# include <pthread.h>
# include <fcntl.h>
# define CAN_ANIMATITE 0
# define ANIMATING 1
# define WALL_FRONT 0
# define WALL_BACK 1
# define WALL_LEFT 2
# define WALL_RIGHT 3

typedef struct		s_wall_info
{
	SDL_Surface		*texture;
	int				side;
}					t_wall_info;

typedef struct		s_animation
{
	unsigned int	frame_count;
	Uint32			duration;
	unsigned int	state;
	Uint32			start_time;
	SDL_Surface		**frames;
	SDL_Surface		*main_frame;
}					t_animation;

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

typedef struct		s_img
{
	SDL_Surface		*textures[100];
	SDL_Surface		*animation[1][8];
}					t_img;

typedef struct		s_sounds
{
	Mix_Music		*track;
	Mix_Chunk		*bowhit;
	Mix_Chunk		*step;
}					t_sounds;

typedef struct		s_main
{
	SDL_Window		*win;
	SDL_Surface		*sur;
	SDL_Event		e;
	t_img			images;
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
	t_vec3			*intersections;
	t_animation		*weapon;
	t_sounds		sound;
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
void				animation_start(t_main *main, Uint32 start_time);
int					by_byte_dis(int color, unsigned char dis);
void				audio_contol(t_main *main);

#endif
