/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrandpa <tgrandpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:42:24 by tgrandpa          #+#    #+#             */
/*   Updated: 2019/07/30 17:56:38 by tgrandpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include "libft/libft.h"

void	show_content(char content[4][5])
{
	int 	i = -1;

	while (++i < 4)
	{
		ft_putstr(content[i]);
		ft_putchar(10);
	}
	ft_putchar(10);
}

void	show_min_pos(int min_pos[4][2])
{
	int 	i;
	int		j;

	i = -1;
	while (++i < 4)
	{
		printf("%d ", min_pos[i][0]);
		printf("%d\n", min_pos[i][1]);
	}
	ft_putchar(10);
}

void	show_all(t_tetrimino *tetr)
{
	while (tetr)
	{
		show_content(tetr->content);
		show_min_pos(tetr->min_pos);
		tetr = tetr->next;
	}
}

void 	fill_sqr_dots(char **minsqr, int length)
{
	int i;
	int j;

	i = -1;
	j = -1;
	while (++i < length)
	{
		j = -1;
		while (++j < length)
			minsqr[i][j] = '.';
		minsqr[i][length] = 0;
	}
	minsqr[i] = NULL;
}

t_minsqr	min_sqr_init(t_tetrimino *tetr)
{
	t_minsqr	minsqr;
	int			counter;

	counter = 0;
	minsqr.length = 0;
	while (tetr)
	{
		tetr = tetr->next;
		counter++;
	}
	printf("counter = %d\n", counter);
	counter *= 4;
	while (minsqr.length * minsqr.length < counter)
		minsqr.length++;
	printf("length = %d\n", minsqr.length);
	counter = -1;
	minsqr.content = (char**)malloc(sizeof(char*) * minsqr.length + 1);
	if (minsqr.content)
		while (++counter < minsqr.length)
			minsqr.content[counter] = (char*)malloc(sizeof(char) * minsqr.length + 1);
	fill_sqr_dots(minsqr.content, minsqr.length);
	return (minsqr);
}

void	clean_min_sqr(char **minsqr)
{
	int		i;
	int 	j;

	i = -1;
	j = -1;

	while (++i < 6)
	{
		j = -1;
		while (++j < 6)
			minsqr[i][j] = 'b';
	}
}

void	show_min_sqr(t_minsqr *minsqr)
{
	int		i;
	int 	j;

	i = -1;
	j = -1;

	while (++i < minsqr->length)
	{
		j = -1;
		while (++j < minsqr->length)
			ft_putchar(minsqr->content[i][j]);
		ft_putchar(10); 
	}
	ft_putchar(10);
}


void	solution(t_tetrimino *tetr)
{
	while (tetr)
	{
		show_content(tetr->content);
		if (!tetr->next)
			break ;
		tetr = tetr->next;
	}
	ft_putstr("------------------------------------\n");
	while (tetr)
	{
		show_content(tetr->content);
		tetr = tetr->prev;
	}
	
}

int 	main(int argc, char **argv)
{
	int 			fd;
	t_tetrimino		*tetr;
	t_tetrimino 	*test;
	char			**minsqr;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		if (check_file(fd))
		{
			ft_putstr("correct file\n");
			close(fd);
			fd = open(argv[1], O_RDONLY);
			tetr = read_tetriminos(fd, tetr);
			// show_all(tetr);
			solution(tetr);
			/* while (tetr)
			{
				move_tetr(tetr);
				tetr = tetr->next;
			} */
			close(fd);
		}
		else
			ft_putstr("error\n");
	}
	else
		ft_putstr("usage: ./fillit source file\n");
	return (0);
}