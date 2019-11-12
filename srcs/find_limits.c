#include "parser.h"

t_vec3	find_min_obj(t_parser_obj *parser)
{
	size_t	i;
	t_vec3	min;

	i = 1;
	min = parser->vertices[0];
	while (i < parser->len_vertices)
	{
		if (min.x > parser->vertices[i].x)
			min.x = parser->vertices[i].x;
		if (min.y > parser->vertices[i].y)
			min.y = parser->vertices[i].y;
		if (min.z > parser->vertices[i].z)
			min.z = parser->vertices[i].z;
		i++;
	}
	return (min);
}

t_vec3	find_max_obj(t_parser_obj *parser)
{
	size_t	i;
	t_vec3	max;

	i = 1;
	max = parser->vertices[0];
	while (i < parser->len_vertices)
	{
		if (max.x < parser->vertices[i].x)
			max.x = parser->vertices[i].x;
		if (max.y < parser->vertices[i].y)
			max.y = parser->vertices[i].y;
		if (max.z < parser->vertices[i].z)
			max.z = parser->vertices[i].z;
		i++;
	}
	return (max);
}

void	center_vertices(t_parser_obj *parser)
{
	size_t	i;
	t_vec3	size;
	float	theta;
	float	tmp;

	i = 0;
	size = vec3_mul_scalar(vec3_add(find_min_obj(parser),
		find_max_obj(parser)), 0.5f);
	theta = 90.0f * (M_PI / 180);
	while (i < parser->all_data_size)
	{
		parser->all_data[i] -= size.x;
		parser->all_data[i + 1] -= size.y;
		parser->all_data[i + 2] -= size.z;
		tmp = parser->all_data[i] * cosf(theta)
				- parser->all_data[i + 2] * sinf(theta);
		parser->all_data[i + 2] = parser->all_data[i] * sinf(theta) \
				+ parser->all_data[i + 2] * cosf(theta);
		parser->all_data[i] = tmp;
		i += parser->offset_all_data;
	}
}
