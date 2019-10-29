#include "parser.h"

void print_parser_data(t_parse_obj *parser)
{
//	printf("Vertices : ");
	printf("Number of vertices : %zu\n", parser->len_vertices);
	printf("Number of normal : %zu\n", parser->len_vertices_normal);
	printf("Number of texture : %zu\n", parser->len_vertices_texture);
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
	while (i < len)
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
		i++;
	}
}
//TODO: Find a way to pass 4 by 4 vertices (no splitting a face)
void	parse_obj_data(char **data, t_parse_obj *parse)
{
	get_length_arrays_obj(data, parse);
}

void	parse_obj_file(const char *obj_name)
{
	char		*obj_data_str;
	char		**obj_data;
	t_parse_obj	*parse;

	if (!(parse = (t_parse_obj *)malloc(sizeof(t_parse_obj))))
		return ;
	init_parse_obj(parse);
	printf("Parser initialized\n");
	if (!(obj_data_str = read_file(obj_name, "r")))
		return ;
	printf("File readed\n");
	if ((obj_data = ft_strsplit(obj_data_str, '\n')) != NULL)
	{
	printf("File data has been splitted\n");
		parse_obj_data(obj_data, parse);
		ft_tabdel(obj_data);
	}
	ft_strdel(&obj_data_str);
print_parser_data(parse);
	return ;
}



int main(int argc, char **argv) {
	if (argc != 2)
		return (1);
	parse_obj_file(argv[1]);
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
