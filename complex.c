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