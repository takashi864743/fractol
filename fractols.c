/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/05 15:28:10 by asaitakashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static double	get_escape_value(t_complex z)
{
	return (z.re * z.re + z.im * z.im);
}

static void	put_color(t_fractol *f, int iter, int x, int y)
{
	int	color;
	int	r;
	int	g;
	int	b;

	if (iter == f->max_iter)
		color = 0x000000;
	else
	{
		r = iter * 5 + f->color_shift;
		g = iter * 7 + f->color_shift;
		b = iter * 11 + f->color_shift;
		color = create_rgb(r, g, b);
	}
	put_pixel(f, x, y, color);
}

int	mandelbrot(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;
	double		escape;
	double		temp;

	z.re = 0.0;
	z.im = 0.0;
	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > 4.0)
			return (i);
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = temp;
		i++;
	}
	return (max_iter);
}

int	julia(t_complex z, t_complex c, int max_iter)
{
	int			i;
	double		escape;
	double		temp;

	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > 4.0)
			return (i);
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * z.re * z.im + c.im;
		z.re = temp;
		i++;
	}
	return (max_iter);
}

int	burning_ship(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;
	double		escape;
	double		temp;

	z.re = 0.0;
	z.im = 0.0;
	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > 4.0)
			return (i);
		temp = z.re * z.re - z.im * z.im + c.re;
		z.im = 2.0 * fabs(z.re) * fabs(z.im) + c.im;
		z.re = temp;
		if (z.im < 0)
			z.im = -z.im;
		if (z.re < 0)
			z.re = -z.re;
		i++;
	}
	return (max_iter);
}

static void	render_pixel(t_fractol *f, t_complex c, int x, int y)
{
	int	iter;

	if (f->fractol_type == 1)
		iter = mandelbrot(c, f->max_iter);
	else if (f->fractol_type == 2)
		iter = julia(c, f->julia_c, f->max_iter);
	else
		iter = burning_ship(c, f->max_iter);
	put_color(f, iter, x, y);
}

void	render_fractol(t_fractol *f)
{
	int			x;
	int			y;
	t_complex	c;
	double		scale;

	scale = 4.0 / (f->zoom * WIDTH);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c.re = (x - WIDTH / 2) * scale + f->offset_x;
			c.im = (y - HEIGHT / 2) * scale + f->offset_y;
			render_pixel(f, c, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}
