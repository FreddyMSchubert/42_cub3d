/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:18:50 by freddy            #+#    #+#             */
/*   Updated: 2024/07/03 17:05:51 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static mlx_texture_t	*l(char *path)
{
	mlx_texture_t	*texture;
	static int		textures = -1;

	if (textures == -1)
		ft_bzero(game()->texture_arr, MAX_TEXTURES);
	texture = mlx_load_png(path);
	if (!texture)
		cub_exit("Error loading texture", -1);
	game()->texture_arr[++textures] = texture;
	printf("added: %p\n", texture);
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

static inline void	load_status_animatons(void)
{
	game()->frame_hurt = l("assets/textures/hud/hurt.png");
	game()->frame_win = l("assets/textures/hud/win_screen.png");
	game()->frame_dead = l("assets/textures/hud/dead_screen.png");
}

void	load_static_textures(void)
{
	game()->textures.door = l("assets/textures/entities/door.png");
	game()->textures.key = l("assets/textures/entities/key.png");
	game()->textures.goal = l("assets/textures/entities/goal.png");
	game()->textures.health = l("assets/textures/entities/health.png");
	game()->textures.water_orb = l("assets/textures/entities/orbs/water.png");
	game()->textures.fire_orb = l("assets/textures/entities/orbs/fire.png");
	game()->textures.earth_orb = l("assets/textures/entities/orbs/earth.png");
	game()->textures.air_orb = l("assets/textures/entities/orbs/air.png");
	game()->textures.hotbar = l("assets/textures/hud/hotbar.png");
	game()->textures.hotbar_select = l("assets/textures/hud/hotbar_select.png");
	load_status_animatons();
	load_blight_textures();
}
