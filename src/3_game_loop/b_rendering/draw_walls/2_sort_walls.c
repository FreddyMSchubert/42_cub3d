/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_sort_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:14:27 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/11 14:32:15 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static double	get_wall_distance(t_transform wall)
{
	t_vec2	new_wall_pos;

	new_wall_pos = wall.pos;
	if (wall.rot.x != 0.0)
		new_wall_pos.x += 0.5;
	else
		new_wall_pos.y += 0.5;
	return (pos_distance(player()->transform.pos, new_wall_pos));
}

static void	swap(t_transform *a, t_transform *b)
{
	t_transform	t;

	t = *a;
	*a = *b;
	*b = t;
}

static int	partition(t_transform arr[], int low, int high)
{
	double	pivot;
	int		i;
	int		k;

	pivot = get_wall_distance(arr[high]);
	i = (low - 1);
	k = low;
	while (k <= high - 1)
	{
		if (get_wall_distance(arr[k]) > pivot)
		{
			i++;
			swap(&arr[i], &arr[k]);
		}
		k++;
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

void	quick_sort_walls(t_transform arr[], int low, int high)
{
	int	pi;

	if (low < high)
	{
		pi = partition(arr, low, high);
		quick_sort_walls(arr, low, pi - 1);
		quick_sort_walls(arr, pi + 1, high);
	}
}
