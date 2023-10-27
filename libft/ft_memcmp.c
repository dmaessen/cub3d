/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 15:28:28 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/27 10:48:58 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	char	*x1;
	char	*x2;

	x1 = (void *)s1;
	x2 = (void *)s2;
	i = 0;
	while (i < n)
	{
		if ((x1[i] < x2[i]) || (x1[i] > x2[i]))
			return ((unsigned char)x1[i] - (unsigned char)x2[i]);
		else
			i++;
	}
	return (0);
}

// int	main(void)
// {
// 	// const char s1[100] = {"abc"};
// 	// const char s2[100] = {"abc"};
// 	int result;
// 	result = ft_memcmp("abc", "abc", 7);
// 	printf("%d \n", memcmp("abc", "abc", 7));
// 	printf("%d", result);
// }
