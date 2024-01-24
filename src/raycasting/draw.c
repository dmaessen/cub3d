/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:09:00 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/24 13:13:05 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void calc_drawing(t_data *data)
{
    // calculate the distance of perpendicular ray
    if (data->m->side == 0)
        data->m->wall_dist = (data->m->side_dist_x - data->m->delta_dist_x);
    else
        data->m->wall_dist = (data->m->side_dist_y - data->m->delta_dist_y);

    data->m->line_height = (int)(HEIGHT / data->m->wall_dist); // calc height of line to draw on screen

    // printf("linehieght = %d || perpwalldist = %f || sideDistX = %f || sideDistY = %f\n", data->m->lineHeight, data->m->perpWallDist, data->m->sideDistX, data->m->sideDistY); // to rm
    data->m->draw_start = ((data->m->line_height * -1) / 2) + (HEIGHT / 2);
    if (data->m->draw_start < 0)
        data->m->draw_start = 0;
    data->m->draw_end = (int)((data->m->line_height / 2) + (HEIGHT / 2));
    // printf("drawEnd: %d\n", data->m->drawEnd);
    if (data->m->draw_end >= HEIGHT)
        data->m->draw_end = HEIGHT - 1;

    if (data->m->side == 0)
        data->m->wall_x = data->m->pos_y + data->m->wall_dist * data->m->ray_dir_y; 
    else
        data->m->wall_x = data->m->pos_x + data->m->wall_dist * data->m->ray_dir_x; 
    data->m->wall_x -= floor((data->m->wall_x)); // floor rounds down a floating point number 
}

void drawing(t_data *data)
{
    int y;

    data->m->texture_x = (int)(data->m->wall_x * (double)TEXWIDTH); // x coordinate on the texture and mirror the location if necessary
    if (data->m->side == 0 && data->m->ray_dir_x > 0)
        data->m->texture_x = TEXWIDTH - data->m->texture_x - 1;
    if (data->m->side == 1 && data->m->ray_dir_y < 0)
        data->m->texture_x = TEXWIDTH - data->m->texture_x - 1;

    data->m->step = 1.0 * TEXHEIGHT / data->m->line_height; // how much to increase the texture coordinate per screen pixel
    data->m->texture_pos = (data->m->draw_start - HEIGHT / 2 + data->m->line_height / 2) * data->m->step; // start texture coordinate
    y = data->m->draw_start;
    // printf("drawStart: %d\n", data->m->drawStart);
    while (y < data->m->draw_end)
    {
        data->m->texture_y = (int)data->m->texture_pos & (TEXWIDTH - 1); // cast text coordinate to int, and mask with the last in case of overflow
        data->m->texture_pos += data->m->step;
        data->m->color = get_pixel(which_wall(data), data->m->texture_x, data->m->texture_y);
        mlx_put_pixel(data->img, data->m->x, y, data->m->color); // each time before drawing clear the img with bzero
        y++;
    }
}

void clear_img(t_data *data) // needed??
{
    ft_memset(data->img->pixels, 255, data->img->width * data->img->height * sizeof(int32_t));
}

mlx_texture_t *which_wall(t_data *data)
{
    if (data->m->dir_x <= 0 && data->m->dir_y >= 0 && data->m->side == 1)
        return (data->wall[0].tex); // NO
    else if (data->m->dir_x >= 0 && data->m->dir_y <= 0 && data->m->side == 1)
        return (data->wall[1].tex); // SO
    else if (data->m->dir_x <= 0 && data->m->dir_y <= 0 && data->m->side == 1)
        return (data->wall[1].tex); // SO
    else if (data->m->dir_x >= 0 && data->m->dir_y <= 0 && data->m->side == 0)
        return (data->wall[2].tex); // WE
    else if (data->m->dir_x >= 0 && data->m->dir_y >= 0 && data->m->side == 0)
        return (data->wall[2].tex); // WE
    else if (data->m->dir_x <= 0 && data->m->dir_y >= 0 && data->m->side == 0)
        return (data->wall[3].tex); // EA
    else if (data->m->dir_x <= 0 && data->m->dir_y <= 0 && data->m->side == 0)
        return (data->wall[3].tex); // EA
    else
        return (data->wall[0].tex); // NO
}



unsigned int get_pixel(mlx_texture_t *t, uint32_t x, uint32_t y)
{
    int r;
    int g;
    int b;

    r = t->pixels[(y * t->width + x) * t->bytes_per_pixel];
	g = t->pixels[(y * t->width + x) * t->bytes_per_pixel + 1];
	b = t->pixels[(y * t->width + x) * t->bytes_per_pixel + 2];
    return ((unsigned int)(r << 24 | g << 16 | b << 8 | 255));
}
