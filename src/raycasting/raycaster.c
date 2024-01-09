/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:15:24 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/09 17:06:43 by domi             ###   ########.fr       */
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

static void alter_walls(t_data *data) 
{
    int i;
    int j;

    i = 0;
    while (data->input->parsed_map[i])
    {
        j = 0;
        while (data->input->parsed_map[i][j] && i == data->input->nb_lines - 6) // SO
        {
            if (data->input->parsed_map[i][j] == 1)
                data->input->parsed_map[i][j] = '4';
            j++;
        }
        i++; 
    }
    i = 0;
    while (data->input->parsed_map[i])
    {
        j = 0;
        while (data->input->parsed_map[i][j]) // SO
        {
            if ((j == 0 && data->input->parsed_map[i][j] != 0) 
            || (data->input->parsed_map[i][j] != 0 && data->input->parsed_map[i][j - 1] == ' ')) 
                data->input->parsed_map[i][j] = '2'; // WE
            if (data->input->parsed_map[i][j] != 0 && (data->input->parsed_map[i][j + 1] == ' '
            || data->input->parsed_map[i][j - 1] == '\n' || data->input->parsed_map[i][j - 1] == '\0')) 
                data->input->parsed_map[i][j] = '3'; // EA
            j++;
        }
        printf("%s",data->input->parsed_map[i]);
        i++;
    }
    

}


int raycaster_start(t_data *data) // , mlx_t *mlx
{
    t_map *m; // to i need to mlloc it??

    m = calloc_exit(1, sizeof(t_map)); // needed -- also free later then
    m->time = 0;
    m->oldtime = 0;
    m->posX = 0;
    pos_player(data, m);
    m->dirX = -1; // like this for testing but change based on facing
    m->dirY = 0;
    m->planeX = 0;
    m->planeY = 0.66; // which results in a 66degre angle for the Field of Vision
    
    //load_textures(data, mlx);
	mlx_texture_t* tex[3];
	tex[0] = mlx_load_png(data->textures->no_texture);
	tex[1] = mlx_load_png(data->textures->so_texture);
	tex[2] = mlx_load_png(data->textures->we_texture);
	tex[3] = mlx_load_png(data->textures->ea_texture);
	if (!tex[0] || !tex[1] || !tex[2] || !tex[3])
		return (err_msg("loading textures\n"), 1);
    
    alter_walls(data);
    
    int x;
    int y;
    while (1) // because idk what else for now
    {
        x = 0;
        while (x < WIDTH) // ou width de la map?? 
        {
            m->cameraX = 2 * x / (double)WIDTH - 1; // to calculate the ray position and direction
            m->rayDirX = m->dirX + m->planeX * m->cameraX;
            m->rayDirY = m->dirY + m->planeY * m->cameraX;
            m->mapX = (int)m->posX; // to know in which square of the map the ray is in
            m->mapY = (int)m->posY;
            m->deltaDistX = (m->rayDirX == 0) ? 1e30 : abs(1 / m->rayDirX); // length of the ray from one x/y side to next x/y side
            m->deltaDistY = (m->rayDirY == 0) ? 1e30 : abs(1 / m->rayDirY);
            m->hit = 0; // is a wall was hit or not
            
            if (m->rayDirX < 0) // calculate step and initial sideDist
            {
                m->stepX = -1;
                m->sideDistX = (m->posX - m->mapX) * m->deltaDistX;
            }
            else
            {
                m->stepX = 1;
                m->sideDistX = (m->mapX + 1.0 - m->posX) * m->deltaDistX;
            }
            if (m->rayDirY < 0)
            {
                m->stepY = -1;
                m->sideDistY = (m->posY - m->mapY) * m->deltaDistY;
            }
            else
            {
                m->stepY = 1;
                m->sideDistY = (m->mapY + 1.0 - m->posY) * m->deltaDistY;
            }

            while (m->hit == 0) // DDA
            {
                // go to the ext square, either in x-direction or y
                if (m->sideDistX < m->sideDistY)
                {
                    m->sideDistX += m->deltaDistX;
                    m->mapX  += m->stepX;
                    m->side = 0;
                }
                else
                {
                    m->sideDistY += m->deltaDistY;
                    m->mapY  += m->stepY;
                    m->side = 1;
                }
                if (data->input->parsed_map[m->mapX][m->mapY] > 0) // to check if we have hit a wall
                    m->hit = 1;
            }

            if (m->side == 0)
                m->perpWallDist = (m->sideDistX - m->deltaDistX);
            else
                m->perpWallDist = (m->sideDistY - m->deltaDistY);

            m->lineHeight = (int)(HEIGHT / m->perpWallDist); // calc height of line to draw on screen
            m->pitch = 100;
            m->drawStart = -m->lineHeight / 2 + HEIGHT / 2 + m->pitch;
            if (m->drawStart < 0)
                m->drawStart = 0;
            m->drawEnd = m->lineHeight / 2 + HEIGHT / 2 + m->picth;
            if (m->drawEnd >= HEIGHT)
                m->drawEnd = HEIGHT - 1;
        
            // find something for this -- i would alter the map with 1/2/3/4 -- see upstairs
            m->addTexture = data->input->parsed_map[m->mapX][m->mapY] - 1; // -1 to be able to use texture 0

            if (m->side == 0)
                m->wallX = m->posY + m->perpWallDist * m->rayDirY; 
            else
                m->wallX = m->posX + m->perpWallDist * m->rayDirX; 
            m->wallX -= floor((m->wallX)); // floor rounds down a flowting point number 
                
            m->textureX = (int)(m->wallX * (double)texWidth); // x coordinate on the texture
            if (m->side == 0 && m->rayDirX > 0)
                m->textureX = texWidth - m->textureX - 1;
            if (m->side == 1 && m->rayDirY < 0)
                m->textureX = texWidth - m->textureX - 1;
            
            m->step = 1.0 * texHeight / m->lineHeight; // how much to increase the texture coordinate per screen pixel
            m->texturePos = (m->drawStart - m->pitch - HEIGHT / 2 + m->lineHeight / 2) * m->step; // start texture coordinate
            y = m->drawStart;
            while (y < m->drawEnd)
            {
                m->textureY = (int)m->texturePos & (texHeight - 1); // cast text coordinate to int, and mask with the last in case of overflow
                m->texturePos += m->step;
                m->color = tex[m->addTexture];
                //m->color = tex[m->addTexture][texHeight * m->textureX + m->textureY]; 
                if (m->side == 1)
                    m->color = (m->color >> 1) & 8355711;
                buffer[y][x] = m->color;
                y++;
            }   
            x++;
        }
        
        // FROM DRAWBUFFER()...
        // drawBuffer(buffer[0]); // LOOK WHAT THIS NEEDS TO DO OR IF BUILT_IN
        // y = 0;
        // x = 0;
        // while ( )

        
    }
    
    
    return (0);
}

// void load_textures(t_data *data, mlx_t *mlx)
// {
    
// }

void pos_player(t_data *data, t_map *m)
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
                m->posY = (double)col + 1;
                m->posX = (double)i + 1;
                break;
            }
            col++;
        }
        if (m->posX != 0)
            break;
        i++;
    }
}
