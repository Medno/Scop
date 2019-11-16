/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_limits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:10:47 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 15:46:09 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	find_limits_obj(t_vec3 *vert, size_t len, t_vec3 *min, t_vec3 *max)
{
	size_t	i;

	i = 1;
	*min = vert[0];
	*max = vert[0];
	while (i < len)
	{
		if (max->x < vert[i].x)
			max->x = vert[i].x;
		if (max->y < vert[i].y)
			max->y = vert[i].y;
		if (max->z < vert[i].z)
			max->z = vert[i].z;
		if (min->x > vert[i].x)
			min->x = vert[i].x;
		if (min->y > vert[i].y)
			min->y = vert[i].y;
		if (min->z > vert[i].z)
			min->z = vert[i].z;
		i++;
	}
}

t_vec3	find_center(t_vec3 *vertices, size_t len)
{
	t_vec3	min;
	t_vec3	max;

	find_limits_obj(vertices, len, &min, &max);
	return (vec3_mul_scalar(vec3_add(min, max), 0.5f));
}

void	center_vertices(t_vec3 *vertices, size_t len)
{
	size_t	i;
	t_vec3	size;
	float	theta;
	float	tmp;

	i = 0;
	size = find_center(vertices, len);
	theta = degree_to_radian(90.0f);
	while (i < len)
	{
		vertices[i].x -= size.x;
		vertices[i].y -= size.y;
		vertices[i].z -= size.z;
		tmp = vertices[i].x * cosf(theta)
			- vertices[i].z * sinf(theta);
		vertices[i].z = vertices[i].x * sinf(theta)
			+ vertices[i].z * cosf(theta);
		vertices[i].x = tmp;
		i++;
	}
}
