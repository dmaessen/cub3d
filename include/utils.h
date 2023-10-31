/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:43:43 by dmaessen          #+#    #+#             */
/*   Updated: 2023/10/31 10:43:48 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "cub3d.h"

/**
 * prints out "Error" followed by an explicit error message on a new line
 * @param str error message
 */
void	err_msg(char *str);

/**
 * frees the content of str single and double pointer
 * @param str 
 */
void	free_str(char **str);
/**
 * frees the content of the textures and colors stored in data, and resets them to NULL
 * @param data data struct
 */
void	free_struct(t_data *data);

/**
 * compares the null-terminated strings s1 and s2.
 * returns an integer greater than, equal to, or less than 0, according as the string s1 is greater than, equal
 * to, or less than the string s2. The comparison is done using unsigned characters, so that ‘\200’ is greater than ‘\0’.
 * @param s1 string 1 to be compared
 * @param s2 string 2 to be compared
 */
int		ft_strcmp(const char *s1, const char *s2);

#endif