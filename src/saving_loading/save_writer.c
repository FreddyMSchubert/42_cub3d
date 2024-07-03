/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_writer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:00:41 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/03 11:54:42 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
	1. amount of hearts, in a char format
	2. amount of earth orbs, char
	3. amount of air orbs
	4. fire orbs
	5. water orbs
	6. player element
*/

static char	get_as_char(int input)
{
	if (input < CHAR_MIN)
		return (CHAR_MIN);
	else if (input > CHAR_MAX)
		return (CHAR_MAX);
	else
		return ((char) input);
}

static inline void	save_file(char *filename, char *data, int size)
{
	int		fd;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
	if (fd < 0)
	{
		logger_v(LOGGER_WARNING, "Failed to open save file");
		return ;
	}
	if (write(fd, data, size) != size)
	{
		logger_v(LOGGER_WARNING, "Failed to write to save file");
		close(fd);
		return ;
	}
	close(fd);
}

void	save_game(void)
{
	char	*data;

	logger_v(LOGGER_STEP, "Saving play data");
	data = malloc(sizeof(char) * 6);
	data[0] = get_as_char(player()->health);
	data[1] = get_as_char(player()->inv.earth_orbs);
	data[2] = get_as_char(player()->inv.air_orbs);
	data[3] = get_as_char(player()->inv.fire_orbs);
	data[4] = get_as_char(player()->inv.water_orbs);
	data[5] = get_as_char(player()->element);
	save_file(SAVE_FILE, data, 6);
	free(data);
}
