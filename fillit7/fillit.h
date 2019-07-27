/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrandpa <tgrandpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:42:28 by tgrandpa          #+#    #+#             */
/*   Updated: 2019/07/25 16:13:19 by tgrandpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct			s_tetrimino
{
	char				content[4][5];
	int 				min_pos[4][2];
	char 				name;
	struct s_tetrimino	*next;
}						t_tetrimino;
// general functions
void			show_content(char content[4][5]);
void			show_min_pos(int min_pos[4][2]);
// validation.c
void			init_tetr_content(char content[6][7]);
int				checkline(char *line);
int				is_correct_tetr(char tetr_check[6][7]);
int				check_file(int fd);
// read.c
void			find_min_pos(int min_pos[4][2]);
void			find_tetr_pos(t_tetrimino *tetr);
t_tetrimino		*read_tetriminos(int fd, t_tetrimino *tetr);

#endif

//exit, open, close, write, read, malloc and free.