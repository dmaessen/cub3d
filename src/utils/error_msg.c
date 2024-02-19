/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:30 by dmaessen          #+#    #+#             */
/*   Updated: 2024/02/19 13:46:54 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <unistd.h>

static int free_from_pos(int i)
{
	if (i = 1)
		// something
	if (i = 2)
		// something else
}

void	err_msg(char *str, int i)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	free_from_pos(i);
	exit (1);
}
