/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:18:50 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 13:49:29 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static mlx_texture_t	*l(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		cub_exit("Error loading texture", -1);
	return (texture);
}

static void	load_animation_textures(char *base_path, t_animation *animation)
{
	char	*str;

	str = ft_strjoin(base_path, "1.png");
	if (!str)
		cub_exit("Error loading texture", -1);
	animation->frame1 = l(str);
	free(str);
	str = ft_strjoin(base_path, "2.png");
	if (!str)
		cub_exit("Error loading texture", -1);
	animation->frame2 = l(str);
	free(str);
	str = ft_strjoin(base_path, "3.png");
	if (!str)
		cub_exit("Error loading texture", -1);
	animation->frame3 = l(str);
	free(str);
}

static void	load_blight_textures(void)
{
	game()->textures.air_blight_idle = \
					l("assets/textures/entities/blights/air/idle.png");
	load_animation_textures("assets/textures/entities/blights/air/death", \
					&game()->textures.air_blight_death);
	load_animation_textures("assets/textures/entities/blights/air/attack", \
					&game()->textures.air_blight_attack);
	game()->textures.fire_blight_idle = \
					l("assets/textures/entities/blights/fire/idle.png");
	load_animation_textures("assets/textures/entities/blights/fire/death", \
					&game()->textures.fire_blight_death);
	load_animation_textures("assets/textures/entities/blights/fire/attack", \
					&game()->textures.fire_blight_attack);
	game()->textures.water_blight_idle = \
					l("assets/textures/entities/blights/water/idle.png");
	load_animation_textures("assets/textures/entities/blights/water/death", \
					&game()->textures.water_blight_death);
	load_animation_textures("assets/textures/entities/blights/water/attack", \
					&game()->textures.water_blight_attack);
	game()->textures.earth_blight_idle = \
					l("assets/textures/entities/blights/earth/idle.png");
	load_animation_textures("assets/textures/entities/blights/earth/death", \
					&game()->textures.earth_blight_death);
	load_animation_textures("assets/textures/entities/blights/earth/attack", \
					&game()->textures.earth_blight_attack);
}

void	load_static_textures(void)
{
	game()->textures.door = l("assets/textures/entities/door.png");
	game()->textures.key = l("assets/textures/entities/key.png");
	game()->textures.goal = l("assets/textures/entities/goal.png");
	game()->textures.water_orb = l("assets/textures/entities/orbs/water.png");
	game()->textures.fire_orb = l("assets/textures/entities/orbs/fire.png");
	game()->textures.earth_orb = l("assets/textures/entities/orbs/earth.png");
	game()->textures.air_orb = l("assets/textures/entities/orbs/air.png");
	load_blight_textures();
}
