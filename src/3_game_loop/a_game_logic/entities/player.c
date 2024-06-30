/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 19:57:01 by freddy            #+#    #+#             */
/*   Updated: 2024/06/30 10:17:38 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// technically not an entity, don't worry about it!

# include "../../../include/cub3d.h"

void	on_collision_player(t_entity	*collider)
{
	int	health_decrease_amount;

	if (!(collider->type == PROJECTILE_NTT))
		return ;
	if (a_beats_b(((t_projectile *)collider->data)->element, player()->element))
		health_decrease_amount = MAJOR_PROJECTILE_HIT_DESCREASE;
	else
		health_decrease_amount = MINOR_PROJECTILE_HIT_DECREASE;
	player()->health -= health_decrease_amount;
	logger(LOGGER_ACTION, "Player took some damange. How embarrassing!");
	collider->to_be_deleted = true;
}

void	check_dead_player(void)
{
	if (player()->health > 0)
		return ;
	printf("%sYou died after %f seconds. Bruh%s\n", ANSI_BOLD_RED, mlx_get_time(), ANSI_RESET);
	cub_exit("Quitting program. Playing as a corpse is dull.", 0);
}
