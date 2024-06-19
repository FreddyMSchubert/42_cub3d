#include "../../../include/cub3d.h"

double	get_mvmnt_speed(void)
{
	double	speed;

	speed = MOVEMENT_SPEED;
	if (mlx_is_key_down(game()->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= MOVEMENT_SPRINT_MULTIPLIER;
	return (speed);
}

t_vec2	get_movement_from_key(void)
{
	double	speed;
	double	angle;
	t_vec2	mvmnt;

	speed = get_mvmnt_speed();
	angle = deg_to_rad(dir_vec_to_deg(player()->transform.rot));
	if (mlx_is_key_down(game()->mlx, MLX_KEY_W))
	{
		mvmnt.x = cos(angle) * speed;
		mvmnt.y = sin(angle) * speed;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_A))
	{
		mvmnt.x = sin(angle) * speed;
		mvmnt.y = -cos(angle) * speed;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_S))
	{
		mvmnt.x = -cos(angle) * speed;
		mvmnt.y = -sin(angle) * speed;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_D))
	{
		mvmnt.x = -sin(angle) * speed;
		mvmnt.y = cos(angle) * speed;
	}
	return (mvmnt);
}

void	handle_player_move(void)
{
	t_vec2	original_pos;
	t_vec2	movement;

	original_pos = player()->transform.pos;
	movement = get_movement_from_key();
	player()->transform.pos.x += movement.x;
	if (*game()->input_data->map[(int)player()->transform.pos.y][(int)player()->transform.pos.x] != FLOOR)
		player()->transform.pos.x = original_pos.x;
	player()->transform.pos.y += movement.y;
	if (*game()->input_data->map[(int)player()->transform.pos.y][(int)player()->transform.pos.x] != FLOOR)
		player()->transform.pos.y = original_pos.y;
}
