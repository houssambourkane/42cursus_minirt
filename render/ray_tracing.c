/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_tracing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbourkan <hbourkan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 23:37:01 by hbourkan          #+#    #+#             */
/*   Updated: 2022/06/09 15:15:30 by hbourkan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray_tracing.h"

t_solution	*get_solution_origin(t_data data, t_vector ray, t_point origin)
{
	t_solution	*arr_t[3];

	arr_t[0] = plane_rendering(data, ray, origin);
	arr_t[1] = sphere_rendering(data, ray, origin);
	arr_t[2] = cylinder_rendering(data, ray, origin);
	return (get_min(arr_t));
}

void	rendering(t_data data, t_mlx ml, t_solution *s, t_vector ray)
{
	if (s)
	{
		if (shadow_rending(data, s, ray))
			ml.image_ptr[ml.pos] = create_trgb(TRANSPARENCY,
					data.amb_light->rgb, 1, data.amb_light->ratio);
		else
			ml.image_ptr[ml.pos] = s->color;
		free(s);
	}
}

void	ray_tracer(t_data data, t_mlx ml, t_point origin)
{
	t_vector	ray;
	t_solution	*s;
	int			x;
	int			y;

	y = -1;
	transform_cam_world(data);
	while (++y < IMAGE_HEIGHT)
	{
		x = -1;
		while (++x < IMAGE_WIDTH)
		{
			get_pixel_coord(x, y, &ray, data);
			normalize(&ray);
			s = get_solution_origin(data, ray, origin);
			ml.pos = (y * IMAGE_WIDTH + x);
			rendering(data, ml, s, ray);
		}
	}
}
