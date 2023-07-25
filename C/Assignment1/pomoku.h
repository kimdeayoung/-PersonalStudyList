#ifndef POMOKU_H
#define POMOKU_H

#include "color.h"
#include <assert.h>

#define TRUE (1)
#define FALSE (0)

void init_game(void);

unsigned int get_row_count(void);

unsigned int get_column_count(void);

unsigned int get_entire_board_size(void);

unsigned int get_board_index(const unsigned int row, const unsigned int col);

int get_score(const color_t color);

int get_color(const unsigned int row, const unsigned int col);

int is_placeable(const unsigned int row, const unsigned int col);

int place_stone(const color_t color, const unsigned int row, const unsigned int col);

void increase_player_score(const color_t color, const int score);

void decrease_player_score(const color_t color, const int score);

void calculate_players_score(const color_t color, const unsigned int row, const unsigned int col);

/* special moves */
int insert_row(const color_t color, const unsigned int row);

int insert_column(const color_t color, const unsigned int col);

int remove_row(const color_t color, const unsigned int row);

int remove_column(const color_t color, const unsigned int col);

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1);

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1);

int copy_row(const color_t color, const unsigned int src, const unsigned int dst);

int copy_column(const color_t color, const unsigned int src, const unsigned int dst);

#endif /* POMOKU_H */
