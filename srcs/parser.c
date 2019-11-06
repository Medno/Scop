/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pchadeni <pchadeni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:25:29 by pchadeni          #+#    #+#             */
/*   Updated: 2019/11/06 15:20:08 by pchadeni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	parse_obj_data(char *data, t_parse_obj *parse)
{
	if (!get_length_arrays_obj(data, parse))
		return ;
	if (!create_vertices_arrays(parse))
		return ;
	get_vertices_values(data, parse);
}

uint8_t	parse_obj_file(const char *obj_name)
{
	char		*obj_data_str;
	t_parse_obj	*parse;

	if (!(parse = init_parse_obj()))
		return (1);
printf("Parser initialized\n");
	if (!(obj_data_str = read_file(obj_name, "r", &parse->obj_size)))
		return (0);
printf("File readed\n");
	parse_obj_data(obj_data_str, parse);

	ft_strdel(&obj_data_str);
print_parser_data(parse);
destroy_parse_obj(parse);
	return (1);
}

int main(int argc, char **argv) {
	if (argc != 2)
		return (1);
	if (!parse_obj_file(argv[1]))
		return (1);
	return (0);
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
