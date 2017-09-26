#ifndef BATTLESHIP_PA6
#define BATTLESHIP_PA6

/*Standard Libraries Included*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/*Macro Constants*/
#define ROWS 11
#define COLUMNS 11
#define LABEL_COLUMN 0
#define LABEL_ROW 0
#define USER 0
#define COMPUTER 1
#define CARRIER_SIZE 5
#define B_SHIP_SIZE 4
#define CRUISER_SIZE 3
#define SUB_SIZE 3
#define DESTR_SIZE 2
#define SHIPS 5
#define SHIP_MUST_HAVE_SUNK 100
#define HITS_NEED_TO_WIN 17

/*Defined Data Types*/
typedef enum menu
{
	MANUAL = 1, RANDOM
} Menu;
typedef enum boolean
{
	FALSE, TRUE
} Boolean;
typedef enum ship
{
	CARRIER, BATTLESHIP, CRUISER, SUBMARINE, DESTROYER
} Ship;
typedef enum shot
{
	HIT, MISS, SUNK, NOT_SUNK, PRINTED_TO_FILE
} Shot;
typedef struct game_stats
{
	int number_of_hits;
	int number_of_misses;
	int total_shots;
	double hit_miss_ratio;
} Game_Stats;

/*Function Prototypes/Declarations*/

/**************************************************************************
* Function: welcome_screen
* Description: This function prints off the rules of Battleship! This is
			   the first screen the user sees once he/she runs the program.
* Input parameters: Text file with rules on it.
* Returns: Nothing
* Preconditions: File was opened successfully.
* Postconditions: Rules are printed to the screen.
**************************************************************************/
void welcome_screen(FILE *rules);

/**************************************************************************
* Function: initialize_game_board
* Description: This function initializes a 'rows' x 11 2-D character array
			   to all '~' except for the first row/column. The function
			   initializes the first row to the letters 'A' through 'J'
			   and the first column to numbers 0-9.
* Input parameters: Board Array, # of rows, # of columns
* Returns: Nothing
* Preconditions: Char Board must be referring to contiguous memory.
* Postconditions: All of board's values are initialized/modified.
**************************************************************************/
void initialize_game_board(char board[][COLUMNS], int rows, int columns);

/**************************************************************************
* Function: select_who_starts_first
* Description: This function simply generates a random number between 0
			   and 1 as assigns it to where player_flg_ptr points. 0 is
			   representative of the user. 1 is the computer.
* Input parameters: variable that points to the integer, player_flg
* Returns: Nothing
* Preconditions: player_flg_ptr is a valid address
* Postconditions: plyr_flag is set to 0 or 1
**************************************************************************/
void select_who_starts_first(int *player_flg_ptr);

/**************************************************************************
* Function: display_board
* Description: This function prints off the entries of a 2-D char array
			   to the screen in a row/column format. If int "player"
			   is an integer signifying "user", the user will get to see
			   all of the entries. If the int "player" is the "cptr",
			   the user will only get to see his/her hits & misses.
* Input parameters: Board Array, # of rows, # of columns, Int Player
				    Signifier
* Returns: Nothing
* Preconditions: Char Board must be referring to contiguous memory
* Postconditions: Char Board values are displayed to screen, with
				  limitations based on the "player" signifier.
**************************************************************************/
void display_board(char board[][COLUMNS], int rows, int columns, int player);

/**************************************************************************
* Function: manual_or_rand
* Description: This function prompts the user to select an option either to
			   enter his/her ships manually or to have the computer
			   randomly do it. Menu_option will only be modified to 
			   RANDOM or MANUAL (nothing else).
* Input parameters: Pointer to Menu menu_option
* Returns: Nothing
* Preconditions: menu_option_ptr is a valid address
* Postconditions: menu_option is indirectly modified
**************************************************************************/
void manual_or_rand(Menu *menu_option_ptr);

/**************************************************************************
* Function: manually_place_ships_on_board
* Description: This function prompts the user to place his/her ships on
			   the board. Each time, the program will check to make sure
			   that his/her selections are valid entries on the board
* Input parameters: Board Array, # of rows, # of columns, ship_array
					string (w/ letters representing ships in order), 
					ship_size array (w/ lengths of ships in order),
					ship_names array (strings of ship names in order)
* Returns: Nothing
* Preconditions: Char Board, ship_size_array, and ship_names must be 
				 referring to contiguous memory. Ship_array is a string.
* Postconditions: The five ships are "placed" on the board.
**************************************************************************/
void manually_place_ships_on_board(char board[][COLUMNS], int rows, int columns,
	char *ship_array, int *ship_size_array, char ship_names[][12]);

/**************************************************************************
* Function: dont_override_ships
* Description: This function returns FALSE if the desired placement of the
			   ship (w/ starting coordinate rand_row, rand_column) will
			   override another ship that is already in place. Otherwise,
			   TRUE is returned.
* Input parameters: Board Array, row_selected, col_selected, direction of
					ship placement (0 is horizontal, 1 is vertical), and
					the length of the ship
* Returns: A Boolean value (TRUE or FALSE)
* Preconditions: Char Board must be referring to contiguous memory.
* Postconditions: None
**************************************************************************/
Boolean dont_override_ships(int dir, int rand_column, int rand_row,
	char board[][COLUMNS], int ship_len);

/**************************************************************************
* Function: rand_place_ship_on_board
* Description: This function randomly places the five ships on the board
			   such that none of the ships go outside the boundary, and
			   also so that they won't override another ship.
* Input parameters: Board Array,  # rows, # columns, Ship_array string,
					Ship which_ship (used_as_index), ship_length
* Returns: Nothing
* Preconditions: Char Board must be referring to contiguous memory &
				 ship_array refers to a string
* Postconditions: A single ship (which_ship) is placed on the board.
**************************************************************************/
void rand_place_ship_on_board(char board[][COLUMNS], int rows,
	int columns, int ship_len, char *ship_array, Ship which_ship);

