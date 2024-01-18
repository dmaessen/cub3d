/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:09:00 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/18 15:20:31 by dmaessen         ###   ########.fr       */
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
        data->m->perpWallDist = (data->m->sideDistX - data->m->deltaDistX);
    else
        data->m->perpWallDist = (data->m->sideDistY - data->m->deltaDistY);

    data->m->lineHeight = (int)(HEIGHT / data->m->perpWallDist); // calc height of line to draw on screen
            
    // printf("linehieght = %d || perpwalldist = %f || sideDistX = %f || sideDistY = %f\n", data->m->lineHeight, data->m->perpWallDist, data->m->sideDistX, data->m->sideDistY); // to rm
    data->m->drawStart = ((data->m->lineHeight * -1) / 2) + (HEIGHT / 2);
    if (data->m->drawStart < 0)
        data->m->drawStart = 0;
    data->m->drawEnd = (int)((data->m->lineHeight / 2) + (HEIGHT / 2));
    // printf("drawEnd: %d\n", data->m->drawEnd);
    if (data->m->drawEnd >= HEIGHT)
        data->m->drawEnd = HEIGHT - 1;
        
    if (data->m->side == 0)
        data->m->wallX = data->m->posY + data->m->perpWallDist * data->m->rayDirY; 
    else
        data->m->wallX = data->m->posX + data->m->perpWallDist * data->m->rayDirX; 
    data->m->wallX -= floor((data->m->wallX)); // floor rounds down a floating point number 
}

void drawing(t_data *data)
{
    int y;
    
    data->m->textureX = (int)(data->m->wallX * (double)TEXWIDTH); // x coordinate on the texture and mirror the location if necessary
    if (data->m->side == 0 && data->m->rayDirX > 0)
        data->m->textureX = TEXWIDTH - data->m->textureX - 1;
    if (data->m->side == 1 && data->m->rayDirY < 0)
        data->m->textureX = TEXWIDTH - data->m->textureX - 1;

    data->m->step = 1.0 * TEXHEIGHT / data->m->lineHeight; // how much to increase the texture coordinate per screen pixel
    data->m->texturePos = (data->m->drawStart - HEIGHT / 2 + data->m->lineHeight / 2) * data->m->step; // start texture coordinate
    y = data->m->drawStart;
    // printf("drawStart: %d\n", data->m->drawStart);
    while (y < data->m->drawEnd)
    {
        data->m->textureY = (int)data->m->texturePos & (TEXWIDTH - 1); // cast text coordinate to int, and mask with the last in case of overflow
        data->m->texturePos += data->m->step;
        data->m->color = get_pixel(which_wall(data), data->m->textureX, data->m->textureY);
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
    if (data->m->dirX <= 0 && data->m->dirY >= 0 && data->m->side == 1)
        return (data->wall[0].tex); // NO
    else if (data->m->dirX >= 0 && data->m->dirY <= 0 && data->m->side == 1)
        return (data->wall[1].tex); // SO
    else if (data->m->dirX <= 0 && data->m->dirY <= 0 && data->m->side == 1)
        return (data->wall[1].tex); // SO
    else if (data->m->dirX >= 0 && data->m->dirY <= 0 && data->m->side == 0)
        return (data->wall[2].tex); // WE
    else if (data->m->dirX >= 0 && data->m->dirY >= 0 && data->m->side == 0)
        return (data->wall[2].tex); // WE
    else if (data->m->dirX <= 0 && data->m->dirY >= 0 && data->m->side == 0)
        return (data->wall[3].tex); // EA
    else if (data->m->dirX <= 0 && data->m->dirY <= 0 && data->m->side == 0)
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