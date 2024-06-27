/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: freddy <freddy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:45:22 by freddy            #+#    #+#             */
/*   Updated: 2024/06/27 21:25:31 by freddy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SETTINGS_H
# define SETTINGS_H

# include <stdbool.h>

// --- General

# define GREETING true
# define VERBOSE true
# define DEBUG false
# define LOG_WALLS false
# define TERMINAL_MAP true
# define MARK_DIRTY_LOGGING false

// --- Debug

# define RENDER_ENTITIES_THROUGH_WALLS false

// --- Quality of Life

# define MOUSE_SENSITIVITY 0.45

// --- Window Setup

# define START_HEIGHT 540
# define START_WIDTH 960
# define WINDOW_NAME "cub3d"

// --- Player Movement Stats

# define MOVEMENT_SPEED 0.08
# define MOVEMENT_SPRINT_MULTIPLIER 2
# define TURN_SPEED_ARROWS_DEG 5
# define TURN_SPEED_MOUSE_DEG 1
# define WALL_COLLISION_MARGIN 0.25

// --- Display Settings

# define FOV_DEG 96
# define RAYCASTS_PER_DEG 5
# define FISHEYE_CORRECTION_FACTOR 0.5
# define VIEW_DIST 3
# define FPS 30

// --- Entities

// collisions

# define GOAL_COLLISION_DISTANCE 0.5
# define KEY_COLLISION_DISTANCE 0.5
# define CLOSED_DOOR_ALLOWED_WALK_DISTANCE 0.4
# define DOOR_OPEN_DISTANCE 1.0
# define DEFAULT_COLLISION_DISTANCE 0.5

// speed

# define DOOR_OPEN_SPEED 0.05
# define PROJECTILE_SPEED 0.1
# define BLIGHT_SPEED 0.05

// movement

# define BLIGHT_WALKING_START_CHANCE 0.06
# define BLIGHT_STANDING_START_CHANCE 0.01
# define BLIGHT_MOVEMENT_ROTATION_SWITCH_CHANCE 0.05
# define BLIGHT_MINIUM_ROTATION_DEG 45
# define BLIGHT_MAX_SPAWN_DISTANCE 10
# define BLIGHT_SPAWN_RETURNING_DEG_VARIATION 60

// animations

# define BLIGHT_DEATH_ANIMATION_FRAMES 30

// --- Minimap Settings

# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200
# define MINIMAP_LEFT_OFFSET 25
# define MINIMAP_TOP_OFFSET 25
# define MINIMAP_BORDER_WIDTH 5

// --- Gameplay Balancing

# define AMMO_AMOUNT_PER_ORB 3

#endif