/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:40:09 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 12:51:28 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ctrl_mouse_press(int button, int x, int y, t_fdf *fdf)
{
	t_ctrl	*c;

	c = &fdf->ctrl;
	c->mouse.buttons[button] = 1;
	c->mouse.click_pos[button] = (t_point2d){x, y};
	return (0);
}

int	ctrl_mouse_release(int button, int x, int y, t_fdf *fdf)
{
	t_ctrl	*c;

	c = &fdf->ctrl;
	c->mouse.buttons[button] = 0;
	c->mouse.release_pos[button] = (t_point2d){x, y};
	return (0);
}

int	ctrl_mouse_move(int x, int y, t_fdf *fdf)
{
	t_ctrl	*c;

	c = &fdf->ctrl;
	c->mouse.pos = (t_point2d){x, y};
	return (0);
}

int	ctrl_key_press(int keycode, t_fdf *fdf)
{
	t_ctrl	*c;

	c = &fdf->ctrl;
	if (keycode == KEY_ESC)
		close_hook(fdf);
	c->keyboard[keycode] = 1;
	ctrl_update_state(fdf);
	return (0);
}

int	ctrl_key_release(int keycode, t_fdf *fdf)
{
	t_ctrl	*c;

	c = &fdf->ctrl;
	c->keyboard[keycode] = 0;
	ctrl_update_state(fdf);
	return (0);
}
