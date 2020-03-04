/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 12:07:37 by llifeboa          #+#    #+#             */
/*   Updated: 2020/03/04 02:48:38 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

void	print_frame(t_main *main, SDL_Surface *frame, int size)
{
	int *dist = (int*)(main->sur->pixels);
	int	*src = (int*)(frame->pixels);
	int i;
	int j;
	int h = frame->h * size;
	int w = frame->w * size;
	i = 0;
	while (i < h)
	{
		j = 0;
		while(j < w)
		{
			if (src[(i / size * w / size ) + (j / size)] & 0x11000000)
				dist[(main->sur->h - h + i) * main->sur->w + j + main->sur->w - w] = src[(i / size * w / size ) + (j / size)];
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
	Uint32 delta = cur_time - anim->start_time;

	if (anim->state)
	{
		if(delta / (anim->duration / anim->frame_count) == anim->frame_count)
		{
			anim->state = CAN_ANIMATITE;
			print_frame(main, anim->frames[0], 6);
		}
		else
		{
			print_frame(main, anim->frames[delta / (anim->duration / anim->frame_count)], 6);
		}
	}
	else
	{
		print_frame(main, anim->main_frame, 6);
	}
	
}

float	fish_eye(t_vec3 origin, t_vec3 cur)
{
	float cos;
	
	cos = (origin.x * cur.x + origin.z * cur.z ) /
	(sqrtf(origin.x * origin.x + origin.z * origin.z) *
	sqrtf(cur.x * cur.x + cur.z * cur.z));
	return (cos);
}

void	print_rect(t_main *main, t_vec3 p, t_vec3 s, float color)
{
	int* dist = main->sur->pixels;
	int i = 0;
	int j = 0;
	p.x = p.x > main->width ? main->width - 1: p.x < 0 ? 0 : p.x;
	p.y = p.y > main->width ? main->width - 1: p.y < 0 ? 0 : p.y;
	while (i < (int)(s.y))
	{
		while (j < (int)(s.x))
		{
			dist[((int)p.y + i) * main->sur->w + (int)p.x + j] = color;
			j++;
		}
		j = 0;
		i++;
	}
}

void	print_map(t_main *main)
{
	int i = 0;
	int j = 0;
	float size;

	size = 64 * main->minimap_scale;
	if (size < 0)
		size = 1;
	while (i < main->map->height)
	{
		while (j < main->map->width)
		{
			print_rect(main,
			(t_vec3){j * size, i * size, 0},
			(t_vec3){size, size, 0},
			main->map->map_cells[i][j].front > 0 ? 0 : 0xffffff);
			j++;
		}
		
		j = 0;
		i++;
	}
	print_rect(main, (t_vec3){main->position.x * main->minimap_scale,
	main->position.z * main->minimap_scale, 0}, (t_vec3){4, 4, 0}, 0xff0000);
	i = 0;
	while (i < main->width)
	{
		print_rect(main, (t_vec3){(int)main->intersections[i].x * main->minimap_scale,
		(int)main->intersections[i].z * main->minimap_scale, 0},
		(t_vec3){2, 2, 0}, 0xff00ff);
		i++;
	}
	
}

t_vec3 rotate_y(t_vec3 v, float cos, float sin)
{
	return (t_vec3){cos * v.x + sin * v.z, v.y, -sin * v.x + cos * v.z};
}

t_vec3	plane_intersection_opt(t_ray ray)
{
	float t = -ray.origin.y / ray.direction.y;
	return ((t_vec3){ray.direction.x * t + ray.origin.x, 0, ray.direction.z * t + ray.origin.z});
}

t_vec3	plane_intersection(t_ray ray, t_vec3 normal)
{
	float dot_normal_ray;

	dot_normal_ray = vec3_dot(ray.direction, normal);
	float t = vec3_dot(vec3_sub((t_vec3){0, 0, 0}, ray.origin), normal) / dot_normal_ray;
	return (vec3_add(ray.origin, vec3_mult(ray.direction, t)));
}

void *cast_ray(void *param)
{
	t_ray_data *data = (t_ray_data*)param;
	t_vec3	left_intersection;
	t_ray	left_ray;
	t_vec3	right_intersection;
	t_ray	right_ray;
	t_vec3	step;
	int i = 0;
	int j = 0;
	int *src;
	int *dist;
	int color;
	dist = (int*)(data->main->sur->pixels);
	src = (int*)(data->main->images.textures[0]->pixels);
	while(j < data->main->step)
	{
		left_ray.origin = data->main->position;
		left_ray.direction = (t_vec3){-0.5 * data->main->aspect_ratio, -0.5 + (float)(data->main->height - data->y + j) / data->main->height, 1};
		left_ray.direction = rotate_y(left_ray.direction, *(data->cos), *(data->sin));
		left_intersection = plane_intersection_opt(left_ray);
		right_ray.origin = data->main->position;
		right_ray.direction = (t_vec3){0.5 * data->main->aspect_ratio, -0.5 + (float)(data->main->height - data->y + j) / data->main->height, 1};
		right_ray.direction = rotate_y(right_ray.direction, *(data->cos), *(data->sin));
		right_intersection = plane_intersection_opt(right_ray);
		step = vec3_div(vec3_sub(right_intersection, left_intersection), data->main->width);

		t_vec3 point = left_intersection;

		while(i < data->main->width)
		{	
			color = src[64 * (63 - ((int)(point.z > 0 ? point.z : -point.z) % 64)) +
			((int)(point.x > 0 ? point.x : -point.x) % 64)];
			dist[(data->y - j) * data->main->sur->w + i] = color;
			point.z += step.z;
			point.x += step.x;
			i++;
		}
		i = 0;
		j++;
	}
	pthread_exit(0);
}

t_vec3	intersection_horizontal(t_main *main, t_vec3 origin, t_vec3 direction)
{
	int	dir;

	dir = direction.z > 0 ? 1 : -1;
	float	z = (((int)origin.z / 64) + (dir > 0 ? 1 : 0)) * 64;
	float point_1 = (z - origin.z) * direction.x / direction.z + origin.x;

	if (point_1 > (main->map->width - 1) * 64 || point_1 < 64)
		return (t_vec3){point_1, 32, z};
	if (main->map->map_cells[(int)((z + dir) / 64)][(int)(point_1 / 64)].front == 1)
		return (t_vec3){point_1, 32, z};
	z += 64 * dir;
	float point_2 = (z - origin.z) * direction.x / direction.z + origin.x;
	if (point_2 > (main->map->width - 1) * 64 || point_2 < 64)
		return (t_vec3){point_2, 32, z};
	float step = point_2 - point_1;
	while(!main->map->map_cells[(int)((z + dir) / 64)][(int)(point_2 / 64)].front)
	{
		point_2 += step;
		z += 64 * dir;
		if (point_2 > (main->map->width - 1) * 64 || point_2 < 64)
			break;
	}
	return (t_vec3){point_2, 32, z};
}

t_vec3	intersection_vertical(t_main *main, t_vec3 origin, t_vec3 direction)
{
	int	dir;

	dir = direction.x > 0 ? 1 : -1;
	float	x = (((int)origin.x / 64) + (dir > 0 ? 1 : 0)) * 64;
	float point_1 = (x - origin.x) * direction.z / direction.x + origin.z;

	if (point_1 > (main->map->height - 1) * 64 || point_1 < 64)
		return (t_vec3){x, 32, point_1};
	if (main->map->map_cells[(int)(point_1 / 64)][(int)((x + dir) / 64)].front == 1)
		return (t_vec3){x, 32, point_1};
	x += 64 * dir;
	float point_2 = (x - origin.x) * direction.z / direction.x + origin.z;
	float step = point_2 - point_1;
	if (point_2 > (main->map->height - 1) * 64 || point_2 < 64)
		return (t_vec3){x, 32, point_2};
	while(!(main->map->map_cells[(int)(point_2 / 64)][(int)((x + dir) / 64)].front))
	{
		point_2 += step;
		x += 64 * dir;
		if (point_2 > (main->map->height - 1) * 64 || point_2 < 65)
			break;
	}
	return (t_vec3){x, 32, point_2};
}

int		by_byte_dis(int color, unsigned char dis)
{
	unsigned char* result;
	
	dis = dis == 0 ? 1 : dis;
	result = (unsigned char*)&color;
	result[1] = (unsigned char)((float)result[1] / dis);
	result[2] = (unsigned char)((float)result[2] / dis);
	result[0] = (unsigned char)((float)result[0] / dis);
	return color;
}

void	walls(t_main *main, float cos, float sin)
{
	int i = 0;
	int j = 0;
	float step = main->aspect_ratio / main->width;
	float cur = -main->aspect_ratio / 2;

	t_vec3 h_intersect;
	t_vec3 v_intersect;
	t_vec3 h_intersect_1;
	t_vec3 v_intersect_1;
	t_vec3	intersection;
	float length;
	float length_v;
	float length_h;
	int length_wall_o;
	int length_wall_p;
	int start_paint;
	float fish_eye_fix;
	int h_or_v;
	int color;
	while(i < main->width)
	{
		h_intersect = intersection_horizontal(main, main->position, rotate_y((t_vec3){cur, 32, 1}, cos, sin));
		v_intersect = intersection_vertical(main, main->position, rotate_y((t_vec3){cur, 32, 1}, cos, sin));
		fish_eye_fix = fish_eye((t_vec3){0, 0, 1}, (t_vec3){cur, 0, 1});
		h_intersect_1 = h_intersect;
		v_intersect_1 = v_intersect;
		h_intersect = vec3_sub(h_intersect, main->position);
		v_intersect = vec3_sub(v_intersect, main->position);
		length_h = sqrtf(h_intersect.x * h_intersect.x + h_intersect.z * h_intersect.z);
		length_v = sqrtf(v_intersect.x * v_intersect.x + v_intersect.z * v_intersect.z);
		length = (length_h > length_v ? length_v : length_h) * fish_eye_fix;
		h_or_v = (length_h > length_v ? 0 : 1); 
		intersection = length_h > length_v ? v_intersect_1 : h_intersect_1;
		main->intersections[i] = intersection;
		length_wall_o = (int)(main->height / (length / 64));
		length_wall_p = length_wall_o > main->height ? main->height : length_wall_o;
		start_paint = (main->height - length_wall_p) / 2;
		j = 0;
		int *dist = (int*)(main->sur->pixels);
		int	*src = (int*)(main->images.textures[0]->pixels);
		while (j < length_wall_p)
		{
			color = src[(int)((((length_wall_o - length_wall_p) / 2 + (float)j) / length_wall_o * 64.0)) * 64 +
			(h_or_v == 1 ? ((int)(intersection.x) % 64) : (63 - (int)(intersection.z) % 64))];
			dist[(start_paint + j) * main->sur->w + i] = color;
			
			j++;
		}
		cur += step;
		i++;
	}
	print_map(main);
}

void move(t_main *main, float cos, float sin)
{
	t_vec3 dir_vec;
	t_vec3 prev_position;

	prev_position = main->position;
	dir_vec = rotate_y(main->forward_dir, cos, sin);
	main->position = vec3_add(main->position, vec3_mult(dir_vec, main->move_dir * main->move_speed));
	if(main->map->map_cells[(int)main->position.z / 64][(int)main->position.x / 64].front)
		main->position = prev_position;
}

int main() 
{ 
	t_main	*main;
	main = init();
	float sin;
	float cos;
	t_ray_data thread[THREAD_COUNT];
	Uint32 t = SDL_GetTicks();

	
    while (main->quit) 
	{
		t = SDL_GetTicks();

		SDL_LockSurface(main->sur);
		print_rect(main, (t_vec3){0,0, 0}, (t_vec3){main->width, main->height, 0}, 0);
		while(SDL_PollEvent(&(main->e)))
			controls(main);
		int i = 0;
		main->angle += main->rotation_speed * main->rotation_dir;
		cos = cosf(main->angle);
		sin = sinf(main->angle);
		move(main, cos, sin);
		while(i < THREAD_COUNT)
		{
			thread[i].main = main;
			thread[i].cos = &cos;
			thread[i].sin = &sin;
			thread[i].y = (main->height - i * main->step) - 1;
			pthread_create(&(thread[i].tid), NULL, cast_ray, &thread[i]);
			i++;
		}
		i = 0;
		while (i < THREAD_COUNT)
		{
			pthread_join(thread[i].tid, NULL);
			i++;
		}
		walls(main, cos, sin);
		animation_update(main, main->weapon, SDL_GetTicks());
		
		SDL_UnlockSurface(main->sur);
		SDL_UpdateWindowSurface(main->win);
		printf("FPS: %d\n", 1000 / (SDL_GetTicks() - t));
	}
	SDL_DestroyWindow(main->win);
	SDL_Quit();
    exit(0);
	return(0);
} 
