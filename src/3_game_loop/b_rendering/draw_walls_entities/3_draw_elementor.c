/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_elementor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:13:27 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/05 14:48:01 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

#define ELEMENTOR_SPRITE_WIDTH 29
#define TICKS_PER_FRAME 1

static inline t_color	get_element_col(int element)
{
	element %= 4;
	if (element < 0)
		element += 4;
	if (element == TYPE_WATER)
		return (int_to_t_color(rgba_to_int(30, 96, 162, 255)));
	else if (element == TYPE_FIRE)
		return (int_to_t_color(rgba_to_int(142, 7, 28, 255)));
	else if (element == TYPE_AIR)
		return (int_to_t_color(rgba_to_int(179, 179, 179, 255)));
	else if (element == TYPE_EARTH)
		return (int_to_t_color(rgba_to_int(4, 123, 16, 255)));
	return (int_to_t_color(rgba_to_int(0, 0, 0, 0)));
}

static inline int	get_phase_2_col(t_scale tex, int frame)
{
	int	effective_x;
	int	color_width;

	effective_x = (tex.x + frame + tex.y) % ELEMENTOR_SPRITE_WIDTH;
	color_width = ELEMENTOR_SPRITE_WIDTH / 3;
	if (effective_x < color_width)
		return (0);
	else if (effective_x < 2 * color_width)
		return (1);
	else
		return (2);
}

t_color	get_elementor_cloak_color(t_scale tex)
{
	t_elementor	*elementor;
	int			i;

	(void)tex;
	if (!game()->boss)
		cub_exit("No boss found", -1);
	elementor = (t_elementor *)game()->boss->data;
	if (elementor->stage == 0)
		return (get_element_col(elementor->element1));
	i = get_phase_2_col(tex, elementor->animation_frame / TICKS_PER_FRAME);
	if (i == 0)
		return (get_element_col(elementor->element1));
	else if (i == 1)
		return (get_element_col(elementor->element2));
	else
		return (get_element_col(elementor->element3));
}
