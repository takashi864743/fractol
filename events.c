/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaitakashi <asaitakashi@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 12:00:00 by asaitakashi       #+#    #+#             */
/*   Updated: 2025/06/05 15:45:09 by asaitakashi      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** handle_key:
**   Handles key events (ESC, arrows, color shift).
*/
int	handle_key(int keycode, t_fractol *f)
{
	double	move_step;

	move_step = 1.0 / f->zoom;
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
	else if (keycode == 'c' || keycode == 'C')
		shift_colors(f);
	else if (keycode == 'r' || keycode == 'R')
	{
		f->zoom = 1.0;
		f->offset_x = 0.0;
		f->offset_y = 0.0;
		f->color_shift = 0;
	}
	render_fractol(f);
	return (0);
}

/*
** handle_mouse:
**   Handles mouse wheel zoom events.
*/
int	handle_mouse(int button, int x, int y, t_fractol *f)
{
	double	zoom_factor;
	double	mouse_x;
	double	mouse_y;

	zoom_factor = 1.5;
	mouse_x = (x - WIDTH / 2.0) * (4.0 / (f->zoom * WIDTH)) + f->offset_x;
	mouse_y = (y - HEIGHT / 2.0) * (4.0 / (f->zoom * HEIGHT)) + f->offset_y;
	if (button == ZOOM_IN)
	{
		f->zoom *= zoom_factor;
		f->offset_x = f->offset_x * zoom_factor - mouse_x;
		f->offset_y = f->offset_y * zoom_factor - mouse_y;
	}
	else if (button == ZOOM_OUT)
	{
		f->zoom /= zoom_factor;
		f->offset_x = f->offset_x / zoom_factor + mouse_x;
		f->offset_y = f->offset_y / zoom_factor + mouse_y;
	}
	render_fractol(f);
	return (0);
}

/*
** handle_mouse_move:
**   Updates Julia set parameters on mouse move.
*/
int	handle_mouse_move(int x, int y, t_fractol *f)
{
	if (f->fractol_type == 2)
	{
		f->julia_c.re = (x - WIDTH / 2.0) / (WIDTH / 4.0);
		f->julia_c.im = (y - HEIGHT / 2.0) / (HEIGHT / 4.0);
		render_fractol(f);
	}
	f->mouse_x = x;
	f->mouse_y = y;
	return (0);
}

/*
** close_window:
**   Cleans up and exits the program.
*/
int	close_window(t_fractol *f)
{
	if (f->img)
		mlx_destroy_image(f->mlx, f->img);
	if (f->win)
		mlx_destroy_window(f->mlx, f->win);
	if (f->mlx)
	{
		mlx_destroy_display(f->mlx);
		free(f->mlx);
	}
	exit(0);
}

void	shift_colors(t_fractol *f)
{
	f->color_shift += 10;
	if (f->color_shift > 255)
		f->color_shift = 0;
	render_fractol(f);
}