/**************************************************************************
* Function: randomly_place_ships_on_board
* Description: This function places all 5 ships onto the board by using the
			   rand_place_ship_on_board function and iterating over a loop
* Input parameters: Board Array, # of rows, # of columns, ship_array
					string, ship_size integral array
* Returns: Nothing
* Preconditions: Char Board & ship_size_array must be referring to 
				 contiguous memory. Ship_array is a string.
* Postconditions: All five ships are randomly placed onto board.
**************************************************************************/
void randomly_place_ships_on_board(char board[][COLUMNS], int rows,
	int columns, char *ship_array, int *ship_size_array);

/**************************************************************************
* Function: select_target
* Description: This function prompts the user for a target on the board if
			   the player_flg is the user. Otherwise, a target is randomly
			   selected for the computer.
* Input parameters: Board Array, pointers to the row_selected &
					col_selected, int player_flag (USER or CPTR)
* Returns: Nothing
* Preconditions: Char Board must be referring to contiguous memory. Row_ptr
				 and col_ptr must be valid addresses.
* Postconditions: Row & Col selections are indirectly modified
**************************************************************************/
void select_target(char board[][COLUMNS], int *row_ptr, int *col_ptr,
	int player_flg);

/**************************************************************************
* Function: check_shot
* Description: This function checks the other player's board to see if
			   the target selected contained a ship character. If so,
			   HIT is returned. Otherwise, MISS is returned.
* Input parameters: Board Array, row_selected, col_selected
* Returns: Nothing
* Preconditions: Char Board must be referring to contiguous memory.
* Postconditions: HIT or MISS returned.
**************************************************************************/
Shot check_shot(char board[][COLUMNS], int row_select, int col_select);

/**************************************************************************
* Function: check_if_sunk_ship
* Description: This function checks to see if a ship was "sunk" (i.e. the
			   ship's representative letters no longer exist on the board).
			   If the ship was sunk, a message is printed off saying which
			   ship was sunk. Additionally, sunk_o_not array is updated to 
			   SUNK so that it won't print off a message every time.
* Input parameters: Character Array, # of rows, # of columns, ship_array
					string, integral ship_size array (in correct order), 
					ship_sunk_o_not array from opposing player, ship_name
					array (in correct order).
* Returns: Nothing
* Preconditions: Char Board & ship_sunk_o_not must be referring to 
				 contiguous memory. Ship_names is an array of strings, and
				 ship_array is a string (of the ship letters, in order).
* Postconditions: A message is printed off if a ship is sunk, and the 
				  corresponding ship in sunk_o_not is updated to SUNK. 
				  Otherwise, nothing is done.
**************************************************************************/
void check_if_sunk_ship(char board[][COLUMNS], int rows, int columns,
	char *ship_array, int *ship_size_array, Ship sunk_o_not[],
	char ship_names[][12]);

/**************************************************************************
* Function: update_board
* Description: This function updates the opposing player's board with
			   either an 'm' or '*' based on whether the shot_taken
			   was a hit or miss.
* Input parameters: Board Array, row_selected, col_selected, shot_taken
* Returns: Nothing
* Preconditions: Char Board must be referring to contiguous memory.
* Postconditions: The target selected is modified to either '*' or 'm'
**************************************************************************/
void update_board(Shot shot_taken, int row_select, int col_select,
	char board[][COLUMNS]);

/**************************************************************************
* Function: is_winner
* Description: This function determines whether or not a winner exists. If
			   there are 17 (hits needs to win) '*'s on the board, then
			   a winner must exist. In this case, TRUE is returned.
			   Otherwise, FALSE is returned.
* Input parameters: Board Array, # of rows, # of columns
* Returns: Nothing
* Preconditions: Char Board must be referring to contiguous memory.
* Postconditions: FALSE or TRUE is returned.
**************************************************************************/
Boolean is_winner(char board[][COLUMNS], int rows, int columns);

/**************************************************************************
* Function: output_current_move
* Description: This function prints off a short line to battle_log about
			   the move that just occurred. Every line includes the player
			   (1 or 2), the shot_taken (EX: 4, A), whether or not the shot
			   was a hit or miss, and if there was a ship sunk, then the name
			   of the ship. Additionally, the plyr_stat struct for the player
			   is updated with what happened (hit/miss/shot).
* Input parameters: Board Array, pointer to Game_stats struct, shot_taken,
					row_selected, col_selected, the file wished to be output
					to, which player (USER or COMPUTER), sunk_or_not array of
					opposing player, array of strings (of ship names)
* Returns: Nothing
* Preconditions: Char Board & sunk_or_not must be referring to contiguous 
				 memory. Ship_names is an array of strings, and battle_log
				 was opened successfully.
* Postconditions: The current move is "written" to battle_log.
**************************************************************************/
void output_current_move(Game_Stats *plyr_stat_ptr, Shot hit_or_miss,
	int row_select, int col_select, FILE *battle_log, int plyr_flag,
	Ship sunk_or_not[], char ship_names[][12]);

/**************************************************************************
* Function: output_stats
* Description: This function prints off game statistics for a given player's
			   game_stats struct. Included are: total hits, total misses,
			   total shots taken, & hits/misses ratio
* Input parameters: Character Array, player's Game_Stats struct, plyr_flag
* Returns: Nothing
* Preconditions: battle_log was opened successfully.
* Postconditions: Game Statistics are printed to battle_log
**************************************************************************/
void output_stats(FILE *battle_log, Game_Stats plyr, int plyr_flag);

#endif