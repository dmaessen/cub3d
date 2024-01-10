/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:15:24 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/10 15:50:31 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

// to implement 
    // left + right arrow -- to only "trun your head in the maze"
    // WASD keys -- allow you to move
    // ESC -- closes and cleans the prog
void move(mlx_key_data_t keydata, void *param)
{
    if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		//move_up((t_data *)param);
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		//move_left((t_data *)param);
	else if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		//move_down((t_data *)param);
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		//move_right((t_data *)param);
    else if ((keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)) // arrow left
        // look left
    else if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS) // arrow right
        // look right
	else if ((keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS))
		exit(EXIT_SUCCESS);
}