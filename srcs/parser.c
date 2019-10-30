#include "parser.h"

void print_parser_data(t_parse_obj *parser)
{
//	printf("Vertices : ");
	printf("Number of vertices : %zu\n", parser->len_vertices);
	printf("Number of normal : %zu\n", parser->len_vertices_normal);
	printf("Number of texture : %zu\n", parser->len_vertices_texture);
	printf("Number of faces : %zu\n", parser->len_faces);
	for (size_t i = 0; i < parser->index_vertices; i++)
		printf("Vertice [%zu] = ( %f, %f, %f )\n", i, parser->vertices[i].x, parser->vertices[i].y, parser->vertices[i].z);
	for (size_t i = 0; i < parser->index_vertices_normal; i++)
		printf("Vertice normal [%zu] = ( %f, %f, %f )\n", i, parser->vertices_normal[i].x, parser->vertices_normal[i].y,parser->vertices_normal[i].z);
	for (size_t i = 0; i < parser->index_vertices_texture; i++)
		printf("Vertice texture [%zu] = ( %f, %f, %f )\n", i, parser->vertices_texture[i].x, parser->vertices_texture[i].y, parser->vertices_texture[i].z);
}

void	init_parse_obj(t_parse_obj *parser)
{
	parser->vertices = NULL;
	parser->vertices_normal = NULL;
	parser->vertices_texture = NULL;
	parser->indices = NULL;
	parser->face_type = V_1;
	parser->len_vertices = 0;
	parser->len_vertices_normal = 0;
	parser->len_vertices_texture = 0;
	parser->len_faces = 0;
	parser->index_vertices = 0;
	parser->index_vertices_normal = 0;
	parser->index_vertices_texture = 0;
}

uint8_t	check_float(const char *str, float *f)
{
	size_t	len;
	size_t	i;
	uint8_t	point;
	uint8_t	is_digit;

	i = 0;
	point = 0;
	len = ft_strlen(str);
	while (i < len && !ft_iswsp(str[i]))
	{
		is_digit = ft_isdigit(str[i]);
		if (!point && str[i] == '.' && i != 0 && i != len - 1)
			point = 1;
		else if ((str[i] == '.' && point) || (!is_digit && str[i] != '-')
				|| (str[i] == '-'  && i != 0))
			return (0);
		i++;
	}
	if (!point)
		return (0);
	errno = 0;
	*f = strtof(str, NULL);
	if (errno == ERANGE)
		return (0);
	return (1);
}
/*
void	get_length_arrays_obj(char **data, t_parse_obj *parse)
{
	size_t	i;
	size_t	len_array;

	i = 0;
	len_array = sizeof(data) / sizeof(data[0]);
	printf("Len = |%zu|\n", len_array);
	while (data[i])
	{
//	printf("Data[%zu] = |%s|\n", i, data[i]);
		if (!ft_strncmp(data[i], "v ", 2))
			parse->len_vertices++;
		else if (!ft_strncmp(data[i], "vt ", 3))
			parse->len_vertices_texture++;
		else if (!ft_strncmp(data[i], "vn ", 3))
			parse->len_vertices_normal++;
		else if (!ft_strncmp(data[i], "f ", 2))
		i++;
	}
}
*/
void	handle_faces(t_parse_obj *parse, char *str) {
	int		nb_faces;
	int		i;
	char	*get_esp;
	char	*get_nl;

	i = 0;
	nb_faces = 0;
	printf("Starting handling_face\n");
	get_nl = ft_strchr(str, '\n');
	while (str[i] && &str[i] < get_nl) {
		printf("index: %c\n", str[i]);
		if (!(get_esp = ft_strchr(&str[i], ' ')))
			break ; // handle_error
		nb_faces++;
		if (nb_faces >= 5)
			break;
		if (!get_esp)
			i += ft_strlen(&str[i]);
		else
			i += get_esp - &str[i];
		if (str[i])
			i++;
	}
	printf("End of parcing faces, nb : %d\n", nb_faces);
	if (i > str[i])
		printf("Error");//handle_error
	if (nb_faces > 5)
		return ; //handle_error
	parse->len_faces += (nb_faces == 5 || (!get_esp && nb_faces == 4)) ? 2 : 1;
	printf("len_faces : %zu\n", parse->len_faces);
}

void	get_length_arrays_obj(char *data, t_parse_obj *parse)
{
	size_t	i;
	char	*get_nl;

	i = 0;
	while (data[i])
	{
		if ((get_nl = ft_strchr(&data[i], '\n')) == NULL)
			return ; // Handle Error
		if (!ft_strncmp(&data[i], "v ", 2))
			parse->len_vertices++;
		else if (!ft_strncmp(&data[i], "vt ", 3))
			parse->len_vertices_texture++;
		else if (!ft_strncmp(&data[i], "vn ", 3))
			parse->len_vertices_normal++;
		else if (!ft_strncmp(&data[i], "f ", 2))
			handle_faces(parse, &data[i]);
		i += get_nl - &data[i];
		i++;
	}
}

