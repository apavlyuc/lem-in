#ifndef LEMIN_H
# define LEMIN_H

# include "../../libft/inc/libft_types.h"
# include <stdio.h>

typedef struct	s_binding
{
	char	*node;
	t_list	*neighbours;
}				t_binding;

typedef struct	s_farm
{
	t_list	*rooms;
	t_list	*links;
	char	*start_room_name;
	char	*finish_room_name;
	int		ants_count;
}				t_farm;

typedef struct	s_link {
	char			*name;
	int				id;
	struct s_link	*next;
}				t_link;

typedef struct	s_node {
	int		used;
	int		index;
	char	*name;
	t_link	*link;
	int		links_count;
}				t_node;

typedef struct	s_path {
	int				length;
	int				id;
	int				ant;
	int				amount;
	struct s_path	*step_forward;
	struct s_path	*next_branch;
}				t_path;

typedef struct	s_scenario {
	t_path	*paths;
	int		id;
	int		complexity;
}				t_scenario;

typedef struct	s_data {
	t_node		*nodes;
	int			count_of_nodes;
	t_path		*paths;
	int			count_of_paths;
	t_scenario	*bad_scenario;
	t_scenario	*scenarios;
	int			count_of_scenarios;
	int			mn_var;
	t_farm		*farm;
}				t_data;

/*
**			parser/reader.c
*/
int				read_farm(t_farm *farm);
/*
**			parser/validator.c
*/
int				validate_farm(t_farm *farm);
int				is_valid_room(char *room);
int				is_valid_link(char *link);
int				is_valid_command(char *command);
int				is_valid_comment(char *comment);
/*
**			parser/getters.c
*/
int				get_next_room_type(char *line);
char			*get_room_name(char *line);
char			*get_link_part(char *link, int part);
/*
**			utility/farm.c
*/
int				add_room(t_farm *farm, char *room_name, int room_type);
int				add_link(t_farm *farm, char *link);
/*
**			utility/binding.c
*/
t_binding		*find_binding(t_list *links, char *node);
t_binding		*create_binding(char *node, char *neighbour);
void			add_neighbour(t_binding *binding, char *name);
void			add_binding(t_list **links, t_binding *binding);
/*
**			logic/game.c
*/
void			play_game(t_farm *farm);
/*
**			logic/simple_path.c
*/
int				find_simple_path(t_data *data, t_farm *farm);
/*
**			logic/indexs.c
*/
void			reinit_nodes_indexs(t_data *data, t_farm *farm, t_link *near);
/*
**			logic/refresh.c
*/
void			shuffle_party(t_data *data, t_farm *farm, int index);
/*
**			logic/superposition_handler.c
*/
void			handle_superposition(t_data *data, t_farm *farm);
void			add_path(t_data *data, t_path *to_add, t_farm *farm);
/*
**			logic/checker.c
*/
int				compare(t_scenario *scen, t_path *path);
int				check_is_amount(t_data *data, t_path **tmp, t_path **path, t_path **prev);
int				check_paths(t_data *data, t_path **tmp, t_path **path, t_path **prev);
/*
**			logic/converter/convert.c
*/
void			change_data_type(t_data *data, t_farm *farm);
/*
**			logic/utility/link.c
*/
t_ull			get_list_size(t_list *lst);
t_link			*create_link(char *name, int id);
t_link			*get_link_at(t_node *node, int index);
void			append_to_link(t_link *link, t_link *new);
/*
**			logic/utility/path.c
*/
t_path			*create_path(int length, int id, t_path *branch, t_path *step);
void			add_node_to_path(t_path *path, int id);
int				is_node_in_path(t_path *path, int id);
void			del_steps(t_path *path);
/*
**			logic/printer/printer.c
*/
void			choose_printing_logic(t_data *data, t_farm *farm);
/*
**			logic/deleter/cleaner.c
*/
void			clear_data(t_data *data);
void			clear_path(t_path **path);

//////////////////////////////////////////////////////////////////
#endif