/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 17:00:31 by jihyukim          #+#    #+#             */
/*   Updated: 2022/04/21 16:27:20 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

int	gnl_strchr(const char *s)
{
	int	i;

	i = -1;
	while (s[++i] != '\0')
	{
		if (s[i] == '\n')
			return (i + 1);
	}
	return (0);
}

void	gnl_strlcpy(char *dst, const char *src, int dstsize)
{
	int	i;

	i = -1;
	while (src[++i] && i + 1 < dstsize)
		dst[i] = src[i];
	if (dstsize > 0)
		dst[i] = 0;
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
	while (s1[++i])
		ret[i] = s1[i];
	j = -1;
	while (s2[++j])
		ret[i++] = s2[j];
	ret[i] = 0;
	return (ret);
}
