# ifndef TETRIS_H
#define TETRIS_H


# define HEIGHT 25
# define WIDTH 12

#include <curses.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct	s_tetris
{
	char	**area;
	int	completed;
	int	tetro_grounded;
	int	lost;
	int	tetro_type;
	int	x;
	int	y;
	int	tetro_rotat;
	int	rotating;
	int	respawning;
}		t_tetris;

typedef struct	s_tetro
{
	int	x;
	int	y;
	struct s_tetro	*next;
	struct s_tetro	*prev;
}		t_tetro;

//tetris.c

void	get_tetro_location(t_tetro *tetro, t_tetris *tetris);

//tetrominos.c

t_tetro	*add_list_back(t_tetro *tetro);

void	create_bar_tetro_0(t_tetro *tetro, t_tetris *tetris);
void	create_bar_tetro_1(t_tetro *tetro, t_tetris *tetris);

void	create_square_tetro(t_tetro *tetro, t_tetris *tetris);

void	create_t_tetro_0(t_tetro *tetro, t_tetris *tetris);
void	create_t_tetro_1(t_tetro *tetro, t_tetris *tetris);
void	create_t_tetro_2(t_tetro *tetro, t_tetris *tetris);
void	create_t_tetro_3(t_tetro *tetro, t_tetris *tetris);

void	create_l_tetro_0(t_tetro *tetro, t_tetris *tetris);
void	create_l_tetro_1(t_tetro *tetro, t_tetris *tetris);
void	create_l_tetro_2(t_tetro *tetro, t_tetris *tetris);
void	create_l_tetro_3(t_tetro *tetro, t_tetris *tetris);

void	create_j_tetro_0(t_tetro *tetro, t_tetris *tetris);
void	create_j_tetro_1(t_tetro *tetro, t_tetris *tetris);
void	create_j_tetro_2(t_tetro *tetro, t_tetris *tetris);
void	create_j_tetro_3(t_tetro *tetro, t_tetris *tetris);

void	create_z_tetro_0(t_tetro *tetro, t_tetris *tetris);
void	create_z_tetro_1(t_tetro *tetro, t_tetris *tetris);

void	create_s_tetro_0(t_tetro *tetro, t_tetris *tetris);
void	create_s_tetro_1(t_tetro *tetro, t_tetris *tetris);

#endif
