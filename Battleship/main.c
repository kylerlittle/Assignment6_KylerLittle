/*************************************************************************
* Programmer: Kyler Little
* Class: CptS 121; Lab Section 11
* Programming Assignment: Programming Project 6
* Date: 11/1/2016                                                                    *
* Description: This program runs the game of Battleship. The game guides
			   the user through the game until player 1 or 2 has sunk all
			   of the other player's ships. The objective of the game is 
			   to guess where the other player's ships are hidden and 
			   sink them. Additionally, once the game is over, the player 
			   can view a summary of the game in battleship.log. 
************************************************************************/

#include "battleship.h"

int main(void)
{
	/*Variable Declarations*/
	char game_board_plyr[ROWS][COLUMNS] = { '\0' },
		game_board_cptr[ROWS][COLUMNS] = { '\0' },
		*ships = "cbrsd", //we want this immutable
		ship_names[SHIPS][12] = { "Carrier", "Battleship", "Cruiser",
		"Submarine", "Destroyer" };
	int player_flag = 0, ship_lengths[SHIPS] = { CARRIER_SIZE,
		B_SHIP_SIZE, CRUISER_SIZE, SUB_SIZE, DESTR_SIZE },
		row_select = 0, col_select = 0, num_hit_plyr = 0,
		num_miss_plyr = 0, num_hit_cptr = 0, num_miss_cptr = 0;
	Menu menu_option = MANUAL;
	Boolean winner = FALSE; //NO WINNER YET
	Shot shot = HIT, sunk_or_not_plyr[SHIPS] = { NOT_SUNK, NOT_SUNK, NOT_SUNK, NOT_SUNK, NOT_SUNK },  //initialize all values to NOT_SUNK
		sunk_or_not_cptr[SHIPS] = { NOT_SUNK, NOT_SUNK, NOT_SUNK, NOT_SUNK, NOT_SUNK };
	Game_Stats stats_plyr = { 0, 0, 0, 0.0 }, stats_cptr = { 0, 0, 0, 0.0 };
	FILE *battleship_stats = fopen("battleship.log", "w"),
		*rules = fopen("rules.txt", "r");
	srand((unsigned)time(NULL)); //seed value

								 /*Game Execution*/
	welcome_screen(rules);
	initialize_game_board(game_board_plyr, ROWS, COLUMNS);
	initialize_game_board(game_board_cptr, ROWS, COLUMNS);
	manual_or_rand(&menu_option);
	if (menu_option == MANUAL)
	{
		manually_place_ships_on_board(game_board_plyr, ROWS, COLUMNS, ships,
			ship_lengths, ship_names);
		system("cls");
	}
	else
	{
		randomly_place_ships_on_board(game_board_plyr, ROWS, COLUMNS, ships,
			ship_lengths);
		printf("Your board has been generated.\n");
	}
	randomly_place_ships_on_board(game_board_cptr, ROWS, COLUMNS, ships,
		ship_lengths);
	printf("Player 2's (Computer's) board has been generated.\n");
	select_who_starts_first(&player_flag);
	printf("Player %d has been randomly selected to go first.\n\t\t", player_flag + 1);
	system("pause");
	while (winner == FALSE)
	{
		if (player_flag % 2 == USER) //USER PLAYER 
		{
			system("cls");
			printf("\n       PLAYER 2's BOARD (THE COMPUTER)     \n");
			display_board(game_board_cptr, ROWS, COLUMNS, COMPUTER);
			putchar('\n');
			select_target(game_board_plyr, &row_select, &col_select, USER);
			system("cls");
			shot = check_shot(game_board_cptr, row_select, col_select);
			update_board(shot, row_select, col_select, game_board_cptr);
			check_if_sunk_ship(game_board_cptr, ROWS, COLUMNS, ships, ship_lengths,
				sunk_or_not_cptr, ship_names);
			output_current_move(&stats_plyr, shot, row_select, col_select, battleship_stats,
				USER, sunk_or_not_cptr, ship_names);
			printf("\n       PLAYER 2's BOARD (THE COMPUTER)     \n");
			display_board(game_board_cptr, ROWS, COLUMNS, COMPUTER);
			printf("\n\t\t");
			system("pause");
			system("cls");
			winner = is_winner(game_board_cptr, ROWS, COLUMNS);
		}
		else //COMPUTER PLAYER
		{
			select_target(game_board_cptr, &row_select, &col_select, COMPUTER);
			shot = check_shot(game_board_plyr, row_select, col_select);
			update_board(shot, row_select, col_select, game_board_plyr);
			check_if_sunk_ship(game_board_plyr, ROWS, COLUMNS, ships, ship_lengths,
				sunk_or_not_plyr, ship_names);
			output_current_move(&stats_cptr, shot, row_select, col_select, battleship_stats,
				COMPUTER, sunk_or_not_plyr, ship_names);
			printf("\n\t    PLAYER 1's BOARD (YOU)\n");
			display_board(game_board_plyr, ROWS, COLUMNS, USER);
			printf("\n\t\t");
			system("pause");
			system("cls");
			winner = is_winner(game_board_plyr, ROWS, COLUMNS);
		}
		++player_flag; //changes player every time through
	}
	fprintf(battleship_stats, "Player %d wins, Player %d loses.\n\n", ((player_flag - 1) % 2) + 1, (player_flag % 2 + 1));
	output_stats(battleship_stats, stats_plyr, USER);
	fprintf(battleship_stats, "\n");
	output_stats(battleship_stats, stats_cptr, COMPUTER);
	printf("Player %d wins!\n\n", ((player_flag - 1) % 2) + 1);
	fclose(battleship_stats);
	fclose(rules);
	return 0;
}