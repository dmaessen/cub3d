/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:34 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/20 15:12:25 by dmaessen         ###   ########.fr       */
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

void	print_msg(char *str)
{
	write(2, str, ft_strlen(str));
}

void	free_exit(t_data *data)
{
	free(data->input);
	free(data->textures->no_texture);
	free(data->textures->we_texture);
	free(data->textures->so_texture);
	free(data->textures->ea_texture);
	free(data->textures);
	free(data->colors);
	free(data);
	exit (1);
}

void	free_struct_exit(t_data *data)
{
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
	free(data);
	exit(1);
}
