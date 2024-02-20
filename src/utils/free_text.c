/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_text.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:34 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/20 12:04:40 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"

void	free_struct_all(t_data *data)
{
	free(data->textures->no_texture);
	free(data->textures->we_texture);
	free(data->textures->so_texture);
	free(data->textures->ea_texture);
	free(data->wall);
	free(data->textures);
	free(data->colors);
	free_str(data->input->parsed_map);
	free(data->input);
	free(data->m);
	free(data);
	exit(1);
}

void	free_tex1(t_data *data)
{
	free(data->textures->no_texture);
	free(data->textures->we_texture);
	free(data->textures->so_texture);
	free(data->textures->ea_texture);
	free(data->wall);
	free(data->textures);
	free(data->colors);
	free_str(data->input->parsed_map);
	free(data->input);
	free(data->m);
	free(data);
	exit(1);
}

void	free_tex2(t_data *data)
{
	free(data->textures->no_texture);
	free(data->textures->we_texture);
	free(data->textures->so_texture);
	free(data->textures->ea_texture);
	mlx_delete_texture(data->wall[0].tex);
	free(data->wall);
	free(data->textures);
	free(data->colors);
	free_str(data->input->parsed_map);
	free(data->input);
	free(data->m);
	free(data);
	exit(1);
}

void	free_tex3(t_data *data)
{
	free(data->textures->no_texture);
	free(data->textures->we_texture);
	free(data->textures->so_texture);
	free(data->textures->ea_texture);
	mlx_delete_texture(data->wall[0].tex);
	mlx_delete_texture(data->wall[1].tex);
	free(data->wall);
	free(data->textures);
	free(data->colors);
	free_str(data->input->parsed_map);
	free(data->input);
	free(data->m);
	free(data);
	exit(1);
}

void	free_tex4(t_data *data)
{
	free(data->textures->no_texture);
	free(data->textures->we_texture);
	free(data->textures->so_texture);
	free(data->textures->ea_texture);
	mlx_delete_texture(data->wall[0].tex);
	mlx_delete_texture(data->wall[1].tex);
	mlx_delete_texture(data->wall[2].tex);
	free(data->wall);
	free(data->textures);
	free(data->colors);
	free_str(data->input->parsed_map);
	free(data->input);
	free(data->m);
	free(data);
	exit(1);
}
