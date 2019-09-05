/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbeahan <mbeahan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 12:35:01 by rymuller          #+#    #+#             */
/*   Updated: 2019/09/05 16:42:50 by mbeahan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include <libft.h>

typedef struct			s_node
{
	char				*name;
	int					x;
	int					y;
	int					count_ants_here;
	int					ant_name;
}						t_node;

typedef struct			s_lst
{
	void				*adjlst;
	struct s_lst		*next;
}						t_lst;

typedef struct			s_adjlst
{
	t_node				node;
	t_lst				*lst;
	int					level;
	int					visited_bfs;
	int					visited_pth;
	struct s_adjlst		*next;
}						t_adjlst;

typedef struct			s_path
{
	t_adjlst			*start;
	t_lst				*path_lst[2];
	int					path_len;
	int					ants_on_the_way;
	struct s_path		*next;
}						t_path;

typedef struct			s_lemin
{
	int					number_of_ants;
	int					count_bfs;
	unsigned int		is_ants:1;
	unsigned int		is_start:1;
	unsigned int		is_end:1;
	t_adjlst			*adjlst;
	t_adjlst			*start;
	t_adjlst			*end;
	t_lst				*queue;
	t_path				*paths;
	t_adjlst			*buffer;
}						t_lemin;

int						ft_printf(char const *s, ...);
t_adjlst				*ft_adjlst_push_back(t_lemin *lemin, t_node *node);
t_lst					*ft_new_lst(t_adjlst *adjlst);
t_lst					*ft_lst_push_back(t_lemin *lemin,
		t_adjlst *adjlst1, t_adjlst *adjlst2);
void					free_adjlst(t_lemin *lemin);
void					free_path_lst(t_lst *path_lst[2]);
char					parse_room(t_lemin *lemin, char *line);
char					parse_link(t_lemin *lemin, char *line);
void					free_graph(t_lemin *lemin);
void					ft_push_queue(t_lemin *lemin, t_adjlst *adjlst);
void					ft_pop_queue(t_lemin *lemin);
char					not_in_queue(t_lemin *lemin, t_adjlst *adjlst);
void					breadth_first_search_to_start(t_lemin *lemin);
char					add_shortest_parallel_path_to_paths(t_lemin *lemin);
int						put_ant_to_path(t_lemin *lemin,
		t_path *paths, int current_ant);
void					do_iter(t_lemin *lemin);
void					move_ant(t_lst *hill_with_ant,
		t_path *path, t_lemin *lemin);
int						ants_on_the_way(t_path *path);
void					print_ops(t_lst *hill_with_ant,
		t_path *path, int flag);
t_lst					*last_ant_detect(t_lst *stop,
		t_lst	*hill_with_ant, t_lst *current_hill);
int						send_or_not(t_lemin *lemin, t_path *best,
		t_path *other, int curr_ant);
# define ERROR(lemin) free_graph(lemin); write(2, "ERROR\n", 6); return (0)
#endif
