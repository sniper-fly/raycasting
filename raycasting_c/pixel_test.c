#include "minilibx-linux/mlx.h"
#include <stdio.h>

int		main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	// printf("%p", mlx);
	mlx_win = mlx_new_window(mlx, 1920, 1080, "hello world!");
	mlx_loop(mlx);

	return (0);
}
