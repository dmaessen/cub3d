/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:15:24 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/14 17:05:41 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	start(void *param)
{
	t_data	*data;

	data = param;
	data->m->x = 0;
	ft_bzero(data->img->pixels, data->img->width * data->img->height * 4);
	while (data->m->x < WIDTH)
	{
		ray_pos(data, data->m->x);
		inital_sidedist(data);
		dda(data);
		calc_drawing(data);
		drawing(data);
		data->m->x++;
	}
}

/*  to calculate the ray position and direction
    to know in which square of the map the ray is in */
void	ray_pos(t_data *data, int x)
{
	data->m->camera_x = 2 * x / (double)WIDTH - 1;
	data->m->ray_dir_x = data->m->dir_x + data->m->plane_x * data->m->camera_x;
	data->m->ray_dir_y = data->m->dir_y + data->m->plane_y * data->m->camera_x;
	data->m->map_x = (int)data->m->pos_x;
	data->m->map_y = (int)data->m->pos_y;
	if (data->m->ray_dir_x == 0)
		data->m->delta_dist_x = 1e30;
	else
		data->m->delta_dist_x = fabs(1 / data->m->ray_dir_x);
	if (data->m->ray_dir_y == 0)
		data->m->delta_dist_y = 1e30;
	else
		data->m->delta_dist_y = fabs(1 / data->m->ray_dir_y);
}

/* calculate step and initial sideDist */
void	inital_sidedist(t_data *data)
{
	if (data->m->ray_dir_x < 0)
	{
		data->m->step_x = -1;
		data->m->side_dist_x = \
		(data->m->pos_x - data->m->map_x) * data->m->delta_dist_x;
	}
	else
	{
		data->m->step_x = 1;
		data->m->side_dist_x = \
		(data->m->map_x + 1.0 - data->m->pos_x) * data->m->delta_dist_x;
	}
	if (data->m->ray_dir_y < 0)
	{
		data->m->step_y = -1;
		data->m->side_dist_y = \
		(data->m->pos_y - data->m->map_y) * data->m->delta_dist_y;
	}
	else
	{
		data->m->step_y = 1;
		data->m->side_dist_y = \
		(data->m->map_y + 1.0 - data->m->pos_y) * data->m->delta_dist_y;
	}
}

/* 
    check if a wall was hit, 
	and go on until a wall has been hit (if == 1, was was hit)
    going to the next square, either in the x-direction or y-direction
*/
void	dda(t_data *data)
{
	data->m->hitwall = 0;
	while (!data->m->hitwall)
	{
		if (data->m->side_dist_x < data->m->side_dist_y)
		{
			data->m->side_dist_x += data->m->delta_dist_x;
			data->m->map_x += data->m->step_x;
			data->m->side = 0;
		}
		else
		{
			data->m->side_dist_y += data->m->delta_dist_y;
			data->m->map_y += data->m->step_y;
			data->m->side = 1;
		}
		if (data->input->parsed_map[data->m->map_x][data->m->map_y] == '1')
			data->m->hitwall = 1;
	}
}
