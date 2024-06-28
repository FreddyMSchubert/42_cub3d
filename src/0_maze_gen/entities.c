/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 19:33:03 by freddy            #+#    #+#             */
/*   Updated: 2024/06/28 20:25:35 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../../include/cub3d.h"

// will not verify whether pos is valid
static void	place_blight(char **maze, t_scale pos)
{
	int		type_i;
	char	type_c;

	type_i = random_int(0, 3);
	if (type_i == 0)
		type_c = 'q';
	else if (type_i == 1)
		type_c = 'd';
	else if (type_i == 2)
		type_c = 'r';
	else
		type_c = 's';
	maze[pos.y][pos.x] = type_c;
}

// will not verify whether pos is valid
static void	place_orb(char **maze, t_scale pos)
{
	int		type_i;
	char	type_c;

	type_i = random_int(0, 3);
	if (type_i == 0)
		type_c = 'f';
	else if (type_i == 1)
		type_c = 'e';
	else if (type_i == 2)
		type_c = 'a';
	else
		type_c = 'w';
	maze[pos.y][pos.x] = type_c;
}

// the more walls a given space is surrounded by, the more likely the entity is to be an orb, and vice versa a blight
void	add_ntts_in_good_spots(char **maze, t_scale scale)
{
	int	y;
	int	x;
	int	wall_count;
	int	orb_chance;

	y = 0;
	while (++y < scale.y - 1)
	{
		x = 0;
		while (++x < scale.x - 1)
		{
			if (maze[y][x] == '1')
				continue ;
			wall_count = 0;
			wall_count += maze[y - 1][x] == '1';
			wall_count += maze[y + 1][x] == '1';
			wall_count += maze[y][x - 1] == '1';
			wall_count += maze[y][x + 1] == '1';
			if (random_int(1, 100) < ENTITIY_PLACEMENT_CHANCE && maze[y][x] == '0')
			{
				orb_chance = wall_count * (100 / 3);
				if (random_int(1, 100) < orb_chance)
				{
					if (random_int(1, 100) < ORB_PLACEMENT_CHANCE)
						place_orb(maze, (t_scale){x, y});
				}
				else
				{
					if (random_int(1, 100) < BLIGHT_PLACEMENT_CHANCE)
						place_blight(maze, (t_scale){x, y});
				}
			}
		}
	}
}
