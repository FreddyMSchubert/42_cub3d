/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blights.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:15:22 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 14:17:58 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

bool	a_beats_b(int a, int b)
{
	return (b == a + 1 || (b == 0 && a == 3));
}
