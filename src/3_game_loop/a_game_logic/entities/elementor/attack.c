/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   attack.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 14:59:57 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 10:03:44 by freddy           ###   ########.fr       */
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
	t_transform	trans;

	trans.rot.x = player()->transform.pos.x - self->transform.pos.x;
	trans.rot.y = player()->transform.pos.y - self->transform.pos.y;
	self->transform.rot = scale_vector(self->transform.rot, 1);
	trans.pos = self->transform.pos;
	self->transform.rot = deg_to_dir_vec(\
		dir_vec_to_deg(self->transform.rot) + (random_val() * \
		LMNTOR_SHOOTING_INACCURACY_DEG - (LMNTOR_SHOOTING_INACCURACY_DEG / 2)));
	shooooot(trans, get_random_element(elem));
}

static inline void	spin_attack(t_entity *self, t_elementor *elem)
{
	t_transform	trans;
	int			i;
	int			count;
	int			degree;

	count = random_int(LMNTOR_SPIN_ATTACK_MIN_PROJECTILES, \
							LMNTOR_SPIN_ATTACK_MAX_PROJECTILES);
	degree = 0;
	i = 0;
	while (i < count)
	{
		trans.pos = self->transform.pos;
		trans.rot = deg_to_dir_vec(degree);
		shooooot(trans, get_random_element(elem));
		degree += 360 / count;
		i++;
	}
}

static inline void	summon_attack(t_entity *self, t_elementor *elem)
{
	int			count;
	int			i;
	t_transform	trans;
	t_entity	*ntt;
	t_blight	*blight;

	count = random_int(LMNTOR_SPAWN_ATTACK_MIN_BLIGHTS, \
						LMNTOR_SPAWN_ATTACK_MAX_BLIGHTS);
	i = 0;
	while (i < count)
	{
		trans.pos.x = self->transform.pos.x + random_val() + \
					LMNTOR_BLIGHT_SPAWN_DIST - (LMNTOR_BLIGHT_SPAWN_DIST / 2);
		trans.pos.y = self->transform.pos.y + random_val() + \
					LMNTOR_BLIGHT_SPAWN_DIST - (LMNTOR_BLIGHT_SPAWN_DIST / 2);
		trans.rot = deg_to_dir_vec(random_int(0, 360));
		ntt = create_entity(trans, BLIGHT_NTT, get_texture_blight, tick_blight);
		ntt->on_collision = on_collision_blight;
		blight = malloc(sizeof(t_blight));
		blight->element = get_random_element(elem);
		blight->drops_key = false;
		ntt->health = ENEMY_STARTING_HEALTH;
		ntt->data = blight;
		i++;
	}
}

void	elementor_attack(t_entity *self, t_elementor *elem)
{
	if (elem->death_animation >= 0)
		return ;
	if (random_val() > LMNTOR_ATTACK_CHANCE)
		return ;
	if (random_val() < LMNTOR_ATTACK_SPIN_CHANCE * elem->stage)
		spin_attack(self, elem);
	else if (random_val() < LMNTOR_ATTACK_SUMMON_CHANCE * elem->stage)
		summon_attack(self, elem);
	else
		normal_attack(self, elem);
}
