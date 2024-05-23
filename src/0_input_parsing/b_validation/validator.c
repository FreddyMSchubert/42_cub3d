/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 10:54:38 by fschuber          #+#    #+#             */
/*   Updated: 2024/05/23 14:24:43 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

bool	check_wall_valid(t_input_data *data, int x, int y)
{
	if (!data->map || x == 0 || y == 0 || !data->map[y] || !data->map[y][x])
		return (false);
	if (!data->map[y + 1])
		return (false);
	if (!data->map[y - 1])
		return (false);
	if (!data->map[y][x + 1])
		return (false);
	if (!data->map[y][x - 1])
		return (false);
	if (*data->map[y + 1][x] == VOID)
		return (false);
	if (*data->map[y - 1][x] == VOID)
		return (false);
	if (*data->map[y][x + 1] == VOID)
		return (false);
	if (*data->map[y][x - 1] == VOID)
		return (false);
	return (true);
}

void	validate(void)
{
	t_input_data	*data;
	int				x;
	int				y;

	data = get_persistent_data()->input_data;
	y = 0;
	while (data->map && data->map[y] != NULL)
	{
		x = 0;
		while (data->map[y][x] != NULL)
		{
			if ((*data->map[y][x] == FLOOR && !check_wall_valid(data, x, y)) ||
				(*data->map[y][x] < VOID || *data->map[y][x] > WALL))
			{
				logger('e', "Invalid map.");
				gc_exit_error();
			}
			x++;
		}
		y++;
	}
}

// ----- TESTER
/*
t_tile_type ***create_map() {
    t_tile_type*** map = malloc(6 * sizeof(t_tile_type**));
    if (map == NULL) {
        perror("Failed to allocate map");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 5; i++) {
        map[i] = malloc(6 * sizeof(t_tile_type*));
        if (map[i] == NULL) {
            perror("Failed to allocate row");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < 5; j++) {
            map[i][j] = malloc(sizeof(t_tile_type));
            if (map[i][j] == NULL) {
                perror("Failed to allocate cell");
                exit(EXIT_FAILURE);
            }
            *map[i][j] = WALL;
        }
        map[i][5] = NULL;
    }
    map[5] = NULL;

    *map[1][1] = FLOOR; *map[1][2] = FLOOR; *map[1][3] = FLOOR;
    *map[2][1] = FLOOR; *map[2][3] = FLOOR;
    *map[3][1] = FLOOR; *map[3][2] = FLOOR; *map[3][3] = FLOOR;

    return map;
}


int main()
{
    t_input_data data;
    data->map = create_map();
    validate(data);
    // *data->map[1][1] = VOID;
	printf("data->map[2][0] was %d, ", *data->map[2][0]);
	*data->map[2][4] = FLOOR;
	printf("now it is %d\n", *data->map[2][0]);
    validate(data);

    // Free memory
    for (int i = 0; data->map[i] != NULL; i++) {
        free(data->map[i]);
    }
    free(data->map);

    return 0;
}
*/