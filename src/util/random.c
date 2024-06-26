/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 22:02:22 by freddy            #+#    #+#             */
/*   Updated: 2024/06/26 22:17:20 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	random_val(void)
{
	double	time_val;

	time_val = mlx_get_time();
	return (time_val - (int)time_val);
}

int	random_int(int min, int max)
{
	double	scaled;

	scaled = random_val() * (max - min + 1);
	return ((int)(scaled + min));
}
