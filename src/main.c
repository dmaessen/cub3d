/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:44 by dmaessen          #+#    #+#             */
/*   Updated: 2023/11/06 16:09:54 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <stdio.h> // to rm ??

int main(int argc, char **argv)
{
	//mlx_t *mlx;
	t_data *data;

	data = calloc_exit(1, sizeof(t_data));
	if (argc != 2)
		err_msg("Invalid number of arguments.\n");
	if (input_validation(data, argv[1]) == 0) // have something for the error, no??
	{
		printf("valid input\n"); // to rm
		if (map_validation(data, argv[1], 0) == 0) // have something for the error, no??
			printf("valid map\n"); // to rm
			// so mlx can be initalized
	}
	// something else to free??
	free_struct(data);
	free(data);
	return (0);
}