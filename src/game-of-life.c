#include "game-of-life.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct game_of_life {
	cell *main_grid;
	cell *aux_grid;
	long int rows, columns;
};

void turn(Game_of_life *game)
{
	long int rows, columns, row, column;
	cell *aux;
	if (!game || !game->main_grid || !game->aux_grid || game->rows < 1 || game->columns < 1)
		return;

	rows = game->rows;
	columns = game->columns;

	for (row = 0; row < rows; ++row) {
		for (column = 0; column < columns; ++column) {
			unsigned char alive_neighbours = 0;
			long int n_row, n_column;
			/*
			 * upleft =		row - 1,	column - 1
			 * up =			row - 1,	column
			 * upright =	row - 1,	column + 1
			 * left =		row,		column - 1
			 * right =		row,		column + 1
			 * downleft =	row + 1,	column - 1
			 * down =		row + 1,	column
			 * downright =	row + 1,	column + 1
			 */

			for (n_row = row - 1; n_row < row + 2; ++n_row) {
				for (n_column = column - 1; n_column < column + 2; ++n_column) {
					if (n_row == row && n_column == column) continue;
					if (n_row < 0 || n_row >= rows) continue;
					if (n_column < 0 || n_column >= columns) continue;

					if (game->main_grid[n_row * columns + n_column] == ALIVE)
						++alive_neighbours;
				}

			}

			if (game->main_grid[row * columns + column] == ALIVE) {
				if (alive_neighbours == 2 || alive_neighbours == 3)
					game->aux_grid[row * columns + column] = ALIVE;
				else
					game->aux_grid[row * columns + column] = DEAD;
			} else {
				if (alive_neighbours == 3)
					game->aux_grid[row * columns + column] = ALIVE;
				else
					game->aux_grid[row * columns + column] = DEAD;
			}

		}
	}

	aux = game->main_grid;
	game->main_grid = game->aux_grid;
	game->aux_grid = aux;
}

Game_of_life *create_game(cell *grid, long int rows, long int columns)
{
	Game_of_life *game;
	if (!grid || rows < 1 || columns < 1) goto fail_1;

	game = (Game_of_life *)malloc(sizeof(*game));
	if (!game) goto fail_1;

	game->main_grid = (cell *)malloc(rows*columns * sizeof(cell));
	if (!game->main_grid) goto fail_2;
	memcpy(game->main_grid, grid, rows*columns * sizeof(cell));

	game->aux_grid = (cell *)calloc(rows*columns, sizeof(cell));
	if (!game->aux_grid) goto fail_3;

	game->rows = rows;
	game->columns = columns;

	return game;

fail_3:
	free(game->main_grid);
fail_2:
	free(game);
fail_1:
	return NULL;
}

void destroy_game(Game_of_life *game)
{
	if (!game) return;

	if (game->main_grid)
		free(game->main_grid);

	if (game->aux_grid)
		free(game->aux_grid);

	free(game);
}

cell *get_grid(Game_of_life *game, long int *rows, long int *columns)
{
	if (!game || !game->main_grid || game->rows < 1 || game->columns < 1) return NULL;
	*rows = game->rows;
	*columns = game->columns;
	return game->main_grid;
}

void print_game(Game_of_life *game)
{
	long int rows, columns, row, col;
	if (!game || !game->main_grid || !game->aux_grid || game->rows < 1 || game->columns < 1)
		return;

	rows = game->rows;
	columns = game->columns;

	for (row = 0; row < rows; ++row) {
		for (col = 0; col < columns; ++col) {
			printf("%s ", game->main_grid[row * columns + col] == ALIVE ? "#" : " ");
		}
		printf("\n");
	}

	for (col = 0; col < columns; ++col) {
		printf("- ");
	}

	printf("\n");

}

