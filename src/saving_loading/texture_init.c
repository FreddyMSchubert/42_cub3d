/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:18:50 by freddy            #+#    #+#             */
/*   Updated: 2024/07/04 17:20:45 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static mlx_texture_t	*l(char *path)
{
	mlx_texture_t	*texture;
	char			*fullpath;
	static int		textures = 0;

	if (textures + 1 >= MAX_TEXTURES)
		cub_exit("Texture amount exceeds max allowed textures", -1);
	if (textures == -1)
		ft_bzero(game()->texture_arr, MAX_TEXTURES);
	fullpath = ft_strjoin("assets/textures/", path);
	if (!fullpath)
		cub_exit("Error loading texture", -1);
	texture = mlx_load_png(fullpath);
	if (!texture)
	{
		free(fullpath);
		printf("Problem texture: <assets/textures/%s>\n", path);
		cub_exit("Error loading texture", -1);
	}
	free(fullpath);
	game()->texture_arr[textures++] = texture;
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
					l("entities/blights/air/idle.png");
	load_animation_textures("entities/blights/air/death", \
					&game()->textures.air_blight_death);
	load_animation_textures("entities/blights/air/attack", \
					&game()->textures.air_blight_attack);
	game()->textures.fire_blight_idle = \
					l("entities/blights/fire/idle.png");
	load_animation_textures("entities/blights/fire/death", \
					&game()->textures.fire_blight_death);
	load_animation_textures("entities/blights/fire/attack", \
					&game()->textures.fire_blight_attack);
	game()->textures.water_blight_idle = \
					l("entities/blights/water/idle.png");
	load_animation_textures("entities/blights/water/death", \
					&game()->textures.water_blight_death);
	load_animation_textures("entities/blights/water/attack", \
					&game()->textures.water_blight_attack);
	game()->textures.earth_blight_idle = \
					l("entities/blights/earth/idle.png");
	load_animation_textures("entities/blights/earth/death", \
					&game()->textures.earth_blight_death);
	load_animation_textures("entities/blights/earth/attack", \
					&game()->textures.earth_blight_attack);
}

static inline void	load_status_animatons(void)
{
	game()->frame_hurt = l("hud/hurt.png");
	game()->frame_win = l("hud/win_screen.png");
	game()->frame_dead = l("hud/dead_screen.png");
	game()->textures.air_blight_hurt = l("entities/blights/air/hurt.png");
	game()->textures.fire_blight_hurt = l("entities/blights/fire/hurt.png");
	game()->textures.water_blight_hurt = l("entities/blights/water/hurt.png");
	game()->textures.earth_blight_hurt = l("entities/blights/earth/hurt.png");
}

void	load_static_textures(void)
{
	game()->textures.elements_overview = l("hud/elements_overview.png");
	game()->textures.door = l("entities/door.png");
	game()->textures.key = l("entities/key.png");
	game()->textures.goal = l("entities/goal.png");
	game()->textures.health = l("entities/health.png");
	game()->textures.key_floor = l("entities/key_floor.png");
	game()->textures.health_floor = l("entities/health_floor.png");
	game()->textures.water_orb = l("entities/orbs/water.png");
	game()->textures.fire_orb = l("entities/orbs/fire.png");
	game()->textures.earth_orb = l("entities/orbs/earth.png");
	game()->textures.air_orb = l("entities/orbs/air.png");
	game()->textures.water_orb_floor = l("entities/orbs/water_floor.png");
	game()->textures.fire_orb_floor = l("entities/orbs/fire_floor.png");
	game()->textures.earth_orb_floor = l("entities/orbs/earth_floor.png");
	game()->textures.air_orb_floor = l("entities/orbs/air_floor.png");
	game()->textures.water_orb_flying = l("entities/orbs/water_flying.png");
	game()->textures.fire_orb_flying = l("entities/orbs/fire_flying.png");
	game()->textures.earth_orb_flying = l("entities/orbs/earth_flying.png");
	game()->textures.air_orb_flying = l("entities/orbs/air_flying.png");
	game()->textures.hotbar = l("hud/hotbar.png");
	game()->textures.hotbar_select = l("hud/hotbar_select.png");
	load_status_animatons();
	load_blight_textures();
}
