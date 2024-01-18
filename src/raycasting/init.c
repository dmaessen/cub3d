/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 13:53:16 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/18 14:07:54 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void init_datamap(t_data *data)
{
    data->m->cameraX = 0.0;
    data->m->rayDirX = 0.0;
    data->m->rayDirY = 0.0;
    data->m->mapX = 0;
    data->m->mapY = 0;
    data->m->sideDistX = 0.0;
    data->m->sideDistY = 0.0;
    data->m->deltaDistX = 0.0;
    data->m->deltaDistY = 0.0;
    data->m->perpWallDist = 0.0;
    data->m->stepX = 0;
    data->m->stepY = 0;
    data->m->hitwall = 0;
    data->m->side = 0;
    data->m->lineHeight = 0;
    data->m->drawStart = 0;
    data->m->drawEnd = 0;
    data->m->wallX = 0.0;
    data->m->textureX = 0;
    data->m->textureY = 0;
    data->m->step = 0;
    data->m->texturePos = 0.0;
}

void init_map(t_data *data, mlx_t *mlx)
{
    data->m = calloc_exit(1, sizeof(t_map)); // needed -- also free later then
    pos_player(data); // fills in posY and posX
    dir_player(data);
    data->m->angleFOV = 0.66; // which results in a 66degre angle for the Field of Vision
    data->m->dirLen = sqrt(data->m->dirX * data->m->dirX + data->m->dirY * data->m->dirY);
    data->m->planeX = data->m->dirY / data->m->dirLen * data->m->angleFOV;
    data->m->planeY = -data->m->dirX / data->m->dirLen * data->m->angleFOV; 
    data->wall = malloc(4 * sizeof(t_wall));
    if (!data->wall)
        return err_msg("malloc failed");
    data->wall[0].tex = NULL;
	data->wall[1].tex = NULL;
	data->wall[2].tex = NULL;
	data->wall[3].tex = NULL;
	data->wall[0].tex = mlx_load_png(data->textures->no_texture);
	data->wall[1].tex = mlx_load_png(data->textures->so_texture);
	data->wall[2].tex = mlx_load_png(data->textures->we_texture);
	data->wall[3].tex = mlx_load_png(data->textures->ea_texture);
	if (!data->wall[0].tex || !data->wall[1].tex || !data->wall[2].tex || !data->wall[3].tex)
		return (err_msg("loading textures\n"));
    data->img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!data->img)
        return (err_msg("mlx_new_image failed"));
    init_datamap(data);
}

void pos_player(t_data *data)
{
    int i;
    int col;

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
                data->m->posY = (double)col + 0.5; // check on it later
                data->m->posX = (double)i + 0.5;
                break;
            }
            col++;
        }
        if (data->m->posX != 0)
            break;
        i++;
    }
}

void dir_player(t_data *data)
{
    if (data->input->player_facing == P_NORTH)
    {
        data->m->dirX = 0;
        data->m->dirY = 1;
    }
    if (data->input->player_facing == P_SOUTH)
    {
        data->m->dirX = 0;
        data->m->dirY = -1;
    }
    if (data->input->player_facing == P_EAST)
    {
        data->m->dirX = -1;
        data->m->dirY = 0;
    }
    if (data->input->player_facing == P_WEST)
    {
        data->m->dirX = 1;
        data->m->dirY = 0;
    }
}