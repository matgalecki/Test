

#include "fdf.h"

void	put_pixel(t_fdf *fdf, int x, int y, uint32_t color)
{
	if (x <= 0 || x >= WINDOW_WIDTH || y <= 0 || y >= WINDOW_HEIGHT)
		return ;
	mlx_put_pixel(fdf->img, x, y, color);
}