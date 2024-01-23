/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:45:23 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/23 16:45:41 by dmaessen         ###   ########.fr       */
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

	moveSpeed = 0.55; // check on these values - or 0.8
	if (data->input->parsed_map[(int)(data->m->pos_x + data->m->dir_x * moveSpeed)][(int)data->m->pos_y] == '0')
		data->m->pos_x += data->m->dir_x * moveSpeed;
	if (data->input->parsed_map[(int)data->m->pos_x][(int)(data->m->pos_y + data->m->dir_y * moveSpeed)] == '0')
		data->m->pos_y += data->m->dir_y * moveSpeed; 
}

void move_down(t_data *data)
{
	double moveSpeed;

	moveSpeed = 0.55;
	if (data->input->parsed_map[(int)(data->m->pos_x - data->m->dir_x * moveSpeed)][(int)data->m->pos_y] == '0')
		data->m->pos_x -= data->m->dir_x * moveSpeed;
	if (data->input->parsed_map[(int)data->m->pos_x][(int)(data->m->pos_y - data->m->dir_y * moveSpeed)] == '0')
		data->m->pos_y -= data->m->dir_y * moveSpeed;
}

// These have to be made the same way as the up and down keys, 
// but use plane_x and plane_y instead of dir_x and dir_y.
void move_left(t_data *data)
{
	double moveSpeed;

	moveSpeed = 0.55;
	if (data->input->parsed_map[(int)(data->m->pos_x + data->m->plane_x * moveSpeed)][(int)data->m->pos_y] == '0')
		data->m->pos_x += data->m->plane_x * moveSpeed;
	if (data->input->parsed_map[(int)data->m->pos_x][(int)(data->m->pos_y + data->m->plane_y * moveSpeed)] == '0')
		data->m->pos_y += data->m->plane_y * moveSpeed;
}

void move_right(t_data *data)
{
	double moveSpeed;

	moveSpeed = 0.55;
	if (data->input->parsed_map[(int)(data->m->pos_x - data->m->plane_x * moveSpeed)][(int)data->m->pos_y] == '0')
		data->m->pos_x -= data->m->plane_x * moveSpeed;
	if (data->input->parsed_map[(int)data->m->pos_x][(int)(data->m->pos_y - data->m->plane_y * moveSpeed)] == '0')
		data->m->pos_y -= data->m->plane_y * moveSpeed;
}

void look_left(t_data *data) // camera direction and camera plane must be rotated
{
	double rotSpeed;
	double olddir_x;
	double oldplane_x;

	rotSpeed = 0.1; // check on these values -- or 0.3
	olddir_x = data->m->dir_x;
	data->m->dir_x = data->m->dir_x * cos(rotSpeed) - data->m->dir_y * sin(rotSpeed);
	data->m->dir_y = olddir_x * sin(rotSpeed) + data->m->dir_y * cos(rotSpeed);
	oldplane_x = data->m->plane_x;
	data->m->plane_x = data->m->plane_x * cos(rotSpeed) - data->m->plane_y * sin(rotSpeed);
	data->m->plane_y = oldplane_x * sin(rotSpeed) + data->m->plane_y * cos(rotSpeed);
}

void look_right(t_data *data)
{
	double rotSpeed;
	double olddir_x;
	double oldplane_x;

	rotSpeed = 0.1;
	olddir_x = data->m->dir_x;
	oldplane_x = data->m->plane_x;
	data->m->dir_x = data->m->dir_x * cos(-rotSpeed) - data->m->dir_y * sin(-rotSpeed);
	data->m->dir_y = olddir_x * sin(-rotSpeed) + data->m->dir_y * cos(-rotSpeed);
	data->m->plane_x = data->m->plane_x * cos(-rotSpeed) - data->m->plane_y * sin(-rotSpeed);
	data->m->plane_y = oldplane_x * sin(-rotSpeed) + data->m->plane_y * cos (-rotSpeed);
}

void move(void *param)
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
