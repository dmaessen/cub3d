/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahornstr <ahornstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:26:02 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/19 15:20:43 by ahornstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	format_validation(char *file)
{
	char	*res;

	if (ft_strlen(file) < 4)
		return (1);
	res = ft_substr(file, ft_strlen(file) - 4, 4);
	if (!res)
		err_msg("Malloc failed.\n");
	if (ft_strcmp(res, ".cub") != 0)
		return (free(res), 1);
	free(res);
	return (0);
}

void	validate_colors(t_colors *colors)
{
	if (colors->c_color_b == -1 || colors->c_color_g == -1
		|| colors->c_color_r == -1)
		err_msg("Color for the ceiling missing.\n");
	if (colors->f_color_b == -1 || colors->f_color_g == -1
		|| colors->f_color_r == -1)
		err_msg("Color for the floor missing.\n");
	if (colors->c_color_b < 0 || colors->c_color_b > 255
		|| colors->c_color_r < 0 || colors->c_color_r > 255
		|| colors->c_color_g < 0 || colors->c_color_g > 255)
		err_msg("Invalid color code for the ceiling.\n");
	if (colors->f_color_b < 0 || colors->f_color_b > 255
		|| colors->f_color_r < 0 || colors->f_color_r > 255
		|| colors->f_color_g < 0 || colors->f_color_g > 255)
		err_msg("Invalid color code for the floor.\n");
	if ((colors->f_color_b == colors->c_color_b)
		&& (colors->f_color_r == colors->c_color_r)
		&& (colors->f_color_g == colors->c_color_g))
		err_msg("Colors of the floor and ceiling need to be different.\n");
}

static void	check_missing_texture(t_textures *t)
{
	if (!t->no_texture)
		err_msg("NO texture missing.\n");
	if (!t->ea_texture)
		err_msg("EA texture missing.\n");
	if (!t->we_texture)
		err_msg("WE texture missing.\n");
	if (!t->so_texture)
		err_msg("SO texture missing.\n");
}

void	check_doubles(t_textures *t)
{
	check_missing_texture(t);
	if (ft_strcmp(t->no_texture, t->so_texture) == 0
		&& ft_strlen(t->no_texture) == ft_strlen(t->so_texture))
		err_msg("The textures of NO and SO need to be different.\n");
	if (ft_strcmp(t->no_texture, t->we_texture) == 0
		&& ft_strlen(t->no_texture) == ft_strlen(t->we_texture))
		err_msg("The textures of NO and WE need to be different.\n");
	if (ft_strcmp(t->no_texture, t->ea_texture) == 0
		&& ft_strlen(t->no_texture) == ft_strlen(t->ea_texture))
		err_msg("The textures of NO and EA need to be different.\n");
	if (ft_strcmp(t->so_texture, t->we_texture) == 0
		&& ft_strlen(t->so_texture) == ft_strlen(t->we_texture))
		err_msg("The textures of WE and SO need to be different.\n");
	if (ft_strcmp(t->so_texture, t->ea_texture) == 0
		&& ft_strlen(t->so_texture) == ft_strlen(t->ea_texture))
		err_msg("The textures of SO and EA need to be different.\n");
	if (ft_strcmp(t->we_texture, t->ea_texture) == 0
		&& ft_strlen(t->we_texture) == ft_strlen(t->ea_texture))
		err_msg("The textures of WE and EA need to be different.\n");
}

void	check_image(char *path)
{
	char	*res;
	char	*pos;
	bool	trim;

	pos = ft_strrchr(path, '.');
	if (ft_strlen(path) < 4 || ft_strlen(pos) < 4 || pos == NULL)
		err_msg("Wrong texture extension, only .png and .jpg supported\n");
	trim = false;
	while (ft_strchr(pos, '\n') != 0)
	{
		trim = true;
		pos = ft_strtrim(pos, "\n");
	}
	res = ft_substr(pos, 0, ft_strlen(pos));
	if (ft_strcmp(res, ".png") != 0 && ft_strcmp(res, ".jpg") != 0)
	{
		if (trim == true)
			free(pos);
		free(res);
		err_msg("Wrong texture extension, only .png and .jpg supported\n");
	}
	if (trim == true)
		free(pos);
	free(res);
}
