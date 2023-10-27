/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 15:13:33 by dmaessen          #+#    #+#             */
/*   Updated: 2023/04/26 16:41:07 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

// int	main(void)
// {
// 	int	i;
// 	char	s[] = "hek476";
// 	i = ft_strlen(s);
// 	printf("%d", i);
// 	return (0);
// }
