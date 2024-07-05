/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_elementor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:13:27 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/05 13:42:20 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

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

t_color	get_elementor_cloak_color(t_scale tex)
{
	t_elementor	*elementor;

	(void)tex;
	if (!game()->boss)
		cub_exit("No boss found", -1);
	elementor = (t_elementor *)game()->boss->data;
	return (get_element_col(elementor->element1));
}
