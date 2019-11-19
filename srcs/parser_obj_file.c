/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_obj_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 16:20:24 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/16 18:16:29 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

static uint8_t	get_length_arrays_obj(char *data, t_parser_obj *parser)
{
	long	i;
	char	*get_nl;

	i = 0;
	while (i < parser->obj_size)
	{
		get_nl = ft_strchr(&data[i], '\n');
		if (get_nl == NULL)
			get_nl = data + parser->obj_size;
		if (!ft_strncmp(&data[i], "v ", 2))
			parser->len_vertices++;
		else if (!ft_strncmp(&data[i], "vt ", 3))
			parser->len_textures++;
		else if (!ft_strncmp(&data[i], "vn ", 3))
			parser->len_normals++;
		else if (!ft_strncmp(&data[i], "f ", 2))
			if (!handle_faces(parser, &data[i]))
				return (0);
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}

static void		put_texture_vertices(t_parser_obj *parser)
{
	size_t	i;

	if (parser->len_textures != 0)
		return ;
	i = 0;
	while (i < parser->data_size)
	{
		parser->data[i + parser->offset_data - 2] = parser->data[i];
		parser->data[i + parser->offset_data - 1] =
			parser->data[i + 1];
		i += parser->offset_data;
	}
}

static uint8_t	parse_obj_data(char *data, t_parser_obj *parser)
{
	if (!get_length_arrays_obj(data, parser) || !create_vertices_arrays(parser)
		|| !get_vertices_values(data, parser) || !parser->len_vertices)
		return (0);
	center_vertices(parser->vertices, parser->len_vertices);
	if (parser->len_normals > 0)
		center_vertices(parser->normals, parser->len_normals);
	if (!add_faces_into_data(parser))
		return (0);
	put_texture_vertices(parser);
	clean_parser(parser);
	return (1);
}

t_parser_obj	*parse_obj_file(const char *obj_name)
{
	char			*obj_data_str;
	t_parser_obj	*parser;

	if (!(parser = init_parser_obj()))
		return (NULL);
	if (!(obj_data_str = read_file(obj_name, "r", &parser->obj_size)))
		return (NULL);
	if (!parse_obj_data(obj_data_str, parser))
		destroy_parser_obj(&parser, 1);
	ft_strdel(&obj_data_str);
	return (parser);
}
