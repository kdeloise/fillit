/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgrandpa <tgrandpa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 14:22:40 by tgrandpa          #+#    #+#             */
/*   Updated: 2019/07/23 09:36:56 by tgrandpa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

void    ft_putchar(char c)
{
    write(1, &c, 1);
}

void    ft_putstr(char *str)
{
    while (*str)
        ft_putchar(*str++);
}

void    change(char s[2])
{
    int     i;

    i = -1;
    while (++i < 2)
        s[i] = '0' + i;
}

int     main(int argc, char **argv)
{
    char    s[4 + 1];
    int     i;

    i = -1;
    while (++i < 4)
        s[i] = 'a' + i;
    s[4] = 0;
    ft_putstr(s);
    change(s);
    ft_putchar(10);
    ft_putstr(s);
    return (0);
}