/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_limits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 10:10:47 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/13 10:42:15 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	find_limits_obj(t_parser_obj *parser, t_vec3 *min, t_vec3 *max)
{
	size_t	i;

	i = 1;
	*min = parser->vertices[0];
	*max = parser->vertices[0];
	while (i < parser->len_vertices)
	{
		if (max->x < parser->vertices[i].x)
			max->x = parser->vertices[i].x;
		if (max->y < parser->vertices[i].y)
			max->y = parser->vertices[i].y;
		if (max->z < parser->vertices[i].z)
			max->z = parser->vertices[i].z;
		if (min->x > parser->vertices[i].x)
			min->x = parser->vertices[i].x;
		if (min->y > parser->vertices[i].y)
			min->y = parser->vertices[i].y;
		if (min->z > parser->vertices[i].z)
			min->z = parser->vertices[i].z;
		i++;
	}
}

t_vec3	find_center(t_parser_obj *parser)
{
	t_vec3	min;
	t_vec3	max;

	find_limits_obj(parser, &min, &max);
	return (vec3_mul_scalar(vec3_add(min, max), 0.5f));
}

void	center_vertices(t_parser_obj *parser)
{
	size_t	i;
	t_vec3	size;
	float	theta;
	float	tmp;

	i = 0;
	size = find_center(parser);
	theta = degree_to_radian(90.0f);
	while (i < parser->all_data_size)
	{
		parser->all_data[i] -= size.x;
		parser->all_data[i + 1] -= size.y;
		parser->all_data[i + 2] -= size.z;
		tmp = parser->all_data[i] * cosf(theta)
			- parser->all_data[i + 2] * sinf(theta);
		parser->all_data[i + 2] = parser->all_data[i] * sinf(theta)
			+ parser->all_data[i + 2] * cosf(theta);
		parser->all_data[i] = tmp;
		i += parser->offset_all_data;
	}
}
