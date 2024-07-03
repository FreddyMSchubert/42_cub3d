/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_loader.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:10:07 by fschuber          #+#    #+#             */
/*   Updated: 2024/07/03 11:56:40 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	load_save(void)
{
	char	data[6];
	int		fd;
	int		read_bytes;

	logger_v(LOGGER_STEP, "Loading save file");
	fd = open(SAVE_FILE, O_RDONLY);
	if (fd < 0)
	{
		logger_v(LOGGER_ERROR, "Failed to open save file");
		return ;
	}
	read_bytes = read(fd, data, 6);
	if (read_bytes < (int) sizeof(data))
	{
		logger(LOGGER_ERROR, "Failed to read save file, corrupted data");
		close(fd);
		return ;
	}
	player()->health = (int)data[0];
	player()->inv.earth_orbs = (int)data[1];
	player()->inv.air_orbs = (int)data[2];
	player()->inv.fire_orbs = (int)data[3];
	player()->inv.water_orbs = (int)data[4];
	player()->element = (int)data[5];
	close(fd);
}
