/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 13:45:23 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/14 17:06:59 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	look_left(t_data *data)
{
	double	rotation;
	double	old_dir_x;
	double	old_plane_x;

	rotation = 0.1;
	old_dir_x = data->m->dir_x;
	data->m->dir_x = data->m->dir_x * cos(rotation) \
	- data->m->dir_y * sin(rotation);
	data->m->dir_y = old_dir_x * sin(rotation) \
	+ data->m->dir_y * cos(rotation);
	old_plane_x = data->m->plane_x;
	data->m->plane_x = data->m->plane_x * cos(rotation) \
	- data->m->plane_y * sin(rotation);
	data->m->plane_y = old_plane_x * sin(rotation) \
	+ data->m->plane_y * cos(rotation);
}

void	look_right(t_data *data)
{
	double	rotation;
	double	old_dir_x;
	double	old_plane_x;

	rotation = 0.1;
	old_dir_x = data->m->dir_x;
	old_plane_x = data->m->plane_x;
	data->m->dir_x = data->m->dir_x * cos(-rotation) \
	- data->m->dir_y * sin(-rotation);
	data->m->dir_y = old_dir_x * sin(-rotation) \
	+ data->m->dir_y * cos(-rotation);
	data->m->plane_x = data->m->plane_x * cos(-rotation) \
	- data->m->plane_y * sin(-rotation);
	data->m->plane_y = old_plane_x * sin(-rotation) \
	+ data->m->plane_y * cos (-rotation);
}

void	move(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		move_up((t_data *)param);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		move_down((t_data *)param);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		move_left((t_data *)param);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		move_right((t_data *)param);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		look_left((t_data *)param);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		look_right((t_data *)param);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(EXIT_SUCCESS);
}
