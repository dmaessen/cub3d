/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:15:24 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/24 13:56:31 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void start(void *param)
{
    t_data *data;

    data = param;
    //background_img(data);
    // floor here
    // ceiling here
    //background_img(data);
    data->m->x = 0;
    //clear_img(data); // maybe not needed after the floor/ceiling
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

void ray_pos(t_data *data, int x)
{
    data->m->camera_x = (2 * x) / ((double)WIDTH - 1); // to calculate the ray position and direction
    data->m->ray_dir_x = data->m->dir_x + data->m->plane_x * data->m->camera_x;
    data->m->ray_dir_y = data->m->dir_y + data->m->plane_y * data->m->camera_x;
    data->m->map_x = (int)data->m->pos_x; // to know in which square of the map the ray is in
    data->m->map_y = (int)data->m->pos_y;
    // printf("posX %f posY %f mapX %d mapY %d", data->m->posX, data->m->posY, data->m->mapX, data->m->mapY);
    // printf("rayDirX = %f || raydirY = %f\n", data->m->rayDirX, data->m->rayDirY); // to rm
    if (data->m->ray_dir_x == 0)
        data->m->delta_dist_x = 1e30;
    else
        data->m->delta_dist_x = fabs(1 / data->m->ray_dir_x);
    if (data->m->ray_dir_y == 0)
        data->m->delta_dist_y = 1e30;
    else
        data->m->delta_dist_y = fabs(1 / data->m->ray_dir_y);
    // data->m->deltaDistX = (data->m->rayDirX == 0) ? 1e30 : fabs(1 / data->m->rayDirX); // length of the ray from one x/y side to next x/y side
    // data->m->deltaDistY = (data->m->rayDirY == 0) ? 1e30 : fabs(1 / data->m->rayDirY);
    // printf()"deltaDistX = %f || deltaDistY = %f\n", data->m->deltaDistX, data->m->deltaDistY); // to rm
}

void inital_sidedist(t_data *data)
{
    if (data->m->ray_dir_x < 0) // calculate step and initial sideDist
    {
        data->m->step_x = -1;
        data->m->side_dist_x = (data->m->pos_x - data->m->map_x) * data->m->delta_dist_x;
    }
    else
    {
        data->m->step_x = 1;
        data->m->side_dist_x = (data->m->map_x + 1.0 - data->m->pos_x) * data->m->delta_dist_x;
    }
    if (data->m->ray_dir_y < 0)
    {
        data->m->step_y = -1;
        data->m->side_dist_y = (data->m->pos_y - data->m->map_y) * data->m->delta_dist_y;
    }
    else
    {
        data->m->step_y = 1;
        data->m->side_dist_y = (data->m->map_y + 1.0 - data->m->pos_y) * data->m->delta_dist_y;
    }
}

void dda(t_data *data)
{
    data->m->hitwall = 0; // is a wall was hit or not
    while (!data->m->hitwall) // DDA -- or while loop here
    {
        // go to the next square, either in x-direction or y
        if (data->m->side_dist_x < data->m->side_dist_y)
        {
            data->m->side_dist_x += data->m->delta_dist_x;
            data->m->map_x  += data->m->step_x;
            data->m->side = 0;
        }
        else
        {
            data->m->side_dist_y += data->m->delta_dist_y;
            data->m->map_y  += data->m->step_y;
            data->m->side = 1;
        }
        if (data->input->parsed_map[data->m->map_x][data->m->map_y] == '1') // to check if we have hit a wall
            data->m->hitwall = 1;
    }
}






// void start(void *param)
// {
//     t_data *data;

//     data = param;
//     // floor here
//     // ceiling here
//     int x;
//     int y;
//         x = 0;
//         while (x < WIDTH) // ou width de la map?? 
//         {
//             data->m->cameraX = (2 * x) / ((double)WIDTH - 1); // to calculate the ray position and direction
//             data->m->rayDirX = data->m->dirX + data->m->planeX * data->m->cameraX;
//             data->m->rayDirY = data->m->dirY + data->m->planeY * data->m->cameraX;
//             data->m->mapX = (int)data->m->posX; // to know in which square of the map the ray is in
//             data->m->mapY = (int)data->m->posY;
//             // printf("posX %f posY %f mapX %d mapY %d", data->m->posX, data->m->posY, data->m->mapX, data->m->mapY);
            
//             // printf("rayDirX = %f || raydirY = %f\n", data->m->rayDirX, data->m->rayDirY); // to rm
//             if (data->m->rayDirX == 0)
//                 data->m->deltaDistX = 1e30;
//             else
//                 data->m->deltaDistX = fabs(1 / data->m->rayDirX);
//             if (data->m->rayDirY == 0)
//                 data->m->deltaDistY = 1e30;
//             else
//                 data->m->deltaDistY = fabs(1 / data->m->rayDirY);
//             // data->m->deltaDistX = (data->m->rayDirX == 0) ? 1e30 : fabs(1 / data->m->rayDirX); // length of the ray from one x/y side to next x/y side
//             // data->m->deltaDistY = (data->m->rayDirY == 0) ? 1e30 : fabs(1 / data->m->rayDirY);
//             // printf("deltaDistX = %f || deltaDistY = %f\n", data->m->deltaDistX, data->m->deltaDistY); // to rm
//             data->m->hitwall = 0; // is a wall was hit or not

//             if (data->m->rayDirX < 0) // calculate step and initial sideDist
//             {
//                 data->m->stepX = -1;
//                 data->m->sideDistX = (data->m->posX - data->m->mapX) * data->m->deltaDistX;
//             }
//             else
//             {
//                 data->m->stepX = 1;
//                 data->m->sideDistX = (data->m->mapX + 1.0 - data->m->posX) * data->m->deltaDistX;
//             }
//             if (data->m->rayDirY < 0)
//             {
//                 data->m->stepY = -1;
//                 data->m->sideDistY = (data->m->posY - data->m->mapY) * data->m->deltaDistY;
//             }
//             else
//             {
//                 data->m->stepY = 1;
//                 data->m->sideDistY = (data->m->mapY + 1.0 - data->m->posY) * data->m->deltaDistY;
//             }

//             while (!data->m->hitwall) // DDA -- or while loop here
//             {
//                 // go to the next square, either in x-direction or y
//                 if (data->m->sideDistX < data->m->sideDistY)
//                 {
//                     data->m->sideDistX += data->m->deltaDistX;
//                     data->m->mapX  += data->m->stepX;
//                     data->m->side = 0;
//                 }
//                 else
//                 {
//                     data->m->sideDistY += data->m->deltaDistY;
//                     data->m->mapY  += data->m->stepY;
//                     data->m->side = 1;
//                 }
//                 if (data->input->parsed_map[data->m->mapX][data->m->mapY] == '1') // to check if we have hit a wall
//                     data->m->hitwall = 1;
//             }
            

//             // calculate the distance of perpendicular ray
//             if (data->m->side == 0)
//                 data->m->perpWallDist = (data->m->sideDistX - data->m->deltaDistX);
//             else
//                 data->m->perpWallDist = (data->m->sideDistY - data->m->deltaDistY);

//             data->m->lineHeight = (int)(HEIGHT / data->m->perpWallDist); // calc height of line to draw on screen
//             // if (data->m->perpWallDist == 0.0) // CHECK THIS
//             //     data->m->lineHeight = (int)HEIGHT; // CHECK THIS
            
//             // printf("linehieght = %d || perpwalldist = %f || sideDistX = %f || sideDistY = %f\n", data->m->lineHeight, data->m->perpWallDist, data->m->sideDistX, data->m->sideDistY); // to rm
//             //data->m->pitch = 100;
//             data->m->drawStart = ((data->m->lineHeight * -1) / 2) + (HEIGHT / 2); //  + data->m->pitch
//             if (data->m->drawStart < 0)
//                 data->m->drawStart = 0;
//             data->m->drawEnd = (int)((data->m->lineHeight / 2) + (HEIGHT / 2)); //  + data->m->pitch
//             // printf("drawEnd: %d\n", data->m->drawEnd);
//             if (data->m->drawEnd >= HEIGHT)
//                 data->m->drawEnd = HEIGHT - 1;

//             // find something for this -- i would alter the map with 1/2/3/4 -- see upstairs
//             //data->m->addTexture = data->input->parsed_map[data->m->mapX][data->m->mapY] - 1; // -1 to be able to use texture 0

//             if (data->m->side == 0)
//                 data->m->wallX = data->m->posY + data->m->perpWallDist * data->m->rayDirY; 
//             else
//                 data->m->wallX = data->m->posX + data->m->perpWallDist * data->m->rayDirX; 
//             data->m->wallX -= floor((data->m->wallX)); // floor rounds down a floating point number 

//             data->m->textureX = (int)(data->m->wallX * (double)TEXWIDTH); // x coordinate on the texture and mirror the location if necessary
//             if (data->m->side == 0 && data->m->rayDirX > 0)
//                 data->m->textureX = TEXWIDTH - data->m->textureX - 1;
//             if (data->m->side == 1 && data->m->rayDirY < 0)
//                 data->m->textureX = TEXWIDTH - data->m->textureX - 1;

//             data->m->step = 1.0 * TEXHEIGHT / data->m->lineHeight; // how much to increase the texture coordinate per screen pixel
//             data->m->texturePos = (data->m->drawStart - HEIGHT / 2 + data->m->lineHeight / 2) * data->m->step; // start texture coordinate
//             y = data->m->drawStart;
//             // printf("drawStart: %d\n", data->m->drawStart);
//             while (y < data->m->drawEnd)
//             {
//                 data->m->textureY = (int)data->m->texturePos & (TEXWIDTH - 1); // cast text coordinate to int, and mask with the last in case of overflow
//                 data->m->texturePos += data->m->step;
//                 data->m->color = get_pixel(which_wall(data), data->m->textureX, data->m->textureY);
//                 mlx_put_pixel(data->img, x, y, data->m->color);
//                 y++;
//             }   
//             x++;
//         }



//     // }


//     // return (0);
// }