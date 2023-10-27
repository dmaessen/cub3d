/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 16:18:44 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/19 11:51:57 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if ((s1[i] < s2[i]) || (s1[i] > s2[i]))
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else
			i++;
	}
	return (0);
}

// int	main(void)
// {
// 	const char s1[100] = {"df\300ghjkl"};
// 	const char s2[100] = {"df\0ghjkl"};
// 	int result;
// 	result = ft_strncmp(s1, s2, 5);
// 	printf("%d \n", strncmp(s1, s2, 5));
// 	printf("%d", result);
// }
