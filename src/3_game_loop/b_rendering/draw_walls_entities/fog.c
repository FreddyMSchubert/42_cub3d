/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fog.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 14:02:36 by freddy            #+#    #+#             */
/*   Updated: 2024/07/07 14:40:00 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static int	clamp_int(int value, int min, int max)
{
	if (value < min)
		return (min);
	if (value > max)
		return (max);
	return (value);
}

t_color	apply_fog(t_color col, double distance)
{
	double	fog_amount;
	t_color	fog_col;

	fog_amount = ((double)game()->input_data->fog_intensity / 10.0) * distance;
	fog_col = game()->input_data->fog_color;
	if (col.r < fog_col.r)
		col.r = clamp_int(col.r + fog_amount, 0, fog_col.r);
	else
		col.r = clamp_int(col.r - fog_amount, fog_col.r, 255);
	if (col.g < fog_col.g)
		col.g = clamp_int(col.g + fog_amount, 0, fog_col.g);
	else
		col.g = clamp_int(col.g - fog_amount, fog_col.g, 255);
	if (col.b < fog_col.b)
		col.b = clamp_int(col.b + fog_amount, 0, fog_col.b);
	else
		col.b = clamp_int(col.b - fog_amount, fog_col.b, 255);
	return (col);
}
