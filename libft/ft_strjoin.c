/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmaessen <dmaessen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:04:14 by dmaessen          #+#    #+#             */
/*   Updated: 2022/10/27 10:55:01 by dmaessen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len1;
	size_t	len2;
	char	*join;

	len1 = (ft_strlen(s1));
	len2 = (ft_strlen(s2));
	join = (char *)malloc((len1 + len2 + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (s2[i])
	{
		join[len1 + i] = s2[i];
		i++;
	}
	join[len1 + len2] = '\0';
	return (join);
}

// int	main(void)
// {
// 	char const	s1[100] = "ablp--";
// 	char const	s2[100] = "dtkindg2569951=";

// 	printf("%s", ft_strjoin(s1, s2));
// 	return (0);
// }
