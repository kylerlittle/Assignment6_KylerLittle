#include "battleship.h"

void welcome_screen(FILE *rules)
{
	putchar('\n');
	char text_print[40] = { '\0' };
	while (!feof(rules))
	{
		fgets(text_print, 40, rules);
		fputs(text_print, stdout);
	}
	printf("\n\n\t\t");
	system("pause");
	system("cls");
}
void initialize_game_board(char board[][COLUMNS], int rows, int columns)
{
	int row_i = 0, column_i = 0, label_i = 0;
	char letter = 'A', number_label = '0';
	for (row_i = 0, label_i = 1; row_i < rows; ++row_i,
		++label_i, (int)number_label++)
	{
		if (label_i < rows)
		{
			board[label_i][LABEL_COLUMN] = number_label;
		}
		for (column_i = 1; column_i < columns; ++column_i, (int)letter++)
		{
			if (row_i == LABEL_ROW)  //initial label row (top row)
			{
				board[LABEL_ROW][column_i] = letter;
			}
			else  //remaining rows
			{
				board[row_i][column_i] = '~';
			}
		}
	}
}
void select_who_starts_first(int *player_flg_ptr)
{
	*player_flg_ptr = rand() % 2;  //player 1 is zero, comp is 1
}
void display_board(char board[][COLUMNS], int rows, int columns, int player)
{
	int row_i = 0, column_i = 0;
	char temp = '\0';
	for (row_i = 0; row_i < rows; ++row_i)
	{
		for (column_i = 0; column_i < columns; ++column_i)
		{
			if (player == COMPUTER)
			{
				if ((board[row_i][column_i] == 'c') | (board[row_i][column_i] == 'b') |
						(board[row_i][column_i] == 'r') | (board[row_i][column_i] == 's') |
						(board[row_i][column_i] == 'd'))
				{
					temp = board[row_i][column_i]; //store ship into temp
					board[row_i][column_i] = '~'; //hide ship
					printf("| %c ", board[row_i][column_i]);
					board[row_i][column_i] = temp; //put ship back in place
				}
				else
				{
					printf("| %c ", board[row_i][column_i]);
				}
			}
			else
			{
			printf("| %c ", board[row_i][column_i]);
			}
		}
		printf("|\n");
	}
}
void manual_or_rand(Menu *menu_option_ptr)
{
	printf("Plese select from the following menu:\n");
	printf("1. Enter positions of ships manually.\n");
	printf("2. Allow the program to randomly select positions of ships.\n");
	do
	{
		scanf("%d", menu_option_ptr);
	} while (*menu_option_ptr < MANUAL | *menu_option_ptr > RANDOM);
}
void manually_place_ships_on_board(char board[][COLUMNS], int rows, int columns,
	char *ship_array, int *ship_size_array, char ship_names[][12])
{
	int row = 0, col = 0, start_cell = 0, hor = 0, vert = 1;
	char col_char = '\0', dir = '\0';
	Ship i_ship = CARRIER;
	for (i_ship = CARRIER; ship_array[i_ship] != '\0'; ++i_ship)
	{
		system("cls");
		printf("\t   ******  YOUR BOARD  ****** \n");
		display_board(board, rows, columns, USER);
		printf("Would you like to place the %s horizontally or vertically? <h/v> ", ship_names[i_ship]);
		scanf(" %c", &dir);
		printf("Please select the starting cell to place it across (it will go right/down).\n");
		printf("NOTE: The %s takes up %d cells!\n", ship_names[i_ship], ship_size_array[i_ship]);
		printf("Enter like: Row <0-9> Column <A-J> \n");
		if (dir == 'h')
		{
			do
			{
				scanf(" %d %c", &row, &col_char);
				col = (int)col_char - 64; //columns correspond to ASCII - 64
				row = row + 1; //the row they choose corresponds to the next index
			} while ((col > (columns - ship_size_array[i_ship])) | col <= 0 | row <= 0 | row >= 11 |
				(dont_override_ships(hor, col, row, board, ship_size_array[i_ship]) == FALSE));
			for (start_cell = col; start_cell < (col + ship_size_array[i_ship]); ++start_cell)
			{
				board[row][start_cell] = ship_array[i_ship];
			}
		}
		else
		{
			do
			{
				scanf(" %d %c", &row, &col_char);
				col = (int)col_char - 64; //columns correspond to ASCII - 64
				row = row + 1; //same explanation as above
			} while ((row > (rows - ship_size_array[i_ship])) | col <= 0 | row <= 0 | row >= 11 |
				(dont_override_ships(vert, col, row, board, ship_size_array[i_ship]) == FALSE));
			for (start_cell = row; start_cell < (row + ship_size_array[i_ship]); ++start_cell)
			{
				board[start_cell][col] = ship_array[i_ship];
			}
		}
	}
}
Boolean dont_override_ships(int dir, int rand_column, int rand_row,
	char board[][COLUMNS], int ship_len)
{
	int i_hor = 0, i_vert = 0;
	if (dir)  //VERTICAL
	{
		for (i_hor = rand_row; i_hor < ship_len + rand_row; ++i_hor)
		{
			if (board[i_hor][rand_column] != '~')
			{
				return FALSE;
			}
		}
	}
	else   //HORIZONTAL
	{
		for (i_vert = rand_column; i_vert < ship_len + rand_column;
			++i_vert)
		{
			if (board[rand_row][i_vert] != '~')
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}
void rand_place_ship_on_board(char board[][COLUMNS], int rows,
	int columns, int ship_len, char *ship_array, Ship which_ship)
{
	int rand_column = 0, rand_row = 0, i_hor = 0, i_vert = 0, dir = 0,
		ships = SHIPS;
	Ship i_ship = 0;
	dir = rand() % 2;  //decides if vertical/horizontal placement
	if (dir)  //VERTICAL
	{
		do
		{
			rand_column = (rand() % (columns - 1)) + 1;  //column can be any if ship vertical
			rand_row = (rand() % (rows - ship_len)) + 1;  //select starting rand_row to fit on board
		} while (dont_override_ships(dir, rand_column, rand_row, board, ship_len) == FALSE);
		for (i_hor = rand_row; i_hor < ship_len + rand_row; ++i_hor)
		{
			board[i_hor][rand_column] = ship_array[which_ship];
		}
	}
	else   //HORIZONTAL
	{
		do
		{
			rand_column = (rand() % (columns - ship_len)) + 1;  //select starting rand_column to fit on board
			rand_row = (rand() % (columns - 1)) + 1;  //rand_row can be any of 1-10 if ship horizontal
		} while (dont_override_ships(dir, rand_column, rand_row, board, ship_len) == FALSE);
		for (i_vert = rand_column; i_vert < ship_len + rand_column;
			++i_vert)
		{
			board[rand_row][i_vert] = ship_array[which_ship];
		}
	}
}
void randomly_place_ships_on_board(char board[][COLUMNS], int rows,
	int columns, char *ship_array, int *ship_size_array)
{
	Ship i_ship = CARRIER;
	for (i_ship = CARRIER; ship_array[i_ship] != '\0'; ++i_ship)
	{
		rand_place_ship_on_board(board, rows, columns, ship_size_array[i_ship],
			ship_array, i_ship);
	}
}
void select_target(char board[][COLUMNS], int *row_ptr, int *col_ptr,
	int player_flg)
{
	int row_select = 0;
	char col_select = '\0';
	if (player_flg == USER)
	{
		do
		{
			printf("Please select a target: <Row (0-9) Column (A-J)>: ");
			scanf("%d %c", &row_select, &col_select);
			*row_ptr = row_select + 1; //the row they enter corresponds to next index
			*col_ptr = (int)col_select - 64; //columns correspond to ASCII - 64
		} while (board[*row_ptr][*col_ptr] == 'm' |
			board[*row_ptr][*col_ptr] == '*');  //can't do same shot twice
	}
	else //COMPUTER
	{
		do
		{
			*row_ptr = rand() % 10 + 1;  //between 1-10
			*col_ptr = rand() % 10 + 1;
		} while (board[*row_ptr][*col_ptr] == 'm' |
			board[*row_ptr][*col_ptr] == '*');
		col_select = (char)((*col_ptr) + 64);
		row_select = (*row_ptr) - 1;
		printf("Computer selects %d %c.\n", row_select, col_select);
	}
}
Shot check_shot(char board[][COLUMNS], int row_select, int col_select)
{
	char col = (char)(col_select + 64); //converts col to ASCII char
	if (board[row_select][col_select] != '~')
	{
		printf("%d %c is a hit.\n", row_select - 1, col);
		return HIT;
	}
	else
	{
		printf("%d %c is a miss.\n", row_select - 1, col);
		return MISS;
	}
}
void check_if_sunk_ship(char board[][COLUMNS], int rows, int columns,
	char *ship_array, int *ship_size_array, Ship sunk_o_not[],
	char ship_names[][12])
{
	int i_row = 0, i_col = 0;
	Ship i_ship = CARRIER;
	for (i_ship = CARRIER; ship_array[i_ship] != '\0'; ++i_ship)
	{
		int ship = 0;  //needs to reset to 0 for every ship to be checked
		for (i_row = 1; i_row < rows; ++i_row)
		{
			for (i_col = 1; i_col < columns; ++i_col)
			{
				if (board[i_row][i_col] != ship_array[i_ship])
				{
					++ship;
				}
			}
		}
		if (ship == SHIP_MUST_HAVE_SUNK && sunk_o_not[i_ship] == NOT_SUNK)
		{
			printf("%s has been sunk!\n", ship_names[i_ship]);
			sunk_o_not[i_ship] = SUNK;
		}
	}
}
void update_board(Shot shot_taken, int row_select, int col_select,
	char board[][COLUMNS])
{
	if (shot_taken == HIT)
	{
		board[row_select][col_select] = '*';
	}
	else //miss
	{
		board[row_select][col_select] = 'm';
	}
}
void output_current_move(Game_Stats *plyr_stat_ptr, Shot hit_or_miss,
	int row_select, int col_select, FILE *battle_log, int plyr_flag,
	Ship sunk_or_not[], char ship_names[][12])
{
	Ship i_ship = 0;
	char col = (char)(col_select + 64);
	if (hit_or_miss == HIT)
	{
		plyr_stat_ptr->number_of_hits += 1;
		fprintf(battle_log, "Player %d: %d, %c 'hit' ", plyr_flag + 1, row_select - 1, col);
		for (i_ship = CARRIER; i_ship < SHIPS; ++i_ship)
		{
			if (sunk_or_not[i_ship] == SUNK)
			{
				fprintf(battle_log, "Sunk the %s!", ship_names[i_ship]);
				sunk_or_not[i_ship] = PRINTED_TO_FILE;
			}
		}
		fprintf(battle_log, "\n"); //go to new line regardless
	}
	else //MISS
	{
		plyr_stat_ptr->number_of_misses += 1;
		fprintf(battle_log, "Player %d: %d, %c 'miss'\n", plyr_flag + 1, row_select - 1, col);
	}
	plyr_stat_ptr->total_shots += 1;
}
Boolean is_winner(char board[][COLUMNS], int rows, int columns)
{
	int i_row = 0, i_col = 0, hit_count = 0;
	for (i_row = 1; i_row < rows; ++i_row)
	{
		for (i_col = 1; i_col < columns; ++i_col)
		{
			if (board[i_row][i_col] == '*')
			{
				++hit_count;
			}
		}
	}
	if (hit_count == HITS_NEED_TO_WIN)
	{
		return TRUE;
	}
	return FALSE;
}
void output_stats(FILE *battle_log, Game_Stats plyr, int plyr_flag)
{
	double ratio = 0.0;
	fprintf(battle_log, "*** Player %d Stats ***\n", plyr_flag + 1);
	fprintf(battle_log, "Number Hits: %d\n", plyr.number_of_hits);
	fprintf(battle_log, "Number Misses: %d\n", plyr.number_of_misses);
	fprintf(battle_log, "Total Shots: %d\n", plyr.total_shots);
	ratio = (double)plyr.number_of_hits / plyr.number_of_misses;
	fprintf(battle_log, "Hit/Miss Ratio: %.1lf\n", ratio);
}