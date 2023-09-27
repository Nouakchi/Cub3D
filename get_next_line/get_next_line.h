/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 15:21:26 by bel-idri          #+#    #+#             */
/*   Updated: 2023/09/27 09:42:07 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*read_newline(int fd, char *my_backup);
char	*extract_newline(char **my_backup);
int		is_newline(char *s);
char	*gl_strjoin(char *s1, char *s2);
char	*gl_strdup(char *s1);
size_t	gl_strlen(char *s);
char	*extract_after_newline(char *my_backup);

#endif
