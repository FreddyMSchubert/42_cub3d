/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:15:40 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 13:36:37 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	vec2_dot_product(t_vec2 a, t_vec2 b)
{
	return (a.x * b.x + a.y * b.y);
}

double	vec2_sqr_magnitude(t_vec2 v)
{
	return (v.x * v.x + v.y * v.y);
}

t_vec2	vec2_sub(t_vec2 a, t_vec2 b)
{
	t_vec2	result;

	result.x = a.x - b.x;
	result.y = a.y - b.y;
	return (result);
}

// if direction is 1, rotate clockwise, if -1, rotate counterclockwise
t_vec2	rotate_vector_by_90_degrees(t_vec2 v, int direction)
{
	t_vec2	rotated;

	rotated.x = v.y * direction;
	rotated.y = -v.x * direction;
	return (rotated);
}
