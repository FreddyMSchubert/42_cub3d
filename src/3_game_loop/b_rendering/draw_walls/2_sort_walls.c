/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_sort_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 10:14:27 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/07 11:26:40 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../../include/cub3d.h"

static double	get_wall_distance(t_transform wall)
{
	return (pos_distance(player()->transform.pos, wall.pos));
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
