/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrandpa <tgrandpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:42:24 by tgrandpa          #+#    #+#             */
/*   Updated: 2019/07/27 16:24:12 by tgrandpa         ###   ########.fr       */
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

int		tetr_positions(char **minsqr, t_tetrimino *tetr, int i, int j)
{
	int		n;
	int		m;
	int		l;
	int		k;
	
	// move_tetr(tetr);
	m = -1;
	n = 0;
	l = 0;
	while (l != 2)
	{
		l = 0;
		m++;
		//CHECK FOR EMPTY PLACE TO PUT TETRIMINO
		k = -1;
		while (++k < 4)
			if (minsqr[tetr->min_pos[k][0] + n + i][tetr->min_pos[k][1] + m + j] != '.')
				break ;
		if (k == 4)
		{
			k = -1;
			while (++k < 4)
				minsqr[tetr->min_pos[k][0] + n + i][tetr->min_pos[k][1] + m + j] = tetr->name;
			break ;
		}
		//MOVE TETRIMINO TO NEXT POSITION
		move_next_pos(tetr, &l, &n, &m);
	}
	printf("l = %d\n", l);
	if (l == 0)
		return (1);
	return (0);
}

int		check_first_line(t_minsqr *minsqr, t_tetrimino *tetr, int i)
{
	int		q;
	int		m;
	int		k;
	int		l;
	int		i1;

	i1 = i;
	while (i1 < i + 4)
	{
		printf("TEST2\n");
		q = -1;
		m = -1;
		// printf("iii = %d, iii1 = %d\n", i, i1);
		// show_content(tetr->content);
		// show_min_pos(tetr->min_pos);
		while (++q < minsqr->length)
			if (minsqr->content[i1][q] == '.')
				break ;
		// printf("iq = %d\n", q);
		if (q >= 4)
			q = q - 3;
		else
			q = 0;
		// printf("iq2 = %d\n", q);		
		while (q + 3 < minsqr->length)
		{
			if (minsqr->content[i1][q + 3] == '.')
			{
				k = -1;
				m++;
				l = 0;
				while (++k < 4)
					if (minsqr->content[tetr->min_pos[k][0] + i][tetr->min_pos[k][1] + q + m] != '.')
					break ;
				// printf("k = %d\n", k);
				if (k == 4)
				{
					k = -1;
					l = 1;
					while (++k < 4)
						minsqr->content[tetr->min_pos[k][0] + i][tetr->min_pos[k][1] + q + m] = tetr->name;
					return (1);
				}
				k = -1;
				while (++k < 4)
					if ((tetr->min_pos[k][1] + m) == 3)
						break ;
				// printf("q = %d\n", q);
				if (k != 4)
				{
					m = -1;
					q++;
				}
			}
			else
				q++;
		}
		i1++;
	}
	return (0);
}

int		movesqr4x4(t_minsqr *minsqr, t_tetrimino *tetr)
{
	int		i;
	int		j;
	int		l;
	int		i1;

	i = -1;
	show_min_pos(tetr->min_pos);
	while (++i < minsqr->length - 3)
	{
		
		l = 0;
		j = -1;
		i1 = i;
		while (i1 < (minsqr->length -  3))
		{
			printf("TEST\n");
			if (check_first_line(minsqr, tetr, i1++))
			{
				printf("FIRST\n");
				show_min_sqr(minsqr);
				l = 1;
				break ;
			}
		}
		if (l == 1)
			break ;
		l = 0;
		while (++j < minsqr->length - 3)
		{
			if (tetr_positions(minsqr->content, tetr, i, j))
			{
				printf("TPOSITION\n");
				show_min_sqr(minsqr);
				l = 1;
				break ;
			}
		}
		if (l == 1)
			break ;
	}
	return (1);
}

void	solution(t_tetrimino *tetr, char *filename)
{
	t_minsqr	minsqr;
	int			fd;
	int			i;
	char		c;

	i = -1;
	minsqr = min_sqr_init(tetr);
	// fd = open(filename, O_RDONLY);
	// while (++i < minsqr.length)
	// {
	// 	read(fd, minsqr.content[i], minsqr.length);
	// 	read(fd, &c, 1);
	// }
	// show_min_sqr(&minsqr);
	// close(fd);
	i = -1;
	/* while (tetr)
	{
		check_first_line(&minsqr, tetr, 0);
		// show_min_sqr(&minsqr);
		tetr = tetr->next;		
	} */
	while (tetr)
	{
		movesqr4x4(&minsqr, tetr);
		tetr = tetr->next;
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
			/* while (tetr)
			{
				move_tetr(tetr);
				tetr = tetr->next;
			} */
			close(fd);
			solution(tetr, argv[2]);
			// while (*minsqr)
			// {
			// 	while (**minsqr)
			// 		ft_putchar(*((*minsqr)++));
			// 	ft_putchar(10);
			// 	minsqr++;
			// }
		}
		else
			ft_putstr("error\n");
	}
	else
		ft_putstr("usage: ./fillit source file\n");
	return (0);
}