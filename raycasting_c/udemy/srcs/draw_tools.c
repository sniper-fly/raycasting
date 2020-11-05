/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnakai <rnakai@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 10:15:13 by rnakai            #+#    #+#             */
/*   Updated: 2020/11/05 14:28:24 by rnakai           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "definitions.h"

int		g_map[ROWS][COLS] = {
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
int		g_is_game_running = FALSE;
int		g_key_flag = TRUE;

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	game->img.data[y * WIDTH + x] = color;
	// int		*dst;
	// dst = game->img.data + (y * game->img.size_l + x * game->img.bpp / (sizeof(int) * 8));
	// *dst = color;
}


void	draw_ray(t_game *game, t_line_info *line)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = line->x2 - line->x1;
	deltaY = line->y2 - line->y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(line->x2 - line->x1) > 0.01 || fabs(line->y2 - line->y1) > 0.01)
	{
		game->img.data[TO_COORD(line->x1, line->y1)] = 0xff0000;
		line->x1 += deltaX;
		line->y1 += deltaY;
	}
}

void	render_player_rect(t_game *game, t_rect_info *rect, int color)
{
	int	x_start;
	int	y_start;
	int	x_end;
	int	y_end;
	int	y_tmp;

	x_start = rect->x - (rect->width / 2);
	x_end = rect->x + (rect->width / 2);
	y_start = rect->y - (rect->height / 2);
	y_end = rect->y + (rect->height / 2);
	y_tmp = y_start;
	while (x_start < x_end)
	{
		y_start = y_tmp;
		while (y_start < y_end)
		{
			my_mlx_pixel_put(game, x_start, y_start, color);
			y_start += 1;
		}
		x_start += 1;
	}
}

// void	render_line(t_game *game, t_line_info *line, int color)
// {
// 	double		a;
// 	double		b;
// 	t_line_info	lncp;
// 	//x1には必ず小さいほう、x2には必ず大きい数がはいる
// 	lncp.x1 = (line->x1 <= line->x2) ? line->x1 : line->x2;
// 	lncp.x2 = (line->x1 <= line->x2) ? line->x2 : line->x1;
// 	if (line->x1 == line->x2)
// 	{
// 		lncp.y1 = (line->y1 <= line->y2) ? line->y1 : line->y2;
// 		lncp.y2 = (line->y1 <= line->y2) ? line->y2 : line->y1;
// 		while (lncp.y1 <= lncp.y2)
// 		{
// 			my_mlx_pixel_put(game, lncp.x1, lncp.y1, color);
// 			lncp.y1++;
// 		}
// 	}
// 	else
// 	{
// 		a = (line->y1 - line->y2) / (line->x1 - line->x2);
// 		b = line->y1 - (a * line->x1);
// 		while (lncp.x1 <= lncp.x2)
// 		{
// 			my_mlx_pixel_put(game, lncp.x1, (a * lncp.x1 + b), color);
// 			lncp.x1++;
// 		}
// 	}
// }