/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:59:57 by freddy            #+#    #+#             */
/*   Updated: 2024/07/07 23:20:53 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

#define ELEMENTOR_ATTACK_NONE 0
#define ELEMENTOR_ATTACK_NORMAL 1
#define ELEMENTOR_ATTACK_SPIN 2
#define ELEMENTOR_ATTACK_SUMMON 3

static inline int	get_random_element(t_elementor *elem)
{
	int			num;

	if (elem->stage == 0)
		return (elem->element1);
	else if (elem->stage == 1)
	{
		num = random_int(0, 1);
		if (num == 0)
			return (elem->element1);
		else
			return (elem->element2);
	}
	else
	{
		num = random_int(0, 2);
		if (num == 0)
			return (elem->element1);
		else if (num == 1)
			return (elem->element2);
		else if (num == 2)
			return (elem->element3);
	}
	return (elem->element1);
}

static inline void	normal_attack(t_entity *self, t_elementor *elem)
{
	t_trans	trans;

	trans.rot.x = player()->trans.pos.x - self->trans.pos.x;
	trans.rot.y = player()->trans.pos.y - self->trans.pos.y;
	self->trans.rot = scale_vector(self->trans.rot, 1);
	trans.pos = self->trans.pos;
	self->trans.rot = deg_to_dir_vec(\
		dir_vec_to_deg(self->trans.rot) + (random_val() * \
		LMNTOR_SHOOTING_INACCURACY_DEG - (LMNTOR_SHOOTING_INACCURACY_DEG / 2)));
	shooooot(trans, get_random_element(elem));
}

static inline void	spin_attack(t_entity *self, t_elementor *elem)
{
	t_trans		trans;
	int			i;
	int			count;
	int			degree;

	count = random_int(LMNTOR_SPIN_ATTACK_MIN_PROJECTILES, \
							LMNTOR_SPIN_ATTACK_MAX_PROJECTILES);
	degree = 0;
	i = 0;
	while (i < count)
	{
		trans.pos = self->trans.pos;
		trans.rot = deg_to_dir_vec(degree);
		shooooot(trans, get_random_element(elem));
		degree += 360 / count;
		i++;
	}
}

static inline void	summon_attack(t_entity *self, t_elementor *elem)
{
	t_trans		trans;
	t_entity	*ntt;
	t_blight	*blight;

	trans.pos.x = self->trans.pos.x + random_int(-LMNTOR_BLIGHT_SPAWN_DIST, \
													LMNTOR_BLIGHT_SPAWN_DIST);
	trans.pos.y = self->trans.pos.y + random_int(-LMNTOR_BLIGHT_SPAWN_DIST, \
													LMNTOR_BLIGHT_SPAWN_DIST);
	if (!is_position_valid(trans.pos.x, trans.pos.y))
		return ;
	trans.rot = deg_to_dir_vec(random_int(0, 360));
	ntt = create_entity(trans, BLIGHT_NTT, get_texture_blight, tick_blight);
	ntt->on_collision = on_collision_blight;
	blight = malloc(sizeof(t_blight));
	blight->element = get_random_element(elem);
	blight->drops_key = false;
	blight->state = BLIGHT_STATE_WALKING;
	ntt->health = ENEMY_STARTING_HEALTH;
	ntt->data = blight;
}

void	elementor_attack(t_entity *self, t_elementor *elem)
{
	if (elem->death_animation >= 0)
		return ;
	if (random_val() > LMNTOR_ATTACK_CHANCE || \
				(self->health <= 5 && random_val() > LMNTOR_ATTACK_CHANCE / 2))
		return ;
	if (random_val() < LMNTOR_ATTACK_SPIN_CHANCE * \
							elem->stage && self->health > 3)
		spin_attack(self, elem);
	else if (random_val() < LMNTOR_ATTACK_SUMMON_CHANCE * \
							elem->stage && self->health > 5)
		summon_attack(self, elem);
	else
		normal_attack(self, elem);
}
