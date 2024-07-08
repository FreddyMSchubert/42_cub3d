/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inventory_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 14:23:39 by jkauker           #+#    #+#             */
/*   Updated: 2024/07/08 12:45:39 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	*get_amount_of_item(int index)
{
	if (index == 0)
		return (&(player()->inv.keys));
	else if (index == TYPE_WATER + 1)
		return (&(player()->inv.water_orbs));
	else if (index == TYPE_FIRE + 1)
		return (&(player()->inv.fire_orbs));
	else if (index == TYPE_EARTH + 1)
		return (&(player()->inv.earth_orbs));
	else if (index == TYPE_AIR + 1)
		return (&(player()->inv.air_orbs));
	return (0);
}

mlx_texture_t	*get_tex_by_index(int index)
{
	mlx_texture_t	*tex;

	if (!*get_amount_of_item(index) || index < 0
		|| index > player()->inv.num_available_items)
		return (NULL);
	if (index == 0)
		tex = game()->textures.key;
	else if (index == TYPE_WATER + 1)
		tex = game()->textures.water_orb;
	else if (index == TYPE_FIRE + 1)
		tex = game()->textures.fire_orb;
	else if (index == TYPE_EARTH + 1)
		tex = game()->textures.earth_orb;
	else if (index == TYPE_AIR + 1)
		tex = game()->textures.air_orb;
	else
		tex = NULL;
	return (tex);
}

mlx_image_t	**get_amount_text_by_index(int index)
{
	if (index == 0)
		return (&(player()->inv.text_amount_key));
	else if (index == TYPE_WATER + 1)
		return (&(player()->inv.text_amount_water));
	else if (index == TYPE_FIRE + 1)
		return (&(player()->inv.text_amount_fire));
	else if (index == TYPE_EARTH + 1)
		return (&(player()->inv.text_amount_earth));
	else
		return (&(player()->inv.text_amount_air));
}
