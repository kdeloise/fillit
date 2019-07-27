/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrandpa <tgrandpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 13:31:28 by tgrandpa          #+#    #+#             */
/*   Updated: 2019/07/25 09:23:18 by tgrandpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void	init_tetr_content(char content[6][7])
{
	int		i;
	int		j;

	i = -1;
	while (++i < 6)
	{
		j = -1;
		while (++j < 6)
			content[i][j] = '.';
		content[i][j] = 0;
	}
}

int		checkline(char *line)
{
	int		i;

	i = -1;
	while (++i < 4)
		if (line[i] != '.' && line[i] != '#')
			return (0);
	return (1);
}

int		is_correct_tetr(char tetr_check[6][7])
{
	int		i;
	int		j;
	int		counter;

	i = -1;
	counter = 0;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			if (tetr_check[i + 1][j + 1] == '#')
			{
				if (tetr_check[i][j + 1] == '#')
					counter++;
				if (tetr_check[i + 2][j + 1] == '#')
					counter++;
				if (tetr_check[i + 1][j] == '#')
					counter++;
				if (tetr_check[i + 1][j + 2] == '#')
					counter++;
			}
	}
	if (counter == 6 || counter == 8)
		return (1);
	return (0);
}

int		check_file(int fd)
{
	int		ret;
	int		i;
	char	tetr[6][7];
	char	c;

	i = 0;
	c = 10;
	init_tetr_content(tetr);
	while ((ret = read(fd, tetr[++i] + 1, 4)))
	{
		if (!(ret == 4 && read(fd, &c, 1) && c == 10 && checkline(tetr[i] + 1)))
			return (0);
		c = '.';
		if (i == 4 && is_correct_tetr(tetr))
		{
			read(fd, &c, 1);
			i = 0;
		}
	}
	if (i != 1 || c == 10)
		return (0);
	return (1);
}
