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
int		g_player_x = 20;
int		g_player_y = 20;
int		g_key_flag = TRUE;


void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	game->img.data[y * WIDTH + x] = color;
	// int		*dst;
	// dst = game->img.data + (y * game->img.size_l + x * game->img.bpp / (sizeof(int) * 8));
	// *dst = color;
}

void	draw_line(t_game *game, double x1, double y1, double x2, double y2)
{
	double	deltaX;
	double	deltaY;
	double	step;

	deltaX = x2 - x1;
	deltaY = y2 - y1;
	step = (fabs(deltaX) > fabs(deltaY)) ? fabs(deltaX) : fabs(deltaY);
	deltaX /= step;
	deltaY /= step;
	while (fabs(x2 - x1) > 0.01 || fabs(y2 - y1) > 0.01)
	{
		game->img.data[TO_COORD(x1, y1)] = 0xb3b3b3;
		x1 += deltaX;
		y1 += deltaY;
	}
}

void 	draw_lines(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < COLS)
	{
		draw_line(game, i * TILE_SIZE, 0, i * TILE_SIZE, HEIGHT);
		i++;
	}
	draw_line(game, COLS * TILE_SIZE - 1, 0, COLS * TILE_SIZE - 1, HEIGHT);
	j = 0;
	while (j < ROWS)
	{
		draw_line(game, 0, j * TILE_SIZE, WIDTH, j * TILE_SIZE);
		j++;
	}
	draw_line(game, 0, ROWS * TILE_SIZE - 1, WIDTH, ROWS * TILE_SIZE - 1);
}

void	draw_rectangle(t_game *game, int x, int y, int color)
{
	int i;
	int j;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			game->img.data[(y  + i) * WIDTH + x + j] = color;
			j++;
		}
		i++;
	}
}

void	draw_rectangles(t_game *game)
{
	int		i;
	int		j;

	i = 0;
	while (i < ROWS)
	{
		j = 0;
		while (j < COLS)
		{
			if (g_map[i][j] == 1)
				draw_rectangle(game, j, i, 0xffffff);
			else
				draw_rectangle(game, j, i, 0x000000);
			j++;
		}
		i++;
	}
}

void	render_rectangle(t_game *game, t_rect_info *rect, int color)
{
	int	x_end;
	int y_end;
	int y_tmp;

	x_end = rect->x + rect->width;
	y_end = rect->y + rect->height;
	y_tmp = rect->y;
	while (rect->x < x_end)
	{
		rect->y = y_tmp;
		while (rect->y < y_end)
		{
			my_mlx_pixel_put(game, rect->x, rect->y, color);
			rect->y += 1;
		}
		rect->x += 1;
	}
}

void	render_line(t_game *game, t_line_info *line, int color)
{
	double		a;
	double		b;
	t_line_info	lncp;
	
	//x1には必ず小さいほう、x2には必ず大きい数がはいる
	lncp.x1 = (line->x1 <= line->x2) ? line->x1 : line->x2;
	lncp.x2 = (line->x1 <= line->x2) ? line->x2 : line->x1;
	if (line->x1 == line->x2)
	{
		lncp.y1 = (line->y1 <= line->y2) ? line->y1 : line->y2;
		lncp.y2 = (line->y1 <= line->y2) ? line->y2 : line->y1;
		while (lncp.y1 <= lncp.y2)
		{
			my_mlx_pixel_put(game, lncp.x1, lncp.y1, color);
			lncp.y1++;
		}
	}
	else
	{
		a = (line->y1 - line->y2) / (line->x1 - line->x2);
		b = line->y1 - (a * line->x1);
		while (lncp.x1 <= lncp.x2)
		{
			my_mlx_pixel_put(game, lncp.x1, (a * lncp.x1 + b), color);
			lncp.x1++;
		}
	}
}

int		deal_key(int key_code, t_game *game)
{
	if (key_code == KEY_ESC)
		exit(0);
	else if (key_code == KEY_W)
		g_player_y -= 10;
	else if (key_code == KEY_S)
		g_player_y += 10;
	else if (key_code == KEY_A)
		g_player_x -= 10;
	else if (key_code == KEY_D)
		g_player_x += 10;
	g_key_flag = TRUE;
	return (0);
}