/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 10:56:39 by freddy            #+#    #+#             */
/*   Updated: 2024/05/30 10:59:19 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	degrees_to_radians(double degrees)
{
	return (degrees / (M_PI / 180.0));
}

double	radians_to_degrees(double radians)
{
	return (radians * (180.0 / M_PI));
}
