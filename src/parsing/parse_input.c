/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:23 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/19 15:19:26 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

static void	init_data(t_data *data)
{
	data->textures = calloc_exit(1, sizeof(t_textures));
	data->colors = calloc_exit(1, sizeof(t_colors));
	data->colors->c_color_b = -1;
	data->colors->c_color_g = -1;
	data->colors->c_color_r = -1;
	data->colors->f_color_b = -1;
	data->colors->f_color_g = -1;
	data->colors->f_color_r = -1;
	data->input = calloc_exit(1, sizeof(t_data_input));
}

static void	split_colorcode(t_data *data, char *color, int id)
{
	char	**color_code;

	color_code = ft_split(color, ',');
	if (!color_code)
		err_msg_free("Split failed\n", 2, data); // but then str from the other needs freeing too..
	if (id == 1)
	{
		if (color_code[0])
			data->colors->c_color_b = ft_atoi(color_code[0]);
		if (color_code[1])
			data->colors->c_color_g = ft_atoi(color_code[1]);
		if (color_code[2])
			data->colors->c_color_r = ft_atoi(color_code[2]);
	}
	if (id == 2)
	{
		if (color_code[0])
			data->colors->f_color_b = ft_atoi(color_code[0]);
		if (color_code[1])
			data->colors->f_color_g = ft_atoi(color_code[1]);
		if (color_code[2])
			data->colors->f_color_r = ft_atoi(color_code[2]);
	}
	free_str(color_code);
}

void	add_data(t_data *data, char **str, int i)
{
	if (ft_strncmp(str[i], "NO", 2) == 0 && str[i + 1])
	{
		data->textures->no_texture = ft_strdup_check(str[i + 1]);
		check_image(data->textures->no_texture);
	}
	if (ft_strncmp(str[i], "SO", 2) == 0 && str[i + 1])
	{
		data->textures->so_texture = ft_strdup_check(str[i + 1]);
		check_image(data->textures->so_texture);
	}
	if (ft_strncmp(str[i], "WE", 2) == 0 && str[i + 1])
	{
		data->textures->we_texture = ft_strdup_check(str[i + 1]);
		check_image(data->textures->we_texture);
	}
	if (ft_strncmp(str[i], "EA", 2) == 0 && str[i + 1])
	{
		data->textures->ea_texture = ft_strdup_check(str[i + 1]);
		check_image(data->textures->ea_texture);
	}
}

int	parse_line(t_data *data, char *line)
{
	char	**str;
	int		i;

	data->input->player = false;
	str = ft_split(line, ' ');
	if (!str)
		err_msg_free("Spliting line\n", 1, data);
	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], "NO", 2) == 0
			|| ft_strncmp(str[i], "SO", 2) == 0
			|| ft_strncmp(str[i], "WE", 2) == 0
			|| ft_strncmp(str[i], "EA", 2) == 0)
			add_data(data, str, i);
		else if (ft_strncmp(str[i], "C", 1) == 0 && str[i + 1])
			split_colorcode(data, str[i + 1], 1);
		else if (ft_strncmp(str[i], "F", 1) == 0 && str[i + 1])
			split_colorcode(data, str[i + 1], 2);
		i++;
	}
	free_str(str);
	return (0);
}

int	input_validation(t_data *data, char *file)
{
	int		fd;
	char	*line;

	if (format_validation(file) == 1)
		err_msg("Wrong file extension, should be: .cub\n");
	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_msg("Opening the file\n");
	init_data(data);
	data->input->nb_lines = 0;
	while (1)
	{
		line = get_next_line_exit(fd);
		if (line == NULL)
			break ;
		if (ft_strcmp(line, "\n\0") != 0)
			data->input->nb_lines++;
		if (parse_line(data, line) == 1)
			return (free(line), close(fd), 1);
		free(line);
	}
	close(fd);
	if (check_doubles(data->textures) == 1
	|| validate_colors(data->colors) == 1)
		free_exit(data);
	return (0);
}
