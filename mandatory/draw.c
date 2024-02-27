#include "cub3d.h"

static void put_x(t_bresenham *bre, t_map_data *map_data, int color);
static void put_y(t_bresenham *bre, t_map_data *map_data, int color);

void draw_line(t_map_data *map_data, double x_end, double y_end, int color)
{
	t_bresenham bre;

	bre.x0 = map_data->player.x;
	bre.y0 = map_data->player.y;
	bre.inc_x = 1;
	bre.inc_y = 1;
	bre.dx = x_end - bre.x0;
	bre.dy = y_end - bre.y0;
	bre.abs_dx = ft_abs(bre.dx);
	bre.abs_dy = ft_abs(bre.dy);
	if (bre.dx < 0)
		bre.inc_x = -1;
	if (bre.dy < 0)
		bre.inc_y = -1;
	if (bre.abs_dx > bre.abs_dy)
		put_x(&bre, map_data, color);
	else
		put_y(&bre, map_data, color);
}

static void put_x(t_bresenham *bre, t_map_data *map_data, int color)
{
	int i;

	i = 0;
	img_pixel_put(&map_data->img, bre->x0, bre->y0, color);
	bre->pk = (2 * bre->abs_dy) - bre->abs_dx;
	while (i < bre->abs_dx)
	{
		bre->x0 += bre->inc_x;
		if (bre->pk < 0)
			bre->pk = bre->pk + (2 * bre->abs_dy);
		else
		{
			bre->pk = bre->pk + (2 * bre->abs_dy) - (2 * bre->abs_dx);
			bre->y0 += bre->inc_y;
		}
		img_pixel_put(&map_data->img, bre->x0, bre->y0, color);
		i++;
	}
}

static void put_y(t_bresenham *bre, t_map_data *map_data, int color)
{
	int i;

	i = 0;
	img_pixel_put(&map_data->img, bre->x0, bre->y0, color);
	bre->pk = (2 * bre->abs_dx) - bre->abs_dy;
	while (i < bre->abs_dy)
	{
		bre->y0 += bre->inc_y;
		if (bre->pk < 0)
			bre->pk = bre->pk + (2 * bre->abs_dx);
		else
		{
			bre->pk = bre->pk + (2 * bre->abs_dx) - (2 * bre->abs_dy);
			bre->x0 += bre->inc_x;
		}
		img_pixel_put(&map_data->img, bre->x0, bre->y0, color);
		i++;
	}
}

float ft_abs(float value)
{
	if (value < 0)
		return (-value);
	else
		return (value);
}
