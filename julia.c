/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/07 13:31:39 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/07 13:31:43 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int check_if_julia(t_complex c, int max_iter, t_complex z)
{
	float r;
	t_complex result;
	int i;

	r = (1.0 + sqrt(1 + 4 * c.abs))/2.0;
	i = 1;
	while (i <= max_iter) {
		result = comp_multiply(z, z);
		result = comp_sum(result, c);
		if (result.abs > r)
			return (i * 256);
		z = init_complex(result.re, result.im);
		i++;
	}
	return (0);
}

void draw_julia(t_julia julia)
{
	t_complex   z;
	int			colour;
	t_point2 dot;
	float inc;

	inc = 0.005;
	z.re = -2;
	dot.x = 0;
	while (dot.x < 800)
	{
		z.im = -2;
		dot.y = 0;
		while (dot.y < 800)
		{
			colour = (check_if_julia(julia.c, 100, z));
			julia.img_data[dot.x + (julia.line_size * dot.y)/4] = colour * 2;
			z.im += inc;
			dot.y++;
		}
		z.re += inc;
		dot.x++;
	}
	mlx_put_image_to_window(julia.mlx_ptr, julia.win_ptr, julia.img_ptr, 0,0);
}
