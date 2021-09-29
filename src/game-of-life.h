#ifndef _GAME_OF_LIFE_H
#define _GAME_OF_LIFE_H value

typedef struct game_of_life Game_of_life;
typedef enum {DEAD = 0, ALIVE} cell;

void turn(Game_of_life *game);
Game_of_life *create_game(cell *grid, long int rows, long int columns);
void destroy_game(Game_of_life *game);
cell *get_grid(Game_of_life *game, long int *rows, long int *columns);
void print_game(Game_of_life *game);

#endif /* ifndef _GAME_OF_LIFE_H */
