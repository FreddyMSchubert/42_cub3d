/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persistent_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:03:38 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/25 18:37:46 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_persistent_data	*game(void)
{
	static t_persistent_data	game;

	return (&game);
}

t_list	**gc(void)
{
	static t_list	*gc;

	if (!gc)
		gc = gc_create();
	return (&gc);
}

// pass a negative value to also just get player1
// in singleplayer only player 1 will be used
t_player	*player(int id)
{
	static t_player	player1;
	static t_player	player2;

	if (id == 1)
		return (&player2);
	return (&player1);
}
