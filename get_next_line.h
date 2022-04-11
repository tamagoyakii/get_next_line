/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihyukim <jihyukim@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 14:10:48 by jihyukim          #+#    #+#             */
/*   Updated: 2022/04/11 18:13:56 by jihyukim         ###   ########.fr       */
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
size_t	gnl_strchr(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*ft_strdup(const char *s1);
char	*gnl_strjoin(char *line, char *backup);

#endif
