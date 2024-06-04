/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persistent_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:03:38 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/04 10:39:10 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_persistent_data	*game(void)
{
	static t_persistent_data	game;

	return (&game);
}

t_list	**get_gc(void)
{
	static t_list	*gc;

	if (!gc)
		gc = gc_create();
	return (&gc);
}

t_entity	*player(void)
{
	static t_entity	player;

	return (&player);
}
