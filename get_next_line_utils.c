/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:10:38 by jihyukim          #+#    #+#             */
/*   Updated: 2022/04/13 13:53:39 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

size_t	gnl_strchr(const char *s)
{
	size_t	i;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '\n')
			return (i);
	}
	return (0);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = -1;
	while (src[++i] && i + 1 < dstsize)
		dst[i] = src[i];
	if (dstsize > 0)
		dst[i] = 0;
	return (ft_strlen(src));
}

char	*ft_strdup(const char *s)
{
	char	*ret;
	int		len;
	int		i;

	len = ft_strlen(s);
	ret = (char *)malloc(sizeof(char) * (len + 1));
	if (!(ret))
		return (0);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i] = 0;
	return (ret);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*ret;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (0);
	ret = (char *)malloc(sizeof(char) * (
				ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ret)
		return (0);
	i = -1;
	while(s1[++i])
		ret[i] = s1[i];
	j = -1;
	while(s2[++j])
		ret[i++] = s2[j];
	ret[i] = 0;
	return (ret);
}
