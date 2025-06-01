/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/01 15:58:09 by asaitakashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** handle_arrow_keys:
**   Moves the fractal view with arrow keys.
*/
static void	handle_arrow_keys(int keycode, t_fractal *f)
{
	double	move_amount;

	move_amount = 0.1 / f->zoom;
	if (keycode == LEFT)
		f->offset_x -= move_amount;
	else if (keycode == RIGHT)
		f->offset_x += move_amount;
	else if (keycode == UP)
		f->offset_y -= move_amount;
	else if (keycode == DOWN)
		f->offset_y += move_amount;
}

/*
** handle_key:
**   Handles key events (ESC, arrows, color shift).
*/
int	handle_key(int keycode, t_fractal *f)
{
	long	move_step;

	move_step = FIXED_DIVIDE(INT_TO_FIXED(1), f->zoom);
	if (keycode == ESC)
		close_window(f);
	else if (keycode == LEFT)
		f->offset_x -= move_step;
	else if (keycode == RIGHT)
		f->offset_x += move_step;
	else if (keycode == UP)
		f->offset_y -= move_step;
	else if (keycode == DOWN)
		f->offset_y += move_step;
	else if (keycode == 'r')
		shift_colors(f);
	render_fractal(f);
	return (0);
}

/*
** handle_zoom:
**   Zooms in/out centered on mouse position.
*/
static void	apply_zoom(t_fractal *f, int x, int y, int zoom_in)
{
	long	zoom_factor;
	long	mouse_x;
	long	mouse_y;

	mouse_x = INT_TO_FIXED(x - WIDTH / 2);
	mouse_y = INT_TO_FIXED(y - HEIGHT / 2);
	zoom_factor = zoom_in ? INT_TO_FIXED(2) : INT_TO_FIXED(1) / 2;
	f->zoom = FIXED_MULTIPLY(f->zoom, zoom_factor);
	f->offset_x = FIXED_MULTIPLY(f->offset_x, zoom_factor) - mouse_x;
	f->offset_y = FIXED_MULTIPLY(f->offset_y, zoom_factor) - mouse_y;
}

/*
** handle_mouse:
**   Handles mouse wheel zoom events.
*/
int	handle_mouse(int button, int x, int y, t_fractal *f)
{
	if (button == ZOOM_IN || button == ZOOM_OUT)
	{
		apply_zoom(f, x, y, button == ZOOM_IN);
		render_fractal(f);
	}
	return (0);
}

/*
** handle_mouse_move:
**   Updates Julia set parameters on mouse move.
*/
int	handle_mouse_move(int x, int y, t_fractal *f)
{
	if (f->fractal_type == 2)
	{
		f->julia_c.re = FIXED_DIVIDE(INT_TO_FIXED(x - WIDTH / 2),
				INT_TO_FIXED(WIDTH / 4));
		f->julia_c.im = FIXED_DIVIDE(INT_TO_FIXED(y - HEIGHT / 2),
				INT_TO_FIXED(HEIGHT / 4));
		render_fractal(f);
	}
	return (0);
}

/*
** close_window:
**   Cleans up and exits the program.
*/
int	close_window(t_fractal *f)
{
	mlx_destroy_image(f->mlx, f->img);
	mlx_destroy_window(f->mlx, f->win);
	mlx_destroy_display(f->mlx);
	free(f->mlx);
	exit(0);
	return (0);
}

void	shift_colors(t_fractal *f)
{
	f->color_shift = (f->color_shift + 10) % 256;
}
