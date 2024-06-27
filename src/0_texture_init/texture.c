/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:18:50 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 20:50:59 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static mlx_texture_t	*load_texture(char *path)
{
	mlx_texture_t	*texture;

	texture = mlx_load_png(path);
	if (!texture)
		cub_exit("Error loading texture", -1);
	return (texture);
}

void	load_static_textures(void)
{
	game()->textures.door = load_texture("assets/entities/door.png");
	game()->textures.key = load_texture("assets/entities/key.png");
	game()->textures.goal = load_texture("assets/entities/goal.png");
	game()->textures.water_orb = load_texture("assets/entities/orbs/water.png");
	game()->textures.fire_orb = load_texture("assets/entities/orbs/fire.png");
	game()->textures.earth_orb = load_texture("assets/entities/orbs/earth.png");
	game()->textures.air_orb = load_texture("assets/entities/orbs/air.png");
	game()->textures.air_blight_idle = load_texture("assets/entities/blights/air/idle.png");
	game()->textures.air_blight_death1 = load_texture("assets/entities/blights/air/death1.png");
	game()->textures.air_blight_death2 = load_texture("assets/entities/blights/air/death2.png");
	game()->textures.air_blight_death3 = load_texture("assets/entities/blights/air/death3.png");
	game()->textures.fire_blight_idle = load_texture("assets/entities/blights/fire/idle.png");
	game()->textures.fire_blight_death1 = load_texture("assets/entities/blights/fire/death1.png");
	game()->textures.fire_blight_death2 = load_texture("assets/entities/blights/fire/death2.png");
	game()->textures.fire_blight_death3 = load_texture("assets/entities/blights/fire/death3.png");
	game()->textures.water_blight_idle = load_texture("assets/entities/blights/water/idle.png");
	game()->textures.water_blight_death1 = load_texture("assets/entities/blights/water/death1.png");
	game()->textures.water_blight_death2 = load_texture("assets/entities/blights/water/death2.png");
	game()->textures.water_blight_death3 = load_texture("assets/entities/blights/water/death3.png");
	game()->textures.earth_blight_idle = load_texture("assets/entities/blights/earth/idle.png");
	game()->textures.earth_blight_death1 = load_texture("assets/entities/blights/earth/death1.png");
	game()->textures.earth_blight_death2 = load_texture("assets/entities/blights/earth/death2.png");
	game()->textures.earth_blight_death3 = load_texture("assets/entities/blights/earth/death3.png");
}
