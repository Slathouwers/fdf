/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_hooks2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 12:21:27 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/13 12:42:49 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	ctrl_update_state(t_fdf *fdf)
{
	t_ctrl	*c;

	c = &fdf->ctrl;
	c->v.z = 10 * (c->keyboard[KEY_W] - c->keyboard[KEY_S]);
	c->d_tilt = 1 * (c->keyboard[KEY_Q] - c->keyboard[KEY_E]);
	c->d_yaw = 1 * (c->keyboard[KEY_RIGHT] - c->keyboard[KEY_LEFT]);
	c->d_pitch = 1 * (c->keyboard[KEY_UP] - c->keyboard[KEY_DOWN]);
	c->status_prj = c->keyboard[KEY_P] - c->keyboard[KEY_I];
	c->d_zoom = c->keyboard[KEY_MINUS] - c->keyboard[KEY_PLUS];
	c->d_scroll = c->keyboard[KEY_HOME] - c->keyboard[KEY_END];
}

void	bind_keys(void *win, t_fdf *fdf)
{
	mlx_hook(win, MLX_EVENT_KEY_PRESS,
		MLX_EVENT_KEY_PRESS_MASK, ctrl_key_press, fdf);
	mlx_hook(win, MLX_EVENT_KEY_RELEASE,
		MLX_EVENT_KEY_RELEASE_MASK, ctrl_key_release, fdf);
	mlx_hook(win, MLX_EVENT_MOUSE_PRESS,
		MLX_EVENT_MOUSE_PRESS_MASK, ctrl_mouse_press, fdf);
	mlx_hook(win, MLX_EVENT_MOUSE_RELEASE,
		MLX_EVENT_MOUSE_RELEASE_MASK, ctrl_mouse_release, fdf);
	mlx_hook(win, MLX_EVENT_MOUSE_MOVE,
		MLX_EVENT_MOUSE_MOVE_MASK, ctrl_mouse_move, fdf);
	mlx_hook(win, MLX_EVENT_EXIT, MLX_EVENT_MOUSE_PRESS_MASK, &close_hook, fdf);
}
