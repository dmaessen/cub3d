/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 14:51:57 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/15 13:47:17 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	move_up(t_data *data)
{
	double	move_speed;

	move_speed = 0.8;
	if (data->input->parsed_map[(int)(data->m->pos_x \
	+ data->m->dir_x * move_speed)][(int)data->m->pos_y] != '1')
		data->m->pos_x += data->m->dir_x * move_speed;
	if (data->input->parsed_map[(int)data->m->pos_x][(int)(data->m->pos_y \
	+ data->m->dir_y * move_speed)] != '1')
		data->m->pos_y += data->m->dir_y * move_speed;
}

void	move_down(t_data *data)
{
	double	move_speed;

	move_speed = 0.8;
	if (data->input->parsed_map[(int)(data->m->pos_x \
	- data->m->dir_x * move_speed)][(int)data->m->pos_y] != '1')
		data->m->pos_x -= data->m->dir_x * move_speed;
	if (data->input->parsed_map[(int)data->m->pos_x][(int)(data->m->pos_y \
	- data->m->dir_y * move_speed)] != '1')
		data->m->pos_y -= data->m->dir_y * move_speed;
}

void	move_left(t_data *data)
{
	double	move_speed;

	move_speed = 0.8;
	if (data->input->parsed_map[(int)(data->m->pos_x \
	- data->m->plane_x * move_speed)][(int)data->m->pos_y] != '1')
		data->m->pos_x -= data->m->plane_x * move_speed;
	if (data->input->parsed_map[(int)data->m->pos_x][(int)(data->m->pos_y \
	- data->m->plane_y * move_speed)] != '1')
		data->m->pos_y -= data->m->plane_y * move_speed;
}

void	move_right(t_data *data)
{
	double	move_speed;

	move_speed = 0.8;
	if (data->input->parsed_map[(int)(data->m->pos_x \
	+ data->m->plane_x * move_speed)][(int)data->m->pos_y] != '1')
		data->m->pos_x += data->m->plane_x * move_speed;
	if (data->input->parsed_map[(int)data->m->pos_x][(int)(data->m->pos_y \
	+ data->m->plane_y * move_speed)] != '1')
		data->m->pos_y += data->m->plane_y * move_speed;
}
