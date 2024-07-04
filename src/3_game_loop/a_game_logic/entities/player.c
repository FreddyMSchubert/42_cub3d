/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:57:01 by freddy            #+#    #+#             */
/*   Updated: 2024/07/04 11:26:20 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// technically not an entity, don't worry about it!

#include "../../../include/cub3d.h"

#define PLAYER_DAMAGE_EVERY_X_FRAMES 3

static inline void	handle_blight_collision(t_entity *collider)
{
	static int		hits;

	if (collider->type != BLIGHT_NTT || \
			((t_blight *)collider->data)->element == player()->element || \
			pos_dist(player()->transform.pos, \
			get_face_vector(collider).pos) > 1)
		return ;
	hits++;
	if (hits < PLAYER_DAMAGE_EVERY_X_FRAMES)
		return ;
	hits = 0;
	player()->health -= PLAYER_BLIGHT_COLLISION_DAMAGE;
	logger_v(LOGGER_ACTION, "Player took some damage from a blight. Ouch!");
}

void	on_collision_player(t_entity	*collider)
{
	int			health_decrease_amount;
	mlx_image_t	*frame_hurt;

	if (collider->type == BLIGHT_NTT)
		handle_blight_collision(collider);
	if (!(collider->type == PROJECTILE_NTT))
		return ;
	if (a_beats_b(((t_projectile *)collider->data)->element, player()->element))
		health_decrease_amount = MAJOR_PROJECTILE_HIT_DESCREASE;
	else
		health_decrease_amount = MINOR_PROJECTILE_HIT_DECREASE;
	player()->health -= health_decrease_amount;
	frame_hurt = mlx_new_image(game()->mlx, game()->mlx->width,
			game()->mlx->height);
	if (game()->screen_effect)
		mlx_delete_image(game()->mlx, game()->screen_effect);
	mlx_image_to_window(game()->mlx, frame_hurt, 0, 0);
	game()->screen_effect = frame_hurt;
	screen_texture_draw(game()->frame_hurt, (t_scale){0, 0},
		(t_scale){game()->mlx->width, game()->mlx->height});
	game()->screen_effect_end = mlx_get_time() + 0.3;
	logger_v(LOGGER_ACTION, "Player took some damange. How embarrassing!");
	collider->to_be_deleted = true;
}

void	check_dead_player(void)
{
	if (player()->health > 0)
		return ;
	printf("%sYou died after %f seconds. Bruh.%s\n", \
					ANSI_BOLD_RED, mlx_get_time(), ANSI_RESET);
	game()->game_over = true;
}
