/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: domi <domi@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:44 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/19 20:55:43 by domi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		err_msg("Invalid number of arguments.\n");
	data = calloc(1, sizeof(t_data));
	if (!data)
		err_msg("Calloc failed.\n");
	if (input_validation(data, argv[1]) == 0)
	{
		if (map_validation(data, argv[1], 0) == 0)
		{
			data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
			if (!data->mlx)
				return (err_msg_free("init mlx\n", 3, data), 1);
			init_map(data, data->mlx);
			background_img(data);
			mlx_image_to_window(data->mlx, data->img, 0, 0);
			mlx_loop_hook(data->mlx, &start, data);
			mlx_loop_hook(data->mlx, &move, data);
			mlx_loop(data->mlx);
			mlx_terminate(data->mlx);
		}
	}
	free_struct(data);
	free(data);
	exit(EXIT_SUCCESS);
}
