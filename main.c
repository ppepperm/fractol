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

#include "fractol.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (!ft_strcmp(av[1], "Julia"))
			do_julia();
		else if (!ft_strcmp(av[1], "Mand"))
			do_mand();
		else if (!ft_strcmp(av[1], "Ship"))
			do_ship();
		else
			ft_putstr("Wrong fractal name.\nPossible ones: Julia - Julia, Mandelbrot - Mand, Burning ship - Ship\n");
	}
	else
		ft_putstr("Please specify fractal.\nPossible ones: Julia - Julia, Mandelbrot - Mand,  Burning ship - Ship\n");
	return (0);
}
