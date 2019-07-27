/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrandpa <tgrandpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:42:24 by tgrandpa          #+#    #+#             */
/*   Updated: 2019/07/26 09:59:29 by tgrandpa         ###   ########.fr       */
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

void	clean_tetr(char content[4][5])
{
	int 	i;
	int 	j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			content[i][j] = '.';
	}
}

void	move_tetr(t_tetrimino *tetr)
{
	int		i;
	int		l;
	int		m;
	int		n;

	m = -1;
	n = 0;
	l = 0;
	clean_tetr(tetr->content);
	while (l != 2)
	{
		i = -1;
		l = 0;
		m++;
		while (++i < 4)
			tetr->content[tetr->min_pos[i][0] + n][tetr->min_pos[i][1] + m] = tetr->name;
		show_content(tetr->content);
		clean_tetr(tetr->content);
		i = -1;
		while (++i < 4)
			if ((tetr->min_pos[i][1] + m) == 3)
				l = 1;
		i = -1;
		if (l == 1)
		{
			while (++i < 4)
				if (tetr->min_pos[i][0] + n == 3)
					l = 2;
			n++;
			m = -1;
		}
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

char	**min_sqr_init(t_tetrimino *tetr)
{
	char	**minsqr;
	int		length;
	int		counter;

	counter = 0;
	length = 0;
	while (tetr)
	{
		tetr = tetr->next;
		counter++;
	}
	counter *= 4;
	while (length * length < counter)
		length++;
	printf("length = %d\n", length);
	counter = -1;
	minsqr = (char**)malloc(sizeof(char*) * length + 1);
	if (minsqr)
		while (++counter < length)
			minsqr[counter] = (char*)malloc(sizeof(char) * length + 1);
	fill_sqr_dots(minsqr, length);
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

void	show_min_sqr(char **minsqr)
{
	int		i;
	int 	j;

	i = -1;
	j = -1;

	while (++i < 6)
	{
		j = -1;
		while (++j < 6)
			ft_putchar(minsqr[i][j]);
		ft_putchar(10); 
	}
	ft_putchar(10);
}

//PUT TETRIMINO TO EMPTY PLACE
int		put_tetr(char	**minsqr, t_tetrimino *tetr, int n, int m)
{
	int		i;

	i = -1;
	while (++i < 4)
		if (minsqr[tetr->min_pos[i][0] + n][tetr->min_pos[i][1] + m] != '.')
			break ;
	if (i == 4)
	{
		i = -1;
		while (++i < 4)
			minsqr[tetr->min_pos[i][0] + n][tetr->min_pos[i][1] + m] = tetr->name;
		return (1);
	}
	return (0);
}

//MOVE TETRIMINO TO NEXT POSITION
void	move_next_pos(t_tetrimino *tetr, int *l, int *n, int *m)
{
	int		i;
	
	i = -1;
	while (++i < 4)
		if ((tetr->min_pos[i][1] + *m) == 3)
			*l = 1;
	i = -1;
	if (*l == 1)
	{
		while (++i < 4)
			if (tetr->min_pos[i][0] + *n == 3)
				*l = 2;
		(*n)++;
		*m = -1;
	}
}

void	move_tetr(char **minsqr, t_tetrimino *tetr)
{
	int		n;
	int		m;
	int		i;
	int		l;

	minsqr[0][0] = 'A';
	minsqr[0][1] = 'A';
	minsqr[0][2] = 'A';
	minsqr[1][2] = 'A';
	show_min_sqr(minsqr);
	move_tetr(tetr);
	m = -1;
	n = 0;
	l = 0;
	while (l != 2)
	{
		i = -1;
		l = 0;
		m++;
		//CHECK FOR EMPTY PLACE TO PUT TETRIMINO
		if (put_tetr(minsqr, tetr, n, m))
			break ;
		//MOVE TETRIMINO TO NEXT POSITION
		move_next_pos(tetr, &l, &n, &m);
	}
	show_min_sqr(minsqr);
}

/* void	put_tetr_gen(char **minsqr, t_tetrimino *tetr)
{
	int		i;
	int		j;
	int		counter;

	i = -1;
	while (++i < 6 - 4 + 1)
	{
		j = -1;
		counter = 0;
		while (++j < 6)
			if (minsqr[i][j] == '.')
				counter++;
		j = -1;
		if (counter)
		{
			// while (++j < 6)
			// 	if (minsqr[i][j] == '.')

		}
		else
		{
			
		}
	}
} */

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
			/* while (tetr)
			{
				move_tetr(tetr);
				tetr = tetr->next;
			} */
			minsqr = min_sqr_init(tetr);
			move_sqr4x4(minsqr, tetr->next);
			// while (*minsqr)
			// {
			// 	while (**minsqr)
			// 		ft_putchar(*((*minsqr)++));
			// 	ft_putchar(10);
			// 	minsqr++;
			// }
			close(fd);
		}
		else
			ft_putstr("error\n");
	}
	else
		ft_putstr("usage: ./fillit source file\n");
	return (0);
}