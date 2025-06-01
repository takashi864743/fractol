/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/01 15:58:03 by asaitakashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static long	get_escape_value(t_complex z)
{
	return (FIXED_MULTIPLY(z.re, z.re) + FIXED_MULTIPLY(z.im, z.im));
}

static void	put_color(t_fractal *f, int iter, int x, int y)
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
	long		escape;

	z.re = 0;
	z.im = 0;
	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > INT_TO_FIXED(4))
			return (i);
		z.re = FIXED_MULTIPLY(z.re, z.re) - FIXED_MULTIPLY(z.im, z.im) + c.re;
		z.im = FIXED_MULTIPLY(INT_TO_FIXED(2), FIXED_MULTIPLY(z.re, z.im)) + c.im;
		i++;
	}
	return (max_iter);
}

int	julia(t_complex z, t_complex c, int max_iter)
{
	int			i;
	long		escape;

	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > INT_TO_FIXED(4))
			return (i);
		z.re = FIXED_MULTIPLY(z.re, z.re) - FIXED_MULTIPLY(z.im, z.im) + c.re;
		z.im = FIXED_MULTIPLY(INT_TO_FIXED(2), FIXED_MULTIPLY(z.re, z.im)) + c.im;
		i++;
	}
	return (max_iter);
}

int	burning_ship(t_complex c, int max_iter)
{
	t_complex	z;
	int			i;
	long		escape;

	z.re = 0;
	z.im = 0;
	i = 0;
	while (i < max_iter)
	{
		escape = get_escape_value(z);
		if (escape > INT_TO_FIXED(4))
			return (i);
		z.re = FIXED_MULTIPLY(z.re, z.re) - FIXED_MULTIPLY(z.im, z.im) + c.re;
		z.im = FIXED_MULTIPLY(INT_TO_FIXED(2), FIXED_MULTIPLY(z.re, z.im)) + c.im;
		if (z.im < 0)
			z.im = -z.im;
		if (z.re < 0)
			z.re = -z.re;
		i++;
	}
	return (max_iter);
}

static void	render_pixel(t_fractal *f, t_complex c, int x, int y)
{
	int	iter;

	if (f->fractal_type == 1)
		iter = mandelbrot(c, f->max_iter);
	else if (f->fractal_type == 2)
		iter = julia(c, f->julia_c, f->max_iter);
	else
		iter = burning_ship(c, f->max_iter);
	put_color(f, iter, x, y);
}

void	render_fractal(t_fractal *f)
{
	int			x;
	int			y;
	t_complex	c;
	long		scale;

	scale = FIXED_DIVIDE(INT_TO_FIXED(4),
			FIXED_MULTIPLY(f->zoom, INT_TO_FIXED(WIDTH)));
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c.re = FIXED_MULTIPLY(INT_TO_FIXED(x - WIDTH / 2), scale) + f->offset_x;
			c.im = FIXED_MULTIPLY(INT_TO_FIXED(y - HEIGHT / 2), scale) + f->offset_y;
			render_pixel(f, c, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
}

void	init_fractal(t_fractal *f, int type)
{
	f->mlx = mlx_init();
	if (!f->mlx)
		exit(1);
	f->win = mlx_new_window(f->mlx, WIDTH, HEIGHT, "Fractol");
	if (!f->win)
		exit(1);
	f->img = mlx_new_image(f->mlx, WIDTH, HEIGHT);
	if (!f->img)
		exit(1);
	f->addr = mlx_get_data_addr(f->img, &f->bits_per_pixel,
			&f->line_length, &f->endian);
	f->zoom = INT_TO_FIXED(1);
	f->offset_x = 0;
	f->offset_y = 0;
	f->max_iter = MAX_ITER;
	f->color_shift = 0;
	f->fractal_type = type;
	f->julia_c.re = INT_TO_FIXED(-4) / 10;
	f->julia_c.im = INT_TO_FIXED(4) / 10;
	f->mouse_x = WIDTH / 2;
	f->mouse_y = HEIGHT / 2;
}
