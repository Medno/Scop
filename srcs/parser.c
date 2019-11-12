/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:29 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/07 16:46:49 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void			put_texture_vertices(t_parser_obj *parser)
{
	size_t	i;

	if (parser->len_vertices_texture != 0)
		return ;

	i = 0;
	while (i < parser->all_data_size)
	{
		parser->all_data[i + parser->offset_all_data - 2] = parser->all_data[i];
		parser->all_data[i + parser->offset_all_data - 1] =
			parser->all_data[i + 2];
		i += parser->offset_all_data;
	}
}

uint8_t			parse_obj_data(char *data, t_parser_obj *parse)
{
	if (!get_length_arrays_obj(data, parse) || !create_vertices_arrays(parse)
		|| !get_vertices_values(data, parse))
		return (0);
	put_texture_vertices(parse);
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
		return (NULL);
		//print_parser_data(parser);
	ft_strdel(&obj_data_str);
	return (parser);
}

uint8_t			print_parser_error(t_error_parser error)
{
	char	buf[512];

	if (error == ARRAY_VERTICES)
		strcpy(buf, "Error: Cannot allocate memory for array of vertices");
	else if (error == ARRAY_VERTICES_NORMAL)
		strcpy(buf,
				"Error: Cannot allocate memory for array of normal vertices");
	else if (error == ARRAY_VERTICES_TEXTURE)
		strcpy(buf,
				"Error: Cannot allocate memory for array of texture vertices");
	else if (error == ARRAY_ALL_DATA)
		strcpy(buf,
			"Error: Cannot allocate memory for the array sent to OpenGL");
	else if (error == ARRAY_INDICES)
		strcpy(buf, "Error: Cannot allocate memory for the array of indices");
	else if (error == PARSING_NO_NEWLINE)
		strcpy(buf, "Error: Missing newline in obj file");
	else if (error == PARSING_NB_FACES)
		strcpy(buf, "Error: Parser: Invalid number of faces");
	else if (error == PARSING_MISSING_SPACE)
		strcpy(buf, "Error: Parser: Wrong format, missing a space character");
	else if (error == PARSING_INDEX_OUT_OF_BOUND)
		strcpy(buf, "Error: Parser: Index out of bound");
	return ((uint8_t)print_error(buf, NULL));
}
