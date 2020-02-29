/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llifeboa <llifeboa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 17:33:06 by llifeboa          #+#    #+#             */
/*   Updated: 2020/02/17 23:52:13 by llifeboa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

float		vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

float		vec3_length(t_vec3 v)
{
	return (sqrtf(vec3_dot(v, v)));
}

t_vec3		vec3_div(t_vec3 v, float s)
{
	v.x /= s;
	v.y /= s;
	v.z /= s;
	return (v);
}

t_vec3		vec3_mult(t_vec3 v, float s)
{
	v.x *= s;
	v.y *= s;
	v.z *= s;
	return (v);
}

t_vec3		vec3_normalize(t_vec3 v)
{
	float l;

	l = vec3_length(v);
	v = vec3_div(v, l);
	return (v);
}

t_vec3		vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vec3		vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}
