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
# define THREAD_COUNT 25
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
# define DASH_READY 0
# define DASH_DASHING 1
# define DASH_FINISHED 3

typedef struct		s_sprite{
	t_vec3			position;
}					t_sprite;

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
	t_vec3			player_pos;
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

typedef struct		s_skill_dash{
	short			is_dash_ready;
	Uint32			start_time;
	short			multiplayer;
	Uint32			duration;
	Uint32			cooldown;
}					t_skill_dash;

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
	t_skill_dash	dash;

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

typedef struct		s_cast
{
	t_ray_data		*data;
	t_vec3			left_intersection;
	t_ray			left_ray;
	t_vec3			right_intersection;
	t_ray			right_ray;
	t_vec3			step;
	int				color;
	t_vec3			point;
	int				*src;
	int				*dist;
}					t_cast;

typedef struct		s_intersection
{
	int				dir;
	float			x;
	float			point_1;
	float			point_2;
	float			step;
}					t_intersection;

typedef struct		s_wall
{
	float			step;
	float			cur;
	t_vec3			h_intersect;
	t_vec3			v_intersect;
	t_vec3			h_intersect_1;
	t_vec3			v_intersect_1;
	t_vec3			intersection;
	float			length;
	float			length_v;
	float			length_h;
	int				length_wall_o;
	int				length_wall_p;
	int				start_paint;
	float			fish_eye_fix;
	int				h_or_v;
	int				color;
	t_wall_info		wall_info;
	t_vec3			ray;
	int				*dist;
	int				*src;
}					t_wall;

void				exit_with_error(char *message);
void				malloc_check(void *data);
void				controls(t_main *main);
void				move(t_main *main, float cos, float sin);
t_main				*init(char *filename);
void				*cast_ray(void *param);
void				walls(t_main *main, float cos, float sin);
t_map				*get_map_from_file(int fd, char *filename);
int					ft_atoi_with_non_digit_error(const char *str);
void				animation_start(t_main *main, Uint32 start_time);
void				animation_update
						(t_main *main, t_animation *anim, Uint32 cur_time);
int					by_byte_dis(int color, unsigned char dis);
void				audio_contol(t_main *main);
void				print_frame(t_main *main, SDL_Surface *frame, int size);
void				print_rect(t_main *main, t_vec3 p, t_vec3 s, float color);
void				print_map(t_main *main);
t_vec3				rotate_y(t_vec3 v, float cos, float sin);
float				fish_eye(t_vec3 origin, t_vec3 cur);
t_vec3				plane_intersection(t_ray ray, t_vec3 normal);
t_vec3				plane_intersection_opt(t_ray ray);
t_vec3				intersection_horizontal
						(t_main *main, t_vec3 origin, t_vec3 direction);
t_vec3				intersection_vertical
						(t_main *main, t_vec3 origin, t_vec3 direction);
t_wall_info			get_wall_info
						(t_main *main, t_vec3 ray,
						t_vec3 intersection, int h_or_v);
void				load_media(t_main *main);
void				load_animations(t_main *main);
void				load_animations_bow(t_main *main);
void				map_validation(t_map *map, int check);
void				free_split(char **split);
t_vec3				get_pos(t_map *map, char *line);
int					check_elem(char *s, int wc);
int					check_line(char **str, int flag, int w_count);
int					get_height(char *filename);
int					get_word_count(char *line, char sep);
void				elem_filler(t_map_cell *points, int value, int i);
void				push_elem(char **z, t_map_cell *points);
t_map_cell			*line_to_point_array(int flag, char *line, int word_count);
t_map				*add_new_line_to_map(t_map_cell *line, t_map *map);
void				get_properties(t_map *map, char *line, int *h);
void				map_filler(t_map *map, char *line, int h);
void				player_find(t_map *map, char *line, int h, int *check);

#endif
