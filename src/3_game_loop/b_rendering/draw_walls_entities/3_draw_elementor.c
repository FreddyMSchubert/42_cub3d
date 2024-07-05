/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_draw_elementor.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 13:13:27 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/05 21:15:49 by freddy           ###   ########.fr       */
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

static inline int	animation_col(t_scale tex, int frame, int color_amount)
{
	int	effective_x;
	int	color_width;

	effective_x = (tex.x + frame + tex.y) % ELEMENTOR_SPRITE_WIDTH;
	color_width = ELEMENTOR_SPRITE_WIDTH / color_amount;
	if (effective_x <= color_width)
		return (0);
	else if (effective_x <= 2 * color_width)
		return (1);
	else
		return (2);
}

static inline t_color	get_non_intense_color(t_scale tex)
{
	t_elementor	*elementor;
	int			i;

	(void)tex;
	if (!game()->boss)
		cub_exit("No boss found", -1);
	elementor = (t_elementor *)game()->boss->data;
	if (elementor->stage == 0)
		return (get_element_col(elementor->element1));
	if (elementor->stage >= 1 && elementor->stage <= 3)
		i = animation_col(tex, elementor->animation_frame / TICKS_PER_FRAME, \
						elementor->stage + 1);
	else
		i = 0;
	if (i == 0)
		return (get_element_col(elementor->element1));
	else if (i == 1)
		return (get_element_col(elementor->element2));
	else
		return (get_element_col(elementor->element3));
	return (int_to_t_color(rgba_to_int(0, 0, 0, 0)));
}

t_color	get_elementor_cloak_color(t_scale tex)
{
	t_elementor	*elementor;
	t_color		normal_col;
	t_color		random_col;
	double		chance_of_random;

	elementor = (t_elementor *)game()->boss->data;
	normal_col = get_non_intense_color(tex);
	random_col = get_element_col(random_int(0, 3));
	if (elementor->death_animation < 0)
		return (normal_col);
	if (elementor->death_animation > LMNTOR_DEATH_ANIM_TICKS)
		return (random_col);
	chance_of_random = (double)elementor->death_animation / \
						LMNTOR_DEATH_ANIM_TICKS;
	if (random_val() < chance_of_random)
		return (random_col);
	else
		return (normal_col);
}
