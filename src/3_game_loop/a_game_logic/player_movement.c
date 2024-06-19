#include "../../../include/cub3d.h"

void	handle_player_move(void)
{
	double	speed;
	double	angle;

	speed = MOVEMENT_SPEED;
	angle = deg_to_rad(dir_vec_to_deg(player()->transform.rot));
	if (mlx_is_key_down(game()->mlx, MLX_KEY_LEFT_SHIFT))
		speed *= MOVEMENT_SPRINT_MULTIPLIER;
	if (mlx_is_key_down(game()->mlx, MLX_KEY_W))
	{
		write(1, "W\n", 2);
		player()->transform.pos.x = cos(angle) * MOVEMENT_SPEED;
		player()->transform.pos.y = sin(angle) * MOVEMENT_SPEED;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_A))
	{
		write(1, "A\n", 2);
		player()->transform.pos.x = sin(angle) * MOVEMENT_SPEED;
		player()->transform.pos.y = -cos(angle) * MOVEMENT_SPEED;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_S))
	{
		write(1, "S\n", 2);
		player()->transform.pos.x = -cos(angle) * MOVEMENT_SPEED;
		player()->transform.pos.y = -sin(angle) * MOVEMENT_SPEED;
	}
	if (mlx_is_key_down(game()->mlx, MLX_KEY_D))
	{
		write(1, "D\n", 2);
		player()->transform.pos.x = -sin(angle) * MOVEMENT_SPEED;
		player()->transform.pos.y = cos(angle) * MOVEMENT_SPEED;
	}
}
