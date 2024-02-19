/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:30 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/19 15:38:42 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <unistd.h>

static int free_from_pos(int i, t_data *data)
{
	if (i == 1)
	{
		free(data->textures);
		free(data->colors);
		free(data); // right
	}
	if (i == 2)
	{
		free(data->textures->no_texture);
		free(data->textures->we_texture);
		free(data->textures->so_texture);
		free(data->textures->ea_texture);
		free(data->textures);
		free(data->colors);
		free(data); // right
	}
	if (i == 3)
	{
		free(data->textures->no_texture);
		free(data->textures->we_texture);
		free(data->textures->so_texture);
		free(data->textures->ea_texture);
		free(data->textures);
		free(data->colors);
		free_str(data->input->parsed_map);
		free(data->input);
		free(data); // right
	}
}

void	err_msg_free(char *str, int i, t_data *data)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	free_from_pos(i, data);
	exit (1);
}

void	err_msg(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit (1);
}

void print_msg(char *str)
{
	write(2, str, ft_strlen(str));
}

void free_exit(t_data *data)
{
	// du coup deja un message imprimer avant
	free(data->textures->no_texture);
	free(data->textures->we_texture);
	free(data->textures->so_texture);
	free(data->textures->ea_texture);
	free(data->textures);
	free(data->colors);
	free(data); // right
	exit (1);
}