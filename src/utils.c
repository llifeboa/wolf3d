/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 20:00:10 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/11 20:00:12 by nlayna           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <wolf3d.h>

float	fish_eye(t_vec3 origin, t_vec3 cur)
{
	float	cos;

	cos = (origin.x * cur.x + origin.z * cur.z) /
		(sqrtf(origin.x * origin.x + origin.z * origin.z) *
		sqrtf(cur.x * cur.x + cur.z * cur.z));
	return (cos);
}

t_vec3	rotate_y(t_vec3 v, float cos, float sin)
{
	return (t_vec3){cos * v.x + sin * v.z, v.y, -sin * v.x + cos * v.z};
}

t_vec3	plane_intersection_opt(t_ray ray)
{
	float t;

	t = -ray.origin.y / ray.direction.y;
	return ((t_vec3){ray.direction.x * t + ray.origin.x,
		0, ray.direction.z * t + ray.origin.z});
}

t_vec3	plane_intersection(t_ray ray, t_vec3 normal)
{
	float	dot_normal_ray;
	float	t;

	dot_normal_ray = vec3_dot(ray.direction, normal);
	t = vec3_dot(vec3_sub((t_vec3){0, 0, 0},
		ray.origin), normal) / dot_normal_ray;
	return (vec3_add(ray.origin, vec3_mult(ray.direction, t)));
}
