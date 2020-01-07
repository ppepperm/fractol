/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 16:02:41 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/07 16:02:44 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int check_if_mand(t_complex c, int max_iter)
{
	t_complex z;
	t_complex result;
	int i;

	z = init_complex(0, 0);
	i = 0;
	while (i < max_iter)
	{
		result = comp_multiply(z, z);
		result = comp_sum(result, c);
		if (result.abs > 2)
			return (i + 255* 256 * 256);
		z = init_complex(result.re, result.im);
		i++;
	}
	return (0);
}

void draw_mandelbrot(t_mandelbrot mandelbrot)
{
	t_complex   z;
	int			colour;

	z.re = -2;
	while (z.re <= 2)
	{
		z.im = -2;
		while (z.im <= 2)
		{
			colour = (check_if_mand(z, 200));
			mlx_pixel_put(mand.mlx_ptr, mand.win_ptr, z.re * 250 + 500, z.im * 250 + 500, colour * 20);
			z.im += 0.001;
		}
		z.re += 0.001;
	}
}