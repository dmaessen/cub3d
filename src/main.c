/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:44 by dmaessen          #+#    #+#             */
/*   Updated: 2024/01/16 10:00:35 by domi             ###   ########.fr       */
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
			mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false); // or do we want to make resize true??
			if (!mlx)
				return (err_msg("init mlx\n"), 1);
			init_map(data, mlx);
			mlx_image_to_window(mlx, data->img, 0, 0);
			mlx_loop_hook(mlx, &start, data); 
			//mlx_loop_hook(mlx, &move, data); // look into these hooks
			mlx_loop(mlx);
			mlx_terminate(mlx); // needed??
		}
	}
	// delete textures as well
	free_struct(data);
	free(data);
	return (0);
}