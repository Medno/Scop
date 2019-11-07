/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:29 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/07 14:30:25 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

uint8_t	parse_obj_data(char *data, t_parser_obj *parse)
{
	if (!get_length_arrays_obj(data, parse) || !create_vertices_arrays(parse)
		|| !get_vertices_values(data, parse))
		return (0);
	return (1);
}

uint8_t	parse_obj_file(const char *obj_name)
{
	char		*obj_data_str;
	t_parser_obj	*parser;

	if (!(parser = init_parser_obj()))
		return (1);
printf("Parser initialized\n");
	if (!(obj_data_str = read_file(obj_name, "r", &parser->obj_size)))
		return (0);
printf("File readed\n");
	if (parse_obj_data(obj_data_str, parser))
		print_parser_data(parser);
	ft_strdel(&obj_data_str);
	if (parser)
destroy_parser_obj(parser);
	return (1);
}

uint8_t	print_parser_error(t_error_parser error)
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
