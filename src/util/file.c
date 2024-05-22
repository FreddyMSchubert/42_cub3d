/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 12:31:28 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/22 12:33:19 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	*file_get_extension(char *path)
{
	return (ft_strrchr(path, '.'));
}

bool	file_is_valid_extension(char *path, char *extension)
{
	char	*ext;

	ext = file_get_extension(path);
	if (!ext)
		return (false);
	return (str_is_equal(ext, extension));
}
