/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppepperm <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/06 13:53:39 by ppepperm          #+#    #+#             */
/*   Updated: 2020/01/06 13:53:41 by ppepperm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "fractol.h"

t_complex init_complex(float re, float im)
{
	t_complex z;

	z.re = re;
	z.im = im;
	z.abs = sqrt(re * re + im * im);
	z.phase = atan2(im, re);
	return z;
}

t_complex comp_sum(t_complex z1, t_complex z2)
{
	return (init_complex(z1.re + z2.re, z1.im + z2.im));
}

t_complex comp_dif(t_complex z1, t_complex z2)
{
	return (init_complex(z1.re - z2.re, z1.im - z2.im));
}

t_complex comp_multiply(t_complex z1, t_complex z2)
{
	return (init_complex(z1.re*z2.re - z1.im*z2.im, z1.im*z2.re + z1.re * z2.im));
}

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
