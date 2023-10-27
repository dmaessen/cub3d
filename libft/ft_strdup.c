/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 10:32:24 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/31 18:23:18 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*ptr;

	size = ft_strlen(s1);
	ptr = (char *)malloc((size + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

// int	main(void)
// {
// 	const char	s1[] = "12548-0oi2@ß   . ";

// 	ft_strdup(s1);
// 	printf("%s \n", ft_strdup(s1));
// 	printf("%s \n", strdup(s1));
// 	return (0);
// }
