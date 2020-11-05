/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 11:44:19 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/05 16:40:48 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "definitions.h"

int		key_pressed(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		exit(0);
	else if (key_code == KEY_W)
		g_player.walk_direction = 1;
	else if (key_code == KEY_S)
		g_player.walk_direction = -1;
	else if (key_code == KEY_A)
	{
		g_player.walk_direction = 1;
		g_player.side_angle = PI / 2;
	}
	else if (key_code == KEY_D)
	{
		g_player.walk_direction = 1;
		g_player.side_angle = (PI / 2) * -1;
	}
	else if (key_code == KEY_LEFT_ARROW)
		g_player.turn_direction = -1;
	else if (key_code == KEY_RIGHT_ARROW)
		g_player.turn_direction = +1;
	g_key_flag = TRUE;
	return (0);
}

int		key_released(int key_code, t_game *game)
{
	if (key_code == KEY_W)
		g_player.walk_direction = 0;
	else if (key_code == KEY_S)
		g_player.walk_direction = 0;
	else if (key_code == KEY_A)
	{
		g_player.walk_direction = 0;
		g_player.side_angle = 0;
	}
	else if (key_code == KEY_D)
	{
		g_player.walk_direction = 0;
		g_player.side_angle = 0;
	}
	else if (key_code == KEY_LEFT_ARROW)
		g_player.turn_direction = 0;
	else if (key_code == KEY_RIGHT_ARROW)
		g_player.turn_direction = 0;
	return (0);
}