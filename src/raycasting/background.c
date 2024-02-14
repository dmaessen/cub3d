/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 14:45:11 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/14 17:16:56 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft/libft.h"
#include "../include/cub3d.h"
#include "../include/utils.h"
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	background_img(t_data *data)
{
	int		x;
	int		y;
	int32_t	color;
	int32_t	color_floor;

	data->img_back = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img_back)
		return (err_msg("mlx_new_image failed"));
	mlx_image_to_window(data->mlx, data->img_back, 0, 0);
	color = ft_pixel(data->colors->c_color_r, \
	data->colors->c_color_g, data->colors->c_color_b, 0xFF);
	color_floor = ft_pixel(data->colors->f_color_r, \
	data->colors->f_color_g, data->colors->f_color_b, 0xFF);
	y = 0;
	while (y < HEIGHT)
	{
		if (y > (HEIGHT / 2))
			color = color_floor;
		x = -1;
		while (x++ < WIDTH)
			mlx_put_pixel(data->img_back, x, y, color);
		y++;
	}
}

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
