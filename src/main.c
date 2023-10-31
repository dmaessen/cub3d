/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:44 by dmaessen          #+#    #+#             */
/*   Updated: 2023/10/31 12:56:18 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <stdio.h> // to rm ??

int main(int argc, char **argv)
{
	//mlx_t *mlx;
	t_data *data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		err_msg("Calloc failled to init the data struct.\n");
	if (argc != 2)
		err_msg("Invalid number of arguments.\n");
	if (input_validation(data, argv[1]) == 0)
	{
		printf("valid input\n"); // to rm
		//if (map_validation())
			// debating if need to check if the path to textures are valid
			// meaning the map is valid
			// so mlx can be initalized
	}
	// something else to free??
	free_struct(data);
	free(data);
	return (0);
}