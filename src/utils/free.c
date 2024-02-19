/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:34 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/16 12:55:58 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"

void	free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_struct(t_data *data)
{
	printf("here");
	free(data->textures->no_texture);
	free(data->textures->we_texture);
	free(data->textures->so_texture);
	free(data->textures->ea_texture);
	mlx_delete_texture(data->wall[0].tex);
	mlx_delete_texture(data->wall[1].tex);
	mlx_delete_texture(data->wall[2].tex);
	mlx_delete_texture(data->wall[3].tex);
	free(data->wall);
	free(data->textures);
	free(data->colors);
	free_str(data->input->parsed_map);
	free(data->input);
	free(data->m);
}
