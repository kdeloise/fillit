/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrandpa <tgrandpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 10:12:37 by tgrandpa          #+#    #+#             */
/*   Updated: 2019/07/25 09:20:32 by tgrandpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

void			find_min_pos(int min_pos[4][2])
{
	int		i;
	int		j;
	int		min;

	j = -1;
	while (++j < 2)
	{
		min = min_pos[0][j];
		i = -1;
		while (++i < 4)
			if (min > min_pos[i][j])
				min = min_pos[i][j];
		i = -1;
		while (++i < 4)
			min_pos[i][j] -= min;
	}
}

void			find_tetr_pos(t_tetrimino *tetr)
{
	int			i;
	int			j;
	static int	name_i = 0;
	int			counter;

	i = -1;
	counter = 0;
	tetr->name = 'A' + name_i++;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (tetr->content[i][j] == '#')
			{
				tetr->content[i][j] = tetr->name;
				tetr->min_pos[counter][0] = i;
				tetr->min_pos[counter++][1] = j;
			}
	}
	// show_min_pos(tetr->min_pos);
	// ft_putchar(10);
	find_min_pos(tetr->min_pos);
}

t_tetrimino		*read_tetriminos(int fd, t_tetrimino *tetr)
{
	t_tetrimino		*tetr_first;
	int				i;
	char			c;

	i = -1;
	tetr = (t_tetrimino*)malloc(sizeof(t_tetrimino));
	tetr_first = tetr;
	if (tetr)
		while (read(fd, tetr->content[++i], 5))
		{
			tetr->content[i][4] = 0;
			if (i == 3)
			{
				i = -1;
				find_tetr_pos(tetr);
				if (read(fd, &c, 1))
				{
					tetr->next = (t_tetrimino*)malloc(sizeof(t_tetrimino));
					tetr = tetr->next;
				}
				else
					tetr->next = NULL;
			}
		}
	return (tetr_first);
}
