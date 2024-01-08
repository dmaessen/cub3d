/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:15:24 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/08 15:39:36 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int raycaster_start(t_data *data)
{
    mlx_t *mlx;
    t_m *m; // to i need to mlloc it??

    m = calloc_exit(1, sizeof(t_m)); // needed -- also free later then
    m->time = 0;
    m->oldtime = 0;
    m->posX = 0;
    pos_player(data, m);
    m->dirX = -1; // like this for testing but change based on facing
    m->dirY = 0;
    m->planeX = 0;
    m->planeY = 0.66; // which results in a 66degre angle for the Field of Vision
    
    mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true); // or do we want to make resize false??
    if (!mlx)
        return (err_msg("init mlx\n"), 1);
    
    //load_textures(data, mlx);
    mlx_texture_t* tex[3];
    tex[0] = mlx_load_png("../textures/1.png");
    tex[1] = mlx_load_png("../textures/2.png");
    tex[2] = mlx_load_png("../textures/3.png");
    tex[3] = mlx_load_png("../textures/4.png");
    if (!tex[0] || !tex[1] || !tex[2] || !tex[3])
        return (err_msg("loading textures\n"), 1);
    
    return (0);
}

// void load_textures(t_data *data, mlx_t *mlx)
// {
    
// }

void pos_player(t_data *data, t_m *m)
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
