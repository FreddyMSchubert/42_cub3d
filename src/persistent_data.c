/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   persistent_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 14:03:38 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/21 14:28:45 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_persistent_data	*get_persistent_data(void)
{
	static t_persistent_data	data;

	return (&data);
}

t_list	**get_gc(void)
{
	static t_list	*gc;

	if (!gc)
		gc = gc_create();
	return (&gc);
}
