/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bilal_main.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-idri <bel-idri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/19 14:56:23 by bel-idri          #+#    #+#             */
/*   Updated: 2023/08/19 15:01:19 by bel-idri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BILAL_MAIN_H
# define BILAL_MAIN_H

# include "../get_next_line/get_next_line.h"
# include "../libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void	ft_error(char *msg, char *free_str1, char *free_str2);
void	ft_error_open(int fd);
char	*get_init_map(int fd);
void	free_map(char **map);
char	*ft_strjoin_free(char *s1, char *s2);
int		check_map(char **map);
int		check_init_map(char *map);
int		check_chars(char *map);
int		check_walls(char **map);
int		ft_strlen_height(char **map);
int		ft_strlen_width(char **map);
int		check_walls_utils(char **map, int i, int j);
int		check_chars_utils(char map);
int		check_newline(char *map);

#endif
