/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:15:24 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/15 15:55:13 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

uint32_t buffer[HEIGHT][WIDTH];

// static void alter_walls(t_data *data) 
// {
//     int i;
//     int j;

//     i = 0;
//     while (data->input->parsed_map[i])
//     {
//         j = 0;
//         while (data->input->parsed_map[i][j] && i == data->input->nb_lines - 6) // SO
//         {
//             if (data->input->parsed_map[i][j] == 1)
//                 data->input->parsed_map[i][j] = '4';
//             j++;
//         }
//         i++; 
//     }
//     i = 0;
//     while (data->input->parsed_map[i])
//     {
//         j = 0;
//         while (data->input->parsed_map[i][j]) // SO
//         {
//             if ((j == 0 && data->input->parsed_map[i][j] != 0) 
//             || (data->input->parsed_map[i][j] != 0 && data->input->parsed_map[i][j - 1] == ' ')) 
//                 data->input->parsed_map[i][j] = '2'; // WE
//             if (data->input->parsed_map[i][j] != 0 && (data->input->parsed_map[i][j + 1] == ' '
//             || data->input->parsed_map[i][j - 1] == '\n' || data->input->parsed_map[i][j - 1] == '\0')) 
//                 data->input->parsed_map[i][j] = '3'; // EA
//             j++;
//         }
//         printf("%s",data->input->parsed_map[i]);
//         i++;
//     }
    

// }


