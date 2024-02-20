/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:30 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/20 10:51:30 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <unistd.h>

static void free_from_pos1(int i, t_data *data)
{
	if (i == 1)
	{
		free(data->textures);
		free(data->colors);
		free(data->input);
		free(data); // right
	}
}

static void free_from_pos2(int i, t_data *data)
{
	if (i == 2)
	{
		free(data->textures->no_texture);
		free(data->textures->we_texture);
		free(data->textures->so_texture);
		free(data->textures->ea_texture);
		free(data->textures);
		free(data->colors);
		free(data->input);
		free(data); // right
	}
}

static void free_from_pos3(int i, t_data *data)
{
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
	if (i == 1)
		free_from_pos1(i, data);
	else if (i == 2)
		free_from_pos2(i, data);
	else if (i == 3)
		free_from_pos3(i, data);
	exit (1);
}

void	err_msg(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit (1);
}
