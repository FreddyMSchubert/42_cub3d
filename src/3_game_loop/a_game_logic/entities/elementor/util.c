/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:36:49 by freddy            #+#    #+#             */
/*   Updated: 2024/07/06 20:29:48 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	refresh_projectiles(t_elementor *elementor)
{
	bool	valid_config;
	int		el1;
	int		el2;
	int		el3;

	if (elementor->stage == 0)
	{
		elementor->element1 = random_int(0, 3);
		return ;
	}
	valid_config = false;
	while (!valid_config)
	{
		el1 = random_int(0, 3);
		el2 = random_int(0, 3);
		el3 = random_int(0, 3);
		if (el1 != el2 && el1 != el3 && el2 != el3 && \
			el1 != elementor->element1 && el2 != elementor->element2 && \
			el3 != elementor->element3)
			valid_config = true;
	}
	elementor->element1 = el1;
	elementor->element2 = el2;
	elementor->element3 = el3;
}