void	create_vertices_arrays(t_parse_obj *parse)
{
	if (!(parse->vertices = (t_vec3 *)malloc(sizeof(t_vec3) * parse->len_vertices)))
		return ; //Handle_error
	if (!(parse->vertices_normal = (t_vec3 *)malloc(sizeof(t_vec3) * parse->len_vertices_normal)))
		return ; //Handle_error
	if (!(parse->vertices_texture = (t_vec3 *)malloc(sizeof(t_vec3) * parse->len_vertices_texture)))
		return ; //Handle_error
	if (!(parse->all_data = (float *)malloc(sizeof(float) * ((3 * parse->len_vertices) + (2 * parse->len_vertices) + (3 * parse->len_vertices)))))
		return ; //Handle_error
	if (!(parse->indices_data = (int *)malloc(sizeof(int) * parse->len_faces)))
		return ; //Handle_error
}

uint8_t	add_vertice(t_vec3 *vec, char *str, size_t *index, e_token_obj type)
{
	int		i;
	char	*get_esp;
	char	*get_nl;

	i = 0;
	get_nl = ft_strchr(str, '\n');
	if (!(get_esp = ft_strchr(&str[i], ' ')))
		return (print_error("Error: Parser: Wrong format in the obj file, missing a space character", NULL));
	i += get_esp - &str[i] + 1;
	float f = check_float(&str[i], &f);
	printf("Value: %f\n", f);
	if (str[i])
		check_float(&str[i], &vec[*index].x);
	if (!(get_esp = ft_strchr(&str[i], ' ')))
		return (print_error("Error: Parser: Wrong format in the obj file, missing a space character", NULL));
	i += get_esp - &str[i] + 1;
	if (str[i])
		check_float(&str[i], &vec[*index].y);
	if (type == TEXTURE)
	{
		(*index)++;
		return (1);
	}
	if (!(get_esp = ft_strchr(&str[i], ' ')))
		return (print_error("Error: Parser: Wrong format in the obj file, missing a space character", NULL));
	i += get_esp - &str[i] + 1;
	if (str[i])
		check_float(&str[i], &vec[*index].z);
	(*index)++;
	return (1);
}
// Check indexes with len etc
// //Handle Vec2 for textures;
uint8_t	parse_faces(t_parse_obj *parse, char *data)
{
	return (0);
}

uint8_t	get_vertices_values(char *data, t_parse_obj *parse)
{
	size_t	i;
	char	*get_nl;

	i = 0;
	while (data[i])
	{
		if (!ft_strncmp(&data[i], "v ", 2))
			add_vertice(parse->vertices, &data[i], &parse->index_vertices);
		else if (!ft_strncmp(&data[i], "vt ", 3))
			add_vertice(parse->vertices_normal, &data[i], &parse->index_vertices_normal);
		else if (!ft_strncmp(&data[i], "vn ", 3))
			add_vertice(parse->vertices_texture, &data[i], &parse->index_vertices_texture);
		else if (!ft_strncmp(&data[i], "f ", 2))
			return (handle_faces(parse, &data[i]));
		if ((get_nl = ft_strchr(&data[i], '\n')) == NULL)
			return (1); // Handle Error
		i += get_nl - &data[i];
		i++;
	}
	return (1);
}

void	parse_obj_data(char *data, t_parse_obj *parse)
{
	get_length_arrays_obj(data, parse);
	create_vertices_arrays(parse);
	get_vertices_values(data, parse);
}

uint8_t	parse_obj_file(const char *obj_name)
{
	char		*obj_data_str;
	t_parse_obj	*parse;

	if (!(parse = (t_parse_obj *)malloc(sizeof(t_parse_obj))))
		return ((uint8_t)print_error("Error: Cannot allocate memory for parser structure", NULL));
	init_parse_obj(parse);
	printf("Parser initialized\n");
	if (!(obj_data_str = read_file(obj_name, "r")))
		return (NULL);
	printf("File readed\n");
	parse_obj_data(obj_data_str, parse);

	ft_strdel(&obj_data_str);
print_parser_data(parse);
	return (1);
}


int main(int argc, char **argv) {
	if (argc != 2)
		return (1);
	if (!parse_obj_file(argv[1]))
		return (1);
	return (0);
}

/*
int	float_parser_main()
{
	char	*tests[] = {
		"1.0", "2.", "2.0402095308520457248082",
		"55555555555555555555555555555555555555",
		"55555555555555555555555555555555555555333333333333333333333333333.0",
		"55555555555555555555555555555555555555.0",
		"abc", "a.0", "1a.0", "1.a0",
		"1..0", ".10", "2.2.4", "1.3f", "1.4 ", "2",
		"-2", "-2.0"
	};
	size_t	len = sizeof(tests) / sizeof(tests[0]);
	uint8_t	isfloat;
	float	fl;

	for (size_t i = 0; i < len; i++) {
		printf("Test for : |%s|\n", tests[i]);
		isfloat = check_float(tests[i], &fl);
		if (isfloat)
			printf("Is a float\n");
		else
			printf("Is not a float\n");
	}
	return (0);
}
*/
