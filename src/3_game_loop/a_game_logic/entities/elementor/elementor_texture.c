/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   elementor_texture.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 13:37:41 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/05 17:57:01 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

mlx_texture_t	*get_texture_elementor(t_entity *self)
{
	t_elementor	*lmntor;

	lmntor = (t_elementor *)self->data;
	if (lmntor->hurt_state > 0)
		return (game()->textures.elementor_hurt);
	return (game()->textures.elementor_idle);
}
