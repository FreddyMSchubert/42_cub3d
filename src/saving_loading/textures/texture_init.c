/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 20:18:50 by freddy            #+#    #+#             */
/*   Updated: 2024/07/07 15:07:27 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

mlx_texture_t	*l(char *path);
void			load_orbs(void);
void			load_animation_textures(char *base_path, t_animation *anim);

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

static inline void	load_elements_overview_textures(void)
{
	game()->textures.elements_overview = l("hud/elements_overview/main.png");
	game()->textures.hightlight_air = l("hud/elements_overview/air.png");
	game()->textures.hightlight_fire = l("hud/elements_overview/fire.png");
	game()->textures.hightlight_water = l("hud/elements_overview/water.png");
	game()->textures.hightlight_earth = l("hud/elements_overview/earth.png");
}

static inline void	load_explosion(void)
{
	game()->textures.explosion_1 = l("entities/explosion/1.png");
	game()->textures.explosion_2 = l("entities/explosion/2.png");
	game()->textures.explosion_3 = l("entities/explosion/3.png");
	game()->textures.explosion_4 = l("entities/explosion/4.png");
	game()->textures.explosion_5 = l("entities/explosion/5.png");
	game()->textures.explosion_6 = l("entities/explosion/6.png");
	game()->textures.explosion_7 = l("entities/explosion/7.png");
	game()->textures.explosion_8 = l("entities/explosion/8.png");
	game()->textures.explosion_9 = l("entities/explosion/9.png");
	game()->textures.explosion_10 = l("entities/explosion/10.png");
}

void	load_static_textures(void)
{
	game()->textures.door = l("entities/door.png");
	game()->textures.key = l("entities/key.png");
	game()->textures.goal = l("entities/goal.png");
	game()->textures.health = l("hud/health.png");
	game()->textures.health_boss = l("hud/health_boss.png");
	game()->textures.key_floor = l("entities/key_floor.png");
	game()->textures.health_floor = l("entities/health_floor.png");
	game()->textures.hotbar = l("hud/hotbar.png");
	game()->textures.hotbar_select = l("hud/hotbar_select.png");
	load_status_animatons();
	load_blight_textures();
	load_elements_overview_textures();
	load_explosion();
	load_orbs();
	game()->textures.elementor_idle = l("entities/elementor/opacity.png");
	game()->textures.elementor_hurt = l("entities/elementor/hurt.png");
}
