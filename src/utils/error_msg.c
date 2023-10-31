/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:41:30 by dmaessen          #+#    #+#             */
/*   Updated: 2023/10/31 10:41:31 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/utils.h"
#include <unistd.h>

void	err_msg(char *str)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	exit (1);
}
