/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkauker <jkauker@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 08:37:47 by jkauker           #+#    #+#             */
/*   Updated: 2024/05/21 08:38:20 by jkauker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* ----- INCLUDES ----- */
#include "colors.h"

#include "../submodules/MLX42/include/MLX42/MLX42.h"
#include "../submodules/42_libft/libft.h"
#include "../submodules/42_get_next_line/get_next_line.h"

// subject functions
#include <fcntl.h>    // open, close
#include <unistd.h>   // read, write, close
#include <stdio.h>    // printf, perror
#include <stdlib.h>   // malloc, free, exit
#include <string.h>   // strerror
#include <math.h>     // All functions of the math library (-lm)

// other
#include <stdbool.h>

/* ----- RULES ----- */
#define GREETING true
#define VERBOSE true

/* ---- FUNCTIONS ----- */
// lets mirror the file system in here. the less ---, the deeper the file

// ----- util
// garbage collector
t_list		*gc_create(void);
int			gc_append_element(t_list *gc, void *content);
void		gc_cleanup_and_reinit(t_list **gc);
void		*gc_malloc(size_t size, t_list **gc, void *ptr1);
// printing
void		logger(char type, char *message);
void		verbose_logger(char type, char *message);

#endif