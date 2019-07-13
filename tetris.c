#include "tetris.h"

void	create_area(t_tetris *tetris)
{
	int	x;
	int	y = 0;

	if (!(tetris->area = (char**)malloc(sizeof(char*) * HEIGHT + 8)))
	{
		printw("ERROR MALLOC\n");
		refresh();
		exit(0);
	}
	while (y < HEIGHT)
	{
		x = 0;
		if (!(tetris->area[y] = (char*)malloc(sizeof(char) * WIDTH + 1)))
		{
			printw("ERROR MALLOC\n");
			refresh();
			exit(0);
		}
		while (x < WIDTH)
		{
			tetris->area[y][x] = '.';
			x++;
		}
		tetris->area[y][x] = '\0';
		y++;
	}
	tetris->area[y] = NULL;
	tetris->lost = 0;
	tetris->tetro_grounded = 1;
}

t_tetro	*add_list_back(t_tetro *tetro)
{
	t_tetro *new;

	new = (t_tetro*)malloc(sizeof(t_tetro));
	new->next = NULL;
	tetro->next = new;
	new->prev = tetro;
	new = NULL;
	return (tetro);
}

void	init_tetro_chain(t_tetro *tetro)
{
	int	i = 0;

	tetro->prev = NULL;
	while (i < 4)
	{
		tetro->x = 0;
		tetro->y = 0;
		tetro = add_list_back(tetro);
		tetro->next->prev = tetro;
		tetro = tetro->next;
		i++;
	}
}

void	free_left(t_tetris *tetris, t_tetro *tetro)
{
	int	i = 0;
	t_tetro	*head;

	head = tetro;	
	while (tetris->area[i])
	{
		free(tetris->area[i]);
		i++;
	}
	free(tetris->area);
	free(tetris);
	while (tetro->next)
	{
		head = tetro;
		tetro = tetro->next;
		free(head);
	}
	free(tetro);
}

void	determ_new_tetro(t_tetro *tetro, t_tetris *tetris)
{
	srand(time(NULL));
	tetris->y = 0;
	tetris->x = rand() % 12;
	tetris->tetro_rotat = 0;
	//tetris->tetro_type = min + rand() % (max - min);
	tetris->tetro_type = 1;
}

void	clear_previous_tetro_location(t_tetro *tetro, t_tetris *tetris)
{ while (tetro->next)
	{
		tetris->area[tetro->y][tetro->x] = '.';
		tetro = tetro->next;
	}	
}

void	print_tetro_on_board(t_tetris *tetris, t_tetro *tetro, WINDOW *win)
{
	int	y = 0;
	if (tetris->tetro_grounded == 0)
	{
	while (tetro->next)
	{
		tetris->area[tetro->y][tetro->x] = 'X';
		tetro = tetro->next;
	}
	}
	else if (tetris->tetro_grounded == 1)
	{
	while (tetro->next)
	{
		tetris->area[tetro->y][tetro->x] = 'O';
		tetro = tetro->next;
	}
	}
		
	while (tetris->area[y])
	{
		mvwprintw(win, y + 1, 1, "%s", tetris->area[y]);
		y++;
	}
}

void	get_tetro_location(t_tetro *tetro, t_tetris *tetris)
{
	if (tetris->tetro_type == 1 && tetris->tetro_rotat == 0)
		create_bar_tetro_0(tetro, tetris);	
	else if (tetris->tetro_type == 1 && tetris->tetro_rotat == 1)
		create_bar_tetro_1(tetro, tetris);
	tetris->y += 1;
}

int	check_if_move_left_possible(t_tetro *tetro, t_tetris *tetris)
{
	while (tetro->next)
	{
		if (tetro->x - 1 < 0 || tetris->area[tetro->y][tetro->x - 1] == 'O')
			return (0);
		tetro = tetro->next;
	}
	return (1);
}

int	check_if_move_right_possible(t_tetro *tetro, t_tetris *tetris)
{
	while (tetro->next)
	{
		if(tetro->x + 1 > 11 || tetris->area[tetro->y][tetro->x + 1] == 'O')
			return (0);
		tetro = tetro->next;
	}
	return (1);
}


void	check_input(int input, t_tetris *tetris, t_tetro *tetro)
{
	if (input == KEY_LEFT && check_if_move_left_possible(tetro, tetris) == 1)
	{
		tetris->x -= 1;
		tetris->y -= 1;
	}
	else if (input == KEY_RIGHT && check_if_move_right_possible(tetro, tetris) == 1)
	{
		tetris->x += 1;
		tetris->y -= 1;
	}
	else if (input == KEY_UP)
	{
		tetris->rotating = 1;
		tetris->tetro_rotat += 1;
		if ((tetris->tetro_type == 1 || tetris->tetro_type == 6 || tetris->tetro_type == 7) && tetris->tetro_rotat == 2)
			tetris->tetro_rotat = 0;
		else if (tetris->tetro_type >= 3 && tetris->tetro_type <= 5 && tetris->tetro_rotat == 4)
			tetris->tetro_rotat = 0;
	}
}

int	main(void)
{
	WINDOW		*win;
	t_tetris	*tetris;
	t_tetro		*tetro;
	int		input;

	initscr();
	cbreak();
	noecho();
	curs_set(0);
	keypad(stdscr, TRUE);
	tetris = (t_tetris*)malloc(sizeof(t_tetris));
	tetro = (t_tetro*)malloc(sizeof(t_tetro));
	create_area(tetris);
	init_tetro_chain(tetro);
	getch();
	nodelay(stdscr, TRUE);
	win = newwin(HEIGHT + 2, WIDTH + 2, LINES / 2 - HEIGHT / 2, COLS / 2 - WIDTH / 2);
	box(win, ACS_VLINE, ACS_HLINE);
	clear();
	refresh();
	while (tetris->lost == 0)
	{
		if (tetris->tetro_grounded == 1)
			determ_new_tetro(tetro, tetris);
		else
			clear_previous_tetro_location(tetro, tetris);
		get_tetro_location(tetro, tetris);
		tetris->rotating = 0;
		if (tetris->lost == 1)
		{
			printw("lost apres get_loc\n");
			refresh();
			endwin();
			exit(0);
		}
		print_tetro_on_board(tetris, tetro, win);
		wrefresh(win);
		input = getch();
		check_input(input, tetris, tetro);
		timeout(200);
	}

	free_left(tetris, tetro);
	endwin();
	return (0);
}
