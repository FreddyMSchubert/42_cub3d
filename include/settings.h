/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fschuber <fschuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 08:45:22 by freddy            #+#    #+#             */
/*   Updated: 2024/07/02 11:57:57 by fschuber         ###   ########.fr       */
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

// --- Debug

# define RENDER_ENTITIES_THROUGH_WALLS false
# define INFINITE_HEALTH false

// --- Quality of Life

# define MOUSE_SENSITIVITY 0.45

// Map Making

# define MIN_MAP_SIZE 8
# define MAX_MAP_SIZE 20
# define MIN_ROOMS_AMOUNT 2
# define MAX_ROOMS_AMOUNT 5
# define MIN_ROOM_SIZE 1
# define MAX_ROOM_SIZE 13
# define MAX_ROOM_SIZE_TO_MAP_SIZE 3
# define WALL_REMOVAL_CHANCE_PERCENT 5

# define ENTITIY_PLACEMENT_CHANCE 10
# define ORB_PLACEMENT_CHANCE 100
# define BLIGHT_PLACEMENT_CHANCE 85
# define HEALTH_DROP_CHANCE_PERCENT 10

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
# define FPS 60

// --- Entities

// collisions

# define GOAL_COLLISION_DISTANCE 0.5
# define HEALTH_COLLISION_DISTANCE 0.5
# define KEY_COLLISION_DISTANCE 0.5
# define CLOSED_DOOR_ALLOWED_WALK_DISTANCE 0.4
# define DOOR_OPEN_DISTANCE 1.0
# define DEFAULT_COLLISION_DISTANCE 0.5

// speed

# define DOOR_OPEN_SPEED 0.05
# define PROJECTILE_SPEED 0.25
# define BLIGHT_SPEED 0.05

// movement

# define BLIGHT_WALKING_START_CHANCE 0.1
# define BLIGHT_STANDING_START_CHANCE 0.025
# define BLIGHT_ATTACKING_START_CHANCE 0.5
# define BLIGHT_MOVEMENT_ROTATION_SWITCH_CHANCE 0.05
# define BLIGHT_MINIUM_ROTATION_DEG 45
# define BLIGHT_MAX_SPAWN_DISTANCE 10
# define BLIGHT_SPAWN_RETURNING_DEG_VARIATION 45
# define BLIGHT_SHOOTING_INACCURACY_DEG 30

// health

# define ENEMY_STARTING_HEALTH 3
# define PLAYER_STARTING_HEALTH 10
# define MINOR_PROJECTILE_HIT_DECREASE 1
# define MAJOR_PROJECTILE_HIT_DESCREASE 3
# define HEALTH_PICKUP_AMOUNT 1

// animations

# define BLIGHT_DEATH_ANIMATION_FRAMES 45
# define BLIGHT_ATTACK_ANIMATION_FRAMES 30

// --- Minimap Settings

# define MINIMAP_WIDTH 200
# define MINIMAP_HEIGHT 200
# define MINIMAP_LEFT_OFFSET 25
# define MINIMAP_TOP_OFFSET 25
# define MINIMAP_BORDER_WIDTH 5

// --- Gameplay Balancing

# define MIN_AMMO_AMOUNT_PER_ORB 2
# define MAX_AMMO_AMOUNT_PER_ORB 5

#endif