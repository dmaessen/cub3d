/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:53:16 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/15 19:08:27 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void	init_datamap(t_data *data)
{
	data->m->camera_x = 0.0;
	data->m->ray_dir_x = 0.0;
	data->m->ray_dir_y = 0.0;
	data->m->map_x = 0;
	data->m->map_y = 0;
	data->m->side_dist_x = 0.0;
	data->m->side_dist_y = 0.0;
	data->m->delta_dist_x = 0.0;
	data->m->delta_dist_y = 0.0;
	data->m->wall_dist = 0.0;
	data->m->step_x = 0;
	data->m->step_y = 0;
	data->m->hitwall = 0;
	data->m->side = 0;
	data->m->line_height = 0;
	data->m->draw_start = 0;
	data->m->draw_end = 0;
	data->m->wall_x = 0.0;
	data->m->texture_x = 0;
	data->m->texture_y = 0;
	data->m->step = 0;
	data->m->texture_pos = 0.0;
}

static void	load_textures(t_data *data)
{
	data->wall = malloc(4 * sizeof(t_wall));
	if (!data->wall)
		return (err_msg("malloc failed"));
	data->wall[0].tex = NULL;
	data->wall[1].tex = NULL;
	data->wall[2].tex = NULL;
	data->wall[3].tex = NULL;
	data->wall[0].tex = mlx_load_png(data->textures->no_texture);
	if (!data->wall[0].tex)
		return (err_msg("loading textures\n"));
	data->wall[1].tex = mlx_load_png(data->textures->so_texture);
	if (!data->wall[1].tex)
		return (err_msg("loading textures\n"));
	data->wall[2].tex = mlx_load_png(data->textures->we_texture);
	if (!data->wall[2].tex)
		return (err_msg("loading textures\n"));
	data->wall[3].tex = mlx_load_png(data->textures->ea_texture);
	if (!data->wall[3].tex)
		return (err_msg("loading textures\n"));
}

/* 66degre angle for the Field of Vision, to correct fish-eye */
void	init_map(t_data *data, mlx_t *mlx)
{
	data->m = calloc_exit(1, sizeof(t_map));
	pos_player(data);
	dir_player(data);
	data->m->dir_len = sqrt(data->m->dir_x * data->m->dir_x \
	+ data->m->dir_y * data->m->dir_y);
	data->m->angle_fov = 0.66;
	data->m->plane_x = data->m->dir_y / data->m->dir_len * data->m->angle_fov;
	data->m->plane_y = -data->m->dir_x / data->m->dir_len * data->m->angle_fov;
	load_textures(data);
	data->img = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!data->img)
		return (err_msg("mlx_new_image failed"));
	init_datamap(data);
}

void	pos_player(t_data *data)
{
	int	i;
	int	col;

	i = 0;
	while (data->input->parsed_map[i])
	{
		col = 0;
		while (data->input->parsed_map[i][col])
		{
			if (data->input->parsed_map[i][col] == 'N'
			|| data->input->parsed_map[i][col] == 'S'
			|| data->input->parsed_map[i][col] == 'E'
			|| data->input->parsed_map[i][col] == 'W')
			{
				data->m->pos_y = (double)col + 0.5;
				data->m->pos_x = (double)i + 0.5;
				break ;
			}
			col++;
		}
		if (data->m->pos_x != 0)
			break ;
		i++;
	}
}

void	dir_player(t_data *data)
{
	if (data->input->player_facing == P_NORTH)
	{
		data->m->dir_x = -1;
		data->m->dir_y = 0;
	}
	if (data->input->player_facing == P_SOUTH)
	{
		data->m->dir_x = 1;
		data->m->dir_y = 0;
	}
	if (data->input->player_facing == P_EAST)
	{
		data->m->dir_x = -1;
		data->m->dir_y = 1;
	}
	if (data->input->player_facing == P_WEST)
	{
		data->m->dir_x = 0;
		data->m->dir_y = 1;
	}
}
