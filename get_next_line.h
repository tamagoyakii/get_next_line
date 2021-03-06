/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:10:48 by jihyukim          #+#    #+#             */
/*   Updated: 2022/04/13 16:51:07 by jihyukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
char	*get_until_newline(char *line_merged, char *backup);
char	*get_line(char *line_merged, char *backup);
void	gnl_bzero(char *backup);
size_t	ft_strlen(const char *s);
int		gnl_strchr(const char *s);
void	gnl_strlcpy(char *dst, const char *src, int dstsize);
char	*gnl_strjoin(char *s1, char *s2);

#endif
