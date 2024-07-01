/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logging.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:49:10 by fschuber          #+#    #+#             */
/*   Updated: 2024/06/30 16:01:45 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/*
	@brief	prints a message to the console
	@param	type	-	'e' for error, 
						'w' for warning,
						'i' for info,
						's' for step,
						'a' for action
	@param	message	- the message to print
*/
void	logger(char type, char *message)
{
	if (!message)
		return ;
	printf("[%.2f] ", mlx_get_time());
	if (type == 'e')
		printf("%sERROR%s: \t%s\n", ANSI_BOLD_RED, ANSI_RESET, message);
	else if (type == 'w')
		printf("%sWARN%s: \t%s\n", ANSI_BOLD_YELLOW, ANSI_RESET, message);
	else if (type == 'i')
		printf("%sINFO%s: \t%s\n", ANSI_BOLD_CYAN, ANSI_RESET, message);
	else if (type == 's')
		printf("%sSTEP%s: \t%s\n", ANSI_BOLD_GREEN, ANSI_RESET, message);
	else if (type == 'a')
		printf("%sACTION%s: %s\n", ANSI_BOLD_MAGENTA, ANSI_RESET, message);
	else
		printf("%s%s%s\n", ANSI_COLOR_WHITE, ANSI_RESET, message);
}

void	logger_verbose(char type, char *message)
{
	if (VERBOSE)
		logger(type, message);
}
