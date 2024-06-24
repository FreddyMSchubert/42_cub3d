/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:45:22 by freddy            #+#    #+#             */
/*   Updated: 2024/06/24 14:20:04 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <stdbool.h>

// General

# define GREETING true
# define VERBOSE true
# define DEBUG false
# define LOG_WALLS false
# define TERMINAL_MAP true
# define MARK_DIRTY_LOGGING false

// Map limits

# define MAX_GOAL_COUNT 1

// Quality of Life

# define MOUSE_SENSITIVITY 0.35

// Window Setup

# define START_HEIGHT 540
# define START_WIDTH 960
# define WINDOW_NAME "cub3d"

// Player Movement Stats

# define MOVEMENT_SPEED 0.065
# define MOVEMENT_SPRINT_MULTIPLIER 2.5
# define TURN_SPEED_ARROWS_DEG 5
# define TURN_SPEED_MOUSE_DEG 1
# define WALL_COLLISION_MARGIN 0.25

// Display Settings

# define FOV_DEG 96
# define RAYCASTS_PER_DEG 5
# define FISHEYE_CORRECTION_FACTOR 0.5
# define VIEW_DIST 3
# define FPS 30

#endif