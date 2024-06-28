/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:56:27 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 13:41:11 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

unsigned int	t_color_to_int(t_color color)
{
	return (color.r << 24 | color.g << 16 | color.b << 8 | color.a);
}

t_color	int_to_t_color(int color)
{
	t_color	result;

	result.r = (color >> 24) & 0xFF;
	result.g = (color >> 16) & 0xFF;
	result.b = (color >> 8) & 0xFF;
	result.a = color & 0xFF;
	return (result);
}

t_color	with_opacity(t_color in, int opacity)
{
	t_color	result;

	result.r = in.r;
	result.g = in.g;
	result.b = in.b;
	result.a = opacity;
	return (result);
}

int	rgba_to_int(int r, int g, int b, int a)
{
	return (t_color_to_int((t_color){r, g, b, a}));
}
