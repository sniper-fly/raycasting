#include "minilibx-linux/mlx.h"

typedef	struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

int		main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./beako.xpm";
	int		img_width = 800;
	int		img_height = 1128;
	void	*mlx_win;
	t_data	print_img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "hello world!");
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
}