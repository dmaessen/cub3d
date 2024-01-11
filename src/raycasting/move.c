/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:45:23 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/11 15:43:03 by dmaessen         ###   ########.fr       */
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

	moveSpeed = 65 * 5.0; // check on these values
	if (data->input->parsed_map[(int)(data->m->posX + data->m->dirX * moveSpeed)][(int)data->m->posY] == false)
		data->m->posX += data->m->dirX * moveSpeed;
	if (data->input->parsed_map[(int)data->m->posX][(int)(data->m->posY + data->m->dirY * moveSpeed)] == false)
		data->m->posY += data->m->dirY * moveSpeed; 
}

void move_down(t_data *data) // check if walls around
{
	double moveSpeed;

	moveSpeed = 65 * 5.0; // check on these values
	if (data->input->parsed_map[(int)(data->m->posX - data->m->dirX * moveSpeed)][(int)data->m->posY] == false)
		data->m->posX -= data->m->dirX * moveSpeed;
	if (data->input->parsed_map[(int)data->m->posX][(int)(data->m->posY - data->m->dirY * moveSpeed)] == false)
		data->m->posY -= data->m->dirY * moveSpeed;
}

// These have to be made the same way as the up and down keys, 
// but use planeX and planeY instead of dirX and dirY.
void move_left(t_data *data)
{
	double moveSpeed;

	moveSpeed = 65 * 5.0; // check on these values
	if (data->input->parsed_map[(int)(data->m->posX + data->m->planeX * moveSpeed)][(int)data->m->posY] == false)
		data->m->posX += data->m->planeX * moveSpeed;
	if (data->input->parsed_map[(int)data->m->posX][(int)(data->m->posY + data->m->planeY * moveSpeed)] == false)
		data->m->posY += data->m->planeY * moveSpeed;
}

void move_right(t_data *data)
{
	double moveSpeed;

	moveSpeed = 65 * 5.0;
	if (data->input->parsed_map[(int)(data->m->posX - data->m->planeX * moveSpeed)][(int)data->m->posY] == false)
		data->m->posX -= data->m->planeX * moveSpeed;
	if (data->input->parsed_map[(int)data->m->posX][(int)(data->m->posY - data->m->planeY * moveSpeed)] == false)
		data->m->posY -= data->m->planeY * moveSpeed;
}

void look_left(t_data *data) // camera direction and camera plane must be rotated
{
	double rotSpeed;
	double oldDirX;
	double oldPlaneX;

	rotSpeed = 65 * 3.0; // check on these values
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

	rotSpeed = 65 * 3.0; // check on these values
	oldDirX = data->m->dirX;
	oldPlaneX = data->m->planeX;
	data->m->dirX = data->m->dirX * cos(-rotSpeed) - data->m->dirY * sin(-rotSpeed);
	data->m->dirY = oldDirX * sin(-rotSpeed) + data->m->dirY * cos(-rotSpeed);
	data->m->planeX = data->m->planeX * cos(-rotSpeed) - data->m->planeY * sin(-rotSpeed);
	data->m->planeY = oldPlaneX * sin(-rotSpeed) + data->m->planeY * cos (-rotSpeed);
}

void move(mlx_key_data_t keydata, void *param) // maybe these moves need to be made via img->instances[0].x += 5; and same for y
{
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS) // move up
		move_up((t_data *)param);
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS) // move down
		move_down((t_data *)param);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS) // move left
		move_left((t_data *)param);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS) // move right
		move_right((t_data *)param);
    else if ((keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)) // arrow left
        look_left((t_data *)param);
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // arrow right
        look_right((t_data *)param);
	else if ((keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS))
		exit(EXIT_SUCCESS);
}
