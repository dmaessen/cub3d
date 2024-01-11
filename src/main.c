/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:44 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/11 15:23:36 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <stdio.h> // to rm ??

int main(int argc, char **argv)
{
	mlx_t *mlx;
	t_data *data;

	if (argc != 2)
		err_msg("Invalid number of arguments.\n");
	data = calloc_exit(1, sizeof(t_data));
	if (input_validation(data, argv[1]) == 0) // have something for the error, no??
	{
		printf("valid input\n"); // to rm
		if (map_validation(data, argv[1], 0) == 0) // have something for the error, no??
		{
			printf("valid map\n"); // to rm
			mlx = mlx_init(WIDTH, HEIGHT, "cub3D", true); // or do we want to make resize false??
			if (!mlx)
				return (err_msg("init mlx\n"), 1);
			raycaster_start(data, mlx); 
			//mlx_loop_hook(mlx, &move, data); // look into these hooks
			mlx_loop(mlx);
			mlx_terminate(mlx); // needed??
		}
	}
	free_struct(data);
	free(data);
	return (0);
}