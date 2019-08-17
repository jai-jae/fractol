/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaelee <jaelee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/17 12:47:58 by jaelee            #+#    #+#             */
/*   Updated: 2019/08/17 13:50:49 by jaelee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		burningshit_set(t_complex *c)
{
	t_complex	z;
	t_complex	z2;
	int		iter;

	z.real = c->real;
	z.img = c->img;
	z2.real = z.real *z.real;
	z2.img = z.img * z.img;
	iter = -1;
	while (++iter < MAX_ITER && (z2.real + z2.img < 4))
	{
		z.img = fabs(2.0 * z.real * z.img) + c->img;
		z.real = fabs(z2.real - z2.img + c->real);
		z2.real = z.real * z.real;
		z2.img = z.img * z.img;
	}
	return (iter);
}

void	burningshit_draw(t_fractal *fr)
{
	int			color;
	int			x;
	int			y;
	t_complex	c;

	y = -1;
	fr->x_scale = (fr->real_max - fr->real_min) / (double)WIN_WIDTH;
	fr->y_scale = (fr->img_max - fr->img_min) / (double)WIN_HEIGHT;
	reset_buffer(fr->buffer);
	c.img = fr->img_min;
	while (++y < WIN_HEIGHT)
	{
		x = -1;
		c.real = fr->real_min;
		while (++x < WIN_WIDTH)
		{
			color = pick_color(burningshit_set(&c));
			pixel_in_buffer((unsigned char*)fr->buffer, x, y, color);
			c.real += fr->x_scale;
		}
		c.img += fr->y_scale;
	}
	mlx_put_image_to_window(fr->mlx_ptr, fr->win_ptr, fr->img_ptr, 0, 0);
}
