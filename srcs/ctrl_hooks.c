/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl_hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slathouw <slathouw@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:40:09 by slathouw          #+#    #+#             */
/*   Updated: 2021/12/10 09:22:24 by slathouw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static void		ctrl_update_state(t_ctrl *c)
{
	c->v.z = 10 * (c->keyboard[KEY_W] - c->keyboard[KEY_S]);
	c->d_tilt = 1 * (c->keyboard[KEY_Q] - c->keyboard[KEY_E]);
//	c->d_yaw = 1 * (c->keyboard[KEY_RIGHT] - c->keyboard[KEY_LEFT]);
//	c->d_pitch = 1 * (c->keyboard[KEY_UP] - c->keyboard[KEY_DOWN]);
	c->status_prj = c->keyboard[KEY_P] - c->keyboard[KEY_I];
	c->d_zoom = c->keyboard[KEY_MINUS] - c->keyboard[KEY_PLUS];
	c->d_scroll = c->keyboard[KEY_HOME] - c->keyboard[KEY_END];
}

static int	ctrl_mouse_press(int button, int x, int y, t_ctrl *c)
{
	c->mouse.buttons[button] = 1;
	c->mouse.click_pos[button] = (t_point2d){x, y};
	return (0);
}

static int	ctrl_mouse_release(int button, int x, int y, t_ctrl *c)
{
	c->mouse.buttons[button] = 0;
	c->mouse.release_pos[button] = (t_point2d){x, y};
	return (0);
}

static int	ctrl_mouse_move(int x, int y, t_ctrl *c)
{
	c->mouse.pos = (t_point2d){x, y};
	return (0);
}

static int	ctrl_key_press(int keycode, void *p)
{
	ft_printf("key pressed = %i\n", keycode);
	t_ctrl *c;

	c = p;
	if (keycode == KEY_ESC)
		exit(0);
	/*c->keyboard[keycode] = 1;*/
	ctrl_update_state(c);
	return (0);
}

static int	ctrl_key_release(int keycode, void *p)
{
	ft_printf("key released = %i\n", keycode);

	t_ctrl *c;

	c = p;
	/*c->keyboard[keycode] = 0;*/
	ctrl_update_state(c);
	return (0);
}

void	bind_keys(void *win, t_ctrl *c, t_fdf *fdf)
{
	mlx_hook(win, MLX_EVENT_KEY_PRESS, MLX_EVENT_KEY_PRESS_MASK, ctrl_key_press, c);
	mlx_hook(win, MLX_EVENT_KEY_RELEASE, MLX_EVENT_KEY_RELEASE_MASK, ctrl_key_release, c);
	mlx_hook(win, MLX_EVENT_MOUSE_PRESS, MLX_EVENT_MOUSE_PRESS_MASK, ctrl_mouse_press, c);
	mlx_hook(win, MLX_EVENT_MOUSE_RELEASE, MLX_EVENT_MOUSE_RELEASE_MASK, ctrl_mouse_release, c);
	mlx_hook(win, MLX_EVENT_MOUSE_MOVE, MLX_EVENT_MOUSE_MOVE_MASK, ctrl_mouse_move, c);
	mlx_hook(win, MLX_EVENT_EXIT, MLX_EVENT_MOUSE_PRESS_MASK, &close_hook, fdf);
}
