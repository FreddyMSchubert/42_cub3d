/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 22:52:39 by freddy            #+#    #+#             */
/*   Updated: 2024/06/06 10:30:37 by fschuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	random_int(int min, int max)
{
	int				fd;
	unsigned int	bytes_read;
	int				ret_val;

	fd = open("/dev/random", O_RDONLY);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	ret_val = read(fd, &bytes_read, sizeof(bytes_read));
	if (ret_val < 0)
	{
		perror("read");
		close(fd);
		exit(1);
	}
	else if (ret_val != sizeof(bytes_read))
	{
		fprintf(stderr, "Failed to read enough bytes for an integer\n");
		close(fd);
		exit(1);
	}
	close(fd);
	return (bytes_read % (max - min + 1) + min);
}
