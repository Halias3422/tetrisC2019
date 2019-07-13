#include "tetris.h"

void	create_simple_bar_tetro(t_tetro *tetro, t_tetris *tetris)
{
	int	i = 0;

	while (tetro->next)
	{
		tetro->x = tetris->x;
		tetro->y = tetris->y + i;
		i++;
		tetro = tetro->next;
	}
}

void	get_simple_tetro_location(t_tetro *tetro, t_tetris *tetris)
{
	if (tetris->tetro_type == 1 && tetris->tetro_rotat == 0)
		create_simple_bar_tetro(tetro, tetris);
}

void	spawn_tetro_somewhere_else(t_tetro *tetro, t_tetris *tetris, int left_x, int right_x)
{
	int	resolved = 0;

	tetris->x = 0 + left_x;
	tetris->y = 0;
	while (tetro->prev)
		tetro = tetro->prev;
	get_simple_tetro_location(tetro, tetris);
	while (tetris->x + right_x < 12 && resolved < 4)
	{
		resolved = 0;
		while (tetro->next)
		{
			if (tetro->x + tetris->x < 12 && tetris->area[tetro->y][tetro->x + tetris->x] == '.')
				resolved++;
			tetro = tetro->next;
		}
		if (resolved < 4)
			tetris->x += 1;
		while (tetro->prev)
			tetro = tetro->prev;	
	}
	if (resolved < 4)
	{
		printw("jai perdu au respawn\n");
		refresh();
		sleep(3000);
		tetris->lost = 1;
	}
	else
	{
		while (tetro->next)
		{
			tetro->x += tetris->x;
			tetro = tetro->next;
		}
	}
	tetris->tetro_grounded = 0;
}

void	create_bar_tetro_0(t_tetro *tetro, t_tetris *tetris)
{
	int	i = 0;
	t_tetro	*head;
	
	if (tetris->rotating == 1 && tetris->y > 2 && (tetris->y == 24 ||  (tetris->y < 23 && (tetris->area[tetris->y + 1][tetris->x] == '.' && tetris->area[tetris->y + 2][tetris->x] == 'O'))))
		tetris->y -= 3;
	else if (tetris->rotating == 1 && tetris->y > 3 && tetris->y < 24 && tetris->area[tetris->y + 1][tetris->x] == 'O')
		tetris->y -= 4;
	else if (tetris->rotating == 1 && tetris->y == 22)
		tetris->y = -1;
	else if (tetris->rotating == 1 && tetris->y == 23)
		tetris->y = -2;
	head = tetro;
	while (tetro->next)
	{
		tetro->x = tetris->x;
		tetro->y = tetris->y + i;
		if (tetris->rotating == 1 && (tetro->y > 24 || tetris->area[tetro->y][tetro->x] == 'O'))
		{
			printw("tetro->y = %d | ", tetro->y);
			refresh();
			create_bar_tetro_1(head, tetris);
			tetro = head;
			tetris->tetro_rotat = 1;
			return ;
		}	
		if (tetris->tetro_grounded == 1 && tetris->area[tetro->y][tetro->x] == 'O')
			spawn_tetro_somewhere_else(tetro, tetris, 0, 0);
		i++;
		tetro = tetro->next;
	}
	tetris->tetro_grounded = 0;
	tetro = tetro->prev;
	printw("final y = %d ", tetro->y);
	if (tetro->y == 24 || (tetro->y < 24 && tetris->area[tetro->y + 1][tetro->x] == 'O'))
		tetris->tetro_grounded = 1; 
}

void	create_bar_tetro_1(t_tetro *tetro, t_tetris *tetris)
{
	t_tetro	*head;
	int	i;
	int	grounded = 0;

	if (tetris->x > 0 && tetris->x < 10 && tetris->area[tetris->y][tetris->x - 1] == '.' && tetris->area[tetris->y][tetris->x + 1] == '.' && tetris->area[tetris->y][tetris->x + 2] == '.')
		i = -1;
	else if (tetris->x > 1 && tetris->x < 11 && tetris->area[tetris->y][tetris->x - 2] == '.' && tetris->area[tetris->y][tetris->x - 1] == '.' && tetris->area[tetris->y][tetris->x + 1] == '.')
		i = -2;
	else if (tetris->x == 11 || (tetris->x > 2 && tetris->area[tetris->y][tetris->x - 3] == '.' && tetris->area[tetris->y][tetris->x - 2] == '.' && tetris->area[tetris->y][tetris->x - 1] == '.'))
		i = -3;
	else if (tetris->x == 0 || (tetris->x < 9 && tetris->area[tetro->y][tetro->x + 1] == '.' && tetris->area[tetro->y][tetro->x + 2] == '.' && tetris->area[tetro->y][tetro->x + 3] == '.'))
	       i = 0;	
	head = tetro;
	while (tetro->next)
	{
		tetro->x = tetris->x + i;
		tetro->y = tetris->y;
		if (tetris->rotating == 1 && (tetro->y > 24 || tetris->area[tetro->y][tetro->x] == 'O'))
		{
			create_bar_tetro_0(head, tetris);
			tetro = head;
			tetris->tetro_rotat = 0;
			return ;
		}
		if (tetro->y < 24 && tetris->area[tetro->y + 1][tetro->x] == 'O')
			grounded = 1;
		tetro = tetro->next;
		i++;
	}
	tetro = tetro->prev;
	tetris->tetro_grounded = 0;
	if (tetro->y == 24 || grounded == 1)
		tetris->tetro_grounded = 1;
}
