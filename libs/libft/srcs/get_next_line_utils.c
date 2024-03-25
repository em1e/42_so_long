/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/02 12:07:02 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/03 08:11:34 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	unsigned char		*d;
	const unsigned char	*s;
	int					i;

	i = 0;
	if (!dest && !src)
		return (0);
	d = dest;
	s = src;
	while (len-- > 0)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = ft_strlen(s1);
	s2 = malloc(len + 1);
	if (!s2)
		return (0);
	return (ft_memcpy(s2, s1, len + 1));
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*s3;

	if (!s1 || !s2)
		return (0);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3 = malloc(s1_len + s2_len + 1);
	if (!s3)
		return (0);
	ft_memcpy(s3, s1, s1_len);
	ft_memcpy(s3 + s1_len, s2, s2_len + 1);
	return (s3);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
