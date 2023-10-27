/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/10 17:48:16 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/20 15:22:35 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*str;

	str = (char *)s;
	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (s[i] == (char)c)
		return (&str[i]);
	return (0);
}

// int	main(void)
// {
// 	const char s[30] = "Everyth1ing h25-elsye";
// 	printf("%s MINE \n", ft_strchr(s, 'y'));
// 	printf("%s THE ONE", strchr(s, 'y'));
// }
