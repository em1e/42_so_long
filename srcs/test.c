/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vkettune <vkettune@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 13:37:32 by vkettune          #+#    #+#             */
/*   Updated: 2024/03/22 08:21:43 by vkettune         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int    error(char *msg)
{
    ft_putchar('E');
    printf("Error! %s\n", msg);
    return (1);
}

int	main(int argc, char *argv[])
{
    char    *msg;
    msg = argv[1];
    
    if (argc < 2)
        return (error("No map arguments given, use format: ./so_long [map]"));
    if (argc > 2)
        return (error("Too many arguments, use format: ./so_long [map]"));
    printf("hi %s\n", msg);
    write(1, "Hello, World!\n", 14);
    return (0);
}
