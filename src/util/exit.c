/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:51:31 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 15:23:46 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static inline void	free_textures2(void)
{
	if (game()->textures.earth_orb)
		mlx_delete_texture(game()->textures.earth_orb);
	if (game()->textures.air_orb)
		mlx_delete_texture(game()->textures.air_orb);
	if (game()->textures.door)
		mlx_delete_texture(game()->textures.door);
	if (game()->textures.water_orb)
		mlx_delete_texture(game()->textures.water_orb);
	if (game()->textures.water_blight_attack.frame1)
		mlx_delete_texture(game()->textures.water_blight_attack.frame1);
	if (game()->textures.water_blight_attack.frame2)
		mlx_delete_texture(game()->textures.water_blight_attack.frame2);
	if (game()->textures.water_blight_attack.frame3)
		mlx_delete_texture(game()->textures.water_blight_attack.frame3);
	if (game()->textures.air_blight_attack.frame1)
		mlx_delete_texture(game()->textures.air_blight_attack.frame1);
	if (game()->textures.air_blight_attack.frame2)
		mlx_delete_texture(game()->textures.air_blight_attack.frame2);
	if (game()->textures.air_blight_attack.frame3)
		mlx_delete_texture(game()->textures.air_blight_attack.frame3);
	if (game()->textures.fire_blight_attack.frame1)
		mlx_delete_texture(game()->textures.fire_blight_attack.frame1);
	if (game()->textures.fire_blight_attack.frame2)
		mlx_delete_texture(game()->textures.fire_blight_attack.frame2);
	if (game()->textures.fire_blight_attack.frame3)
		mlx_delete_texture(game()->textures.fire_blight_attack.frame3);
	if (game()->textures.earth_blight_attack.frame1)
		mlx_delete_texture(game()->textures.earth_blight_attack.frame1);
	if (game()->textures.earth_blight_attack.frame2)
		mlx_delete_texture(game()->textures.earth_blight_attack.frame2);
	if (game()->textures.earth_blight_attack.frame3)
		mlx_delete_texture(game()->textures.earth_blight_attack.frame3);
	if (game()->textures.earth_blight_death.frame1)
		mlx_delete_texture(game()->textures.earth_blight_death.frame1);
	if (game()->textures.earth_blight_death.frame2)
		mlx_delete_texture(game()->textures.earth_blight_death.frame2);
	if (game()->textures.earth_blight_death.frame3)
		mlx_delete_texture(game()->textures.earth_blight_death.frame3);
	if (game()->textures.air_blight_death.frame1)
		mlx_delete_texture(game()->textures.air_blight_death.frame1);
	if (game()->textures.air_blight_death.frame2)
		mlx_delete_texture(game()->textures.air_blight_death.frame2);
	if (game()->textures.air_blight_death.frame3)
		mlx_delete_texture(game()->textures.air_blight_death.frame3);
	if (game()->textures.water_blight_death.frame1)
		mlx_delete_texture(game()->textures.water_blight_death.frame1);
	if (game()->textures.water_blight_death.frame2)
		mlx_delete_texture(game()->textures.water_blight_death.frame2);
	if (game()->textures.water_blight_death.frame3)
		mlx_delete_texture(game()->textures.water_blight_death.frame3);
	if (game()->textures.fire_blight_death.frame1)
		mlx_delete_texture(game()->textures.fire_blight_death.frame1);
	if (game()->textures.fire_blight_death.frame2)
		mlx_delete_texture(game()->textures.fire_blight_death.frame2);
	if (game()->textures.fire_blight_death.frame3)
		mlx_delete_texture(game()->textures.fire_blight_death.frame3);
}

static inline void	free_textures(void)
{
	if (game()->ea_texture)
		mlx_delete_texture(game()->ea_texture);
	if (game()->no_texture)
		mlx_delete_texture(game()->no_texture);
	if (game()->so_texture)
		mlx_delete_texture(game()->so_texture);
	if (game()->we_texture)
		mlx_delete_texture(game()->we_texture);
	if (game()->textures.air_blight_idle)
		mlx_delete_texture(game()->textures.air_blight_idle);
	if (game()->textures.earth_blight_idle)
		mlx_delete_texture(game()->textures.earth_blight_idle);
	if (game()->textures.fire_blight_idle)
		mlx_delete_texture(game()->textures.fire_blight_idle);
	if (game()->textures.water_blight_idle)
		mlx_delete_texture(game()->textures.water_blight_idle);
	if (game()->textures.goal)
		mlx_delete_texture(game()->textures.goal);
	if (game()->textures.key)
		mlx_delete_texture(game()->textures.key);
	if (game()->textures.fire_orb)
		mlx_delete_texture(game()->textures.fire_orb);
	free_textures2();
}

void	cub_exit(char	*message, int code)
{
	if (code != 0)
		logger(LOGGER_ERROR, message);
	else
		logger(LOGGER_INFO, message);
	free_textures();
	if (game()->mlx)
		mlx_terminate(game()->mlx);
	gc_exit(code);
}
