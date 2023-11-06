/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:34 by dmaessen          #+#    #+#             */
/*   Updated: 2023/11/06 15:43:40 by dmaessen         ###   ########.fr       */
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
	data->textures->no_texture = NULL;
	free(data->textures->so_texture);
	data->textures->so_texture = NULL;
	free(data->textures->we_texture);
	data->textures->we_texture = NULL;
	free(data->textures->ea_texture);
	data->textures->ea_texture = NULL;
	free(data->textures);
	free(data->colors);
	free(data->input);
	free_str(data->input->parsed_map);
}