int raycaster_start(t_data *data, mlx_t *mlx) // , mlx_t *mlx
{
    data->m = calloc_exit(1, sizeof(t_map)); // needed -- also free later then
    // data->m->time = 0;
    // data->m->oldtime = 0;
    // data->m->posX = 0;
    pos_player(data); // fills in posY and posX
    dir_player(data); // 
    // data->m->dirX = -1; // like this for testing but change based on facing
    // data->m->dirY = 0;
    data->m->angleFOV = 0.66; // which results in a 66degre angle for the Field of Vision
    data->m->planeX = 0;
    data->m->planeY = 0.66; 
    
    //load_textures(data, mlx);
    data->wall = malloc(4 * sizeof(t_wall));
    if (!data->wall)
        return (err_msg("malloc failed"), 1);
	//mlx_texture_t* tex[4];
	data->wall[0].tex = mlx_load_png(data->textures->no_texture);
	data->wall[1].tex = mlx_load_png(data->textures->so_texture);
	data->wall[2].tex = mlx_load_png(data->textures->we_texture);
	data->wall[3].tex = mlx_load_png(data->textures->ea_texture);
	// if (!data->wall->tex[0] || !data->wall->tex[1] || !data->wall->tex[2] || !data->wall->tex[3])
	// 	return (err_msg("loading textures\n"), 1);
    
    //alter_walls(data);
    
    data->img = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!data->img)
        return (err_msg("mlx_new_image failed"), 1);
    
    // mlx_image_t* img[4];
    // img[0] = mlx_texture_to_image(mlx, tex[0]);
    // img[1] = mlx_texture_to_image(mlx, tex[1]);
    // img[2] = mlx_texture_to_image(mlx, tex[2]);
    // img[3] = mlx_texture_to_image(mlx, tex[3]);
	// if (!img[0] || !img[1] || !img[2] || !img[3])
	// 	return (err_msg("loading img for textures\n"), 1);
    
    // if (mlx_image_to_window(mlx, img[0], 0, 0) < 0)
    //     return (err_msg("mlx_image_to_window\n"), 1);
    // if (mlx_image_to_window(mlx, img[1], 0, 0) < 0)
    //     return (err_msg("mlx_image_to_window\n"), 1);
    // if (mlx_image_to_window(mlx, img[2], 0, 0) < 0)
    //     return (err_msg("mlx_image_to_window\n"), 1);
    // if (mlx_image_to_window(mlx, img[3], 0, 0) < 0)
    //     return (err_msg("mlx_image_to_window\n"), 1);
    
    int x;
    int y;
    while (1) // because idk what else for now
    {
        x = 0;
        while (x < WIDTH) // ou width de la map?? 
        {
            data->m->cameraX = 2 * x / (double)WIDTH - 1; // to calculate the ray position and direction
            data->m->rayDirX = data->m->dirX + data->m->planeX * data->m->cameraX;
            data->m->rayDirY = data->m->dirY + data->m->planeY * data->m->cameraX;
            data->m->mapX = (int)data->m->posX; // to know in which square of the map the ray is in
            data->m->mapY = (int)data->m->posY;
            data->m->deltaDistX = (data->m->rayDirX == 0) ? 1e30 : fabs(1 / data->m->rayDirX); // length of the ray from one x/y side to next x/y side
            data->m->deltaDistY = (data->m->rayDirY == 0) ? 1e30 : fabs(1 / data->m->rayDirY);
            data->m->hit = 0; // is a wall was hit or not
            
            if (data->m->rayDirX < 0) // calculate step and initial sideDist
            {
                data->m->stepX = -1;
                data->m->sideDistX = (data->m->posX - data->m->mapX) * data->m->deltaDistX;
            }
            else
            {
                data->m->stepX = 1;
                data->m->sideDistX = (data->m->mapX + 1.0 - data->m->posX) * data->m->deltaDistX;
            }
            if (data->m->rayDirY < 0)
            {
                data->m->stepY = -1;
                data->m->sideDistY = (data->m->posY - data->m->mapY) * data->m->deltaDistY;
            }
            else
            {
                data->m->stepY = 1;
                data->m->sideDistY = (data->m->mapY + 1.0 - data->m->posY) * data->m->deltaDistY;
            }

            while (data->m->hit == 0) // DDA
            {
                // go to the ext square, either in x-direction or y
                if (data->m->sideDistX < data->m->sideDistY)
                {
                    data->m->sideDistX += data->m->deltaDistX;
                    data->m->mapX  += data->m->stepX;
                    data->m->side = 0;
                }
                else
                {
                    data->m->sideDistY += data->m->deltaDistY;
                    data->m->mapY  += data->m->stepY;
                    data->m->side = 1;
                }
                if (data->input->parsed_map[data->m->mapX][data->m->mapY] > 0) // to check if we have hit a wall
                    data->m->hit = 1;
            }

            if (data->m->side == 0)
                data->m->perpWallDist = (data->m->sideDistX - data->m->deltaDistX);
            else
                data->m->perpWallDist = (data->m->sideDistY - data->m->deltaDistY);

            data->m->lineHeight = (int)(HEIGHT / data->m->perpWallDist); // calc height of line to draw on screen
            data->m->pitch = 100;
            data->m->drawStart = -data->m->lineHeight / 2 + HEIGHT / 2 + data->m->pitch;
            if (data->m->drawStart < 0)
                data->m->drawStart = 0;
            data->m->drawEnd = data->m->lineHeight / 2 + HEIGHT / 2 + data->m->pitch;
            if (data->m->drawEnd >= HEIGHT)
                data->m->drawEnd = HEIGHT - 1;
        
            // find something for this -- i would alter the map with 1/2/3/4 -- see upstairs
            data->m->addTexture = data->input->parsed_map[data->m->mapX][data->m->mapY] - 1; // -1 to be able to use texture 0

            if (data->m->side == 0)
                data->m->wallX = data->m->posY + data->m->perpWallDist * data->m->rayDirY; 
            else
                data->m->wallX = data->m->posX + data->m->perpWallDist * data->m->rayDirX; 
            data->m->wallX -= floor((data->m->wallX)); // floor rounds down a floating point number 
                
            data->m->textureX = (int)(data->m->wallX * (double)texWidth); // x coordinate on the texture
            if (data->m->side == 0 && data->m->rayDirX > 0)
                data->m->textureX = texWidth - data->m->textureX - 1;
            if (data->m->side == 1 && data->m->rayDirY < 0)
                data->m->textureX = texWidth - data->m->textureX - 1;
            
            data->m->step = 1.0 * texHeight / data->m->lineHeight; // how much to increase the texture coordinate per screen pixel
            data->m->texturePos = (data->m->drawStart - data->m->pitch - HEIGHT / 2 + data->m->lineHeight / 2) * data->m->step; // start texture coordinate
            y = data->m->drawStart;
            while (y < data->m->drawEnd)
            {
                data->m->textureY = (int)data->m->texturePos & (texHeight - 1); // cast text coordinate to int, and mask with the last in case of overflow
                data->m->texturePos += data->m->step;
                //data->m->color = tex[data->m->addTexture];
                //data->m->color = tex[data->m->addTexture][texHeight * data->m->textureX + data->m->textureY]; 
                // if (data->m->side == 1)
                //     data->m->color = (data->m->color >> 1) & 8355711;
                // buffer[y][x] = data->m->color;
                y++;
            }   
            x++;
        }
        
        // FROM DRAWBUFFER()...
        //drawBuffer(buffer[0]); // LOOK WHAT THIS NEEDS TO DO OR IF BUILT_IN
        
        // mlx_image_t *img;
        // img = mlx_new_image(mlx, WIDTH, HEIGHT);
        // if (!img)
        //     err_msg("mlx_new_image failed\n");
        
        y = 0; 
        while (y < HEIGHT) // tis correct?? -- clearing buffer
        {
            x = 0;
            while (x < WIDTH)
            {
                buffer[y][x] = 0;
                x++;
            }
            y++;
        }
        
        
    }
    
    
    return (0);
}

// void load_textures(t_data *data, mlx_t *mlx)
// {
    
// }

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
                data->m->posY = (double)col + 1;
                data->m->posX = (double)i + 1;
                break;
            }
            col++;
        }
        if (data->m->posX != 0)
            break;
        i++;
    }
}

static void dir_player(t_data *data)
{
    if (data->input->player_facing == P_NORTH)
    {
        data->m->dirX = -1;
        data->m->dirY = 0;
    }
    if (data->input->player_facing == P_SOUTH)
    {
        data->m->dirX = 1;
        data->m->dirY = 0;
    }
    if (data->input->player_facing == P_EAST)
    {
        data->m->dirX = 0;
        data->m->dirY = 1;
    }
    if (data->input->player_facing == P_WEST)
    {
        data->m->dirX = 0;
        data->m->dirY = -1;
    }
}