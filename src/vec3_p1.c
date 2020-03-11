/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_p1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlayna <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 01:59:53 by nlayna            #+#    #+#             */
/*   Updated: 2020/03/12 01:59:56 by nlayna           ###   ########.fr       */
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
