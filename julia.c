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
			return ((i + 20) * 256 + 50);
		z = init_complex(result.re, result.im);
		i++;
	}
	return (0);
}

void draw_julia(t_julia julia)
{
	/*t_complex   z;
	int			colour;
	t_point2 dot;
	float inc;
	int count_zer  = 0;

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
			julia.img_data[dot.x + (julia.line_size * dot.y)/4] = colour;
			if (colour == 0)
				count_zer++;
			z.im += inc;
			dot.y++;
		}
		z.re += inc;
		dot.x++;
	}*/
	get_julia_image(julia, (int*)julia.img_data);
	//printf("%d\n",count_zer);
	mlx_put_image_to_window(julia.mlx_ptr, julia.win_ptr, julia.img_ptr, 0,0);
}
