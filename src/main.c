/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 15:07:15 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/06 15:07:17 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!ft_strcmp(av[1], "julia"))
			do_julia();
		else if (!ft_strcmp(av[1], "mand"))
			do_mand();
		else if (!ft_strcmp(av[1], "ship"))
			do_ship();
		else if (!ft_strcmp(av[1], "spider"))
			do_spider1();
		else
			ft_putstr("usage : ./fractol [mand, julia, spider, ship]\n");
	}
	else
		ft_putstr("usage : ./fractol [mand, julia, spider, ship]\n");
	return (0);
}
