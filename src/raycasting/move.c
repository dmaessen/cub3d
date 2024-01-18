/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:45:23 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/18 15:33:39 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void move_up(t_data *data) // checking if walls
{
	double moveSpeed;

	moveSpeed = 0.51; // check on these values - or 0.8
	if (data->input->parsed_map[(int)(data->m->posX + data->m->dirX * moveSpeed)][(int)data->m->posY] == '0')
		data->m->posX += data->m->dirX * moveSpeed;
	if (data->input->parsed_map[(int)data->m->posX][(int)(data->m->posY + data->m->dirY * moveSpeed)] == '0')
		data->m->posY += data->m->dirY * moveSpeed; 
}

void move_down(t_data *data) // check if walls around
{
	double moveSpeed;

	moveSpeed = 0.8; // check on these values
	if (data->input->parsed_map[(int)(data->m->posX - data->m->dirX * moveSpeed)][(int)data->m->posY] == '0')
		data->m->posX -= data->m->dirX * moveSpeed;
	if (data->input->parsed_map[(int)data->m->posX][(int)(data->m->posY - data->m->dirY * moveSpeed)] == '0')
		data->m->posY -= data->m->dirY * moveSpeed;
}

// These have to be made the same way as the up and down keys, 
// but use planeX and planeY instead of dirX and dirY.
void move_left(t_data *data)
{
	double moveSpeed;

	moveSpeed = 0.51; // check on these values
	if (data->input->parsed_map[(int)(data->m->posX + data->m->planeX * moveSpeed)][(int)data->m->posY] == '0')
		data->m->posX += data->m->planeX * moveSpeed;
	if (data->input->parsed_map[(int)data->m->posX][(int)(data->m->posY + data->m->planeY * moveSpeed)] == '0')
		data->m->posY += data->m->planeY * moveSpeed;
}

void move_right(t_data *data)
{
	double moveSpeed;

	moveSpeed = 0.51;
	if (data->input->parsed_map[(int)(data->m->posX - data->m->planeX * moveSpeed)][(int)data->m->posY] == '0')
		data->m->posX -= data->m->planeX * moveSpeed;
	if (data->input->parsed_map[(int)data->m->posX][(int)(data->m->posY - data->m->planeY * moveSpeed)] == '0')
		data->m->posY -= data->m->planeY * moveSpeed;
}

void look_left(t_data *data) // camera direction and camera plane must be rotated
{
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;

	rotSpeed = 0.1; // check on these values -- or 0.3
	oldDirX = data->m->dirX;
	data->m->dirX = data->m->dirX * cos(rotSpeed) - data->m->dirY * sin(rotSpeed);
	data->m->dirY = oldDirX * sin(rotSpeed) + data->m->dirY * cos(rotSpeed);
	oldPlaneX = data->m->planeX;
	data->m->planeX = data->m->planeX * cos(rotSpeed) - data->m->planeY * sin(rotSpeed);
	data->m->planeY = oldPlaneX * sin(rotSpeed) + data->m->planeY * cos(rotSpeed);
}

void look_right(t_data *data)
{
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;

	rotSpeed = 0.1; // check on these values
	oldDirX = data->m->dirX;
	oldPlaneX = data->m->planeX;
	data->m->dirX = data->m->dirX * cos(-rotSpeed) - data->m->dirY * sin(-rotSpeed);
	data->m->dirY = oldDirX * sin(-rotSpeed) + data->m->dirY * cos(-rotSpeed);
	data->m->planeX = data->m->planeX * cos(-rotSpeed) - data->m->planeY * sin(-rotSpeed);
	data->m->planeY = oldPlaneX * sin(-rotSpeed) + data->m->planeY * cos (-rotSpeed);
}

void move(void *param) // maybe these moves need to be made via img->instances[0].x += 5; and same for y
{
	t_data *data;

	data = (t_data *)param;
    //if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_up((t_data *)param);
	// else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS) // move down
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_down((t_data *)param);
	// else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS) // move left
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left((t_data *)param);
	// else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS) // move right
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right((t_data *)param);
    // else if ((keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)) // arrow left
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        look_left((t_data *)param);
    // else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // arrow right
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        look_right((t_data *)param);
	// else if ((keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS))
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
}
