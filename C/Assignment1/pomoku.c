#include "pomoku.h"

int g_board[20 * 20];

size_t g_row_size;
size_t g_column_size;

size_t g_min_board_size;
size_t g_max_board_size;

int g_black_stone_player_score;
int g_white_stone_player_score;

void init_game(void)
{
    size_t index;
    size_t entire_board_size;

    g_row_size = 15;
    g_column_size = 15;

    g_min_board_size = 10;
    g_max_board_size = 20;

    g_black_stone_player_score = 0;
    g_white_stone_player_score = 0;

    entire_board_size = g_max_board_size * g_max_board_size;
    for (index = 0; index < entire_board_size; ++index) {
        g_board[index] = -1;
    }
}

unsigned int get_row_count(void)
{
    return g_row_size;
}

unsigned int get_column_count(void)
{
    return g_column_size;
}

unsigned int get_entire_board_size(void)
{
    return g_row_size * g_column_size;
}

unsigned int get_board_index(const unsigned int row, const unsigned int col)
{
    return col * g_max_board_size + row;
}

int get_score(const color_t color)
{
    int score;
    switch (color) {
    case COLOR_BLACK:
        score = g_black_stone_player_score;
        break;
    case COLOR_WHITE:
        score = g_white_stone_player_score;
        break;
    default:
        score = -1;
        break;
    }

    return score;
}

int get_color(const unsigned int row, const unsigned int col)
{
    int color = -1;

    if (row < g_row_size && col < g_column_size) {
        color = g_board[get_board_index(row, col)];
    }

    return color;
}

int is_placeable(const unsigned int row, const unsigned int col)
{
    unsigned int board_index;

    if (row < g_row_size && col < g_column_size) {
        board_index = get_board_index(row, col);
        if (g_board[board_index] == -1) {
            return TRUE;
        } else {
            return FALSE;
        }
    }
    return FALSE;
}

int place_stone(const color_t color, const unsigned int row, const unsigned int col)
{
    int place_result = FALSE;
    unsigned int board_index;

    switch (color) {
    case COLOR_BLACK:
    case COLOR_WHITE:
        if (is_placeable(row, col)) {
            board_index = get_board_index(row, col);
            g_board[board_index] = color;

            calculate_players_score(color, row, col);
            place_result = TRUE;
        }
        break;
    default:
        assert(0);
        break;
    }
    return place_result;
}

void increase_player_score(const color_t color, const int score)
{
    switch (color) {
    case COLOR_BLACK:
        g_black_stone_player_score += score;
        break;
    case COLOR_WHITE:
        g_white_stone_player_score += score;
        break;
    default:
        assert(0);
        break;
    }
}

void decrease_player_score(const color_t color, const int score)
{
    switch (color) {
    case COLOR_BLACK:
        g_black_stone_player_score -= score;
        break;
    case COLOR_WHITE:
        g_white_stone_player_score -= score;
        break;
    default:
        assert(0);
        break;
    }
}

void calculate_players_score(const color_t color, const unsigned int row, const unsigned int col)
{
    size_t index_x;
    size_t index_y;

    int check_able_dir0;
    int check_able_dir1;

    unsigned int placed_find_index;
    unsigned int placed_stone_count;
    const unsigned int GET_ABLE_SCORE_VALUE = 4;

    placed_stone_count = 1;
    placed_find_index = 0;
    check_able_dir0 = TRUE;
    check_able_dir1 = TRUE;

    while (TRUE) {
        ++placed_find_index;
        if (check_able_dir0 == TRUE) {
            index_x = row - placed_find_index;
            if (color == get_color(index_x, col)) {
                ++placed_stone_count;
            } else {
                check_able_dir0 = FALSE;
            }

            if (index_x <= 0) {
                check_able_dir0 = FALSE;
            }
        }
        if (check_able_dir1 == TRUE) {
            index_x = row + placed_find_index;
            if (color == get_color(index_x, col)) {
                ++placed_stone_count;
            } else {
                check_able_dir1 = FALSE;
            }

            if (index_x >= g_row_size - 1) {
                check_able_dir1 = FALSE;
            }
        }
        if (check_able_dir0 == FALSE && check_able_dir1 == FALSE) {
            break;
        }
    }
    if (placed_stone_count > GET_ABLE_SCORE_VALUE) {
        increase_player_score(color, placed_stone_count - GET_ABLE_SCORE_VALUE);
    }

    placed_stone_count = 1;
    placed_find_index = 0;
    check_able_dir0 = TRUE;
    check_able_dir1 = TRUE;

    while (TRUE) {
        ++placed_find_index;
        if (check_able_dir0 == TRUE) {
            index_y = col - placed_find_index;
            if (color == get_color(row, index_y)) {
                ++placed_stone_count;
            } else {
                check_able_dir0 = FALSE;
            }

            if (index_y <= 0) {
                check_able_dir0 = FALSE;
            }
        }
        if (check_able_dir1 == TRUE) {
            index_y = col + placed_find_index;
            if (color == get_color(row, index_y)) {
                ++placed_stone_count;
            } else {
                check_able_dir1 = FALSE;
            }

            if (index_y >= g_column_size - 1) {
                check_able_dir1 = FALSE;
            }
        }
        if (check_able_dir0 == FALSE && check_able_dir1 == FALSE) {
            break;
        }
    }
    if (placed_stone_count > GET_ABLE_SCORE_VALUE) {
        increase_player_score(color, placed_stone_count - GET_ABLE_SCORE_VALUE);
    }

    placed_stone_count = 1;
    placed_find_index = 0;
    check_able_dir0 = TRUE;
    check_able_dir1 = TRUE;

    while (TRUE) {
        ++placed_find_index;
        if (check_able_dir0 == TRUE) {
            index_x = row - placed_find_index;
            index_y = col - placed_find_index;
            if (color == get_color(index_x, index_y)) {
                ++placed_stone_count;
            } else {
                check_able_dir0 = FALSE;
            }

            if (index_x <= 0 || index_y <= 0) {
                check_able_dir0 = FALSE;
            }
        }
        if (check_able_dir1 == TRUE) {
            index_x = row + placed_find_index;
            index_y = col + placed_find_index;
            if (color == get_color(index_x, index_y)) {
                ++placed_stone_count;
            } else {
                check_able_dir1 = FALSE;
            }

            if (index_x >= g_row_size - 1 || index_y >= g_column_size - 1) {
                check_able_dir1 = FALSE;
            }
        }
        if (check_able_dir0 == FALSE && check_able_dir1 == FALSE) {
            break;
        }
    }
    if (placed_stone_count > GET_ABLE_SCORE_VALUE) {
        increase_player_score(color, placed_stone_count - GET_ABLE_SCORE_VALUE);
    }

    placed_stone_count = 1;
    placed_find_index = 0;
    check_able_dir0 = TRUE;
    check_able_dir1 = TRUE;

    while (TRUE) {
        ++placed_find_index;
        if (check_able_dir0 == TRUE) {
            index_x = row + placed_find_index;
            index_y = col - placed_find_index;
            if (color == get_color(index_x, index_y)) {
                ++placed_stone_count;
            } else {
                check_able_dir0 = FALSE;
            }

            if (index_x >= g_row_size - 1 || index_y <= 0) {
                check_able_dir0 = FALSE;
            }
        }
        if (check_able_dir1 == TRUE) {
            index_x = row - placed_find_index;
            index_y = col + placed_find_index;
            if (color == get_color(index_x, index_y)) {
                ++placed_stone_count;
            } else {
                check_able_dir1 = FALSE;
            }

            if (index_x <= 0 || index_y >= g_column_size - 1) {
                check_able_dir1 = FALSE;
            }
        }
        if (check_able_dir0 == FALSE && check_able_dir1 == FALSE) {
            break;
        }
    }
    if (placed_stone_count > GET_ABLE_SCORE_VALUE) {
        increase_player_score(color, placed_stone_count - GET_ABLE_SCORE_VALUE);
    }
}

int insert_row(const color_t color, const unsigned int row)
{
    size_t row_index;
    size_t col_index;

    unsigned int raw_board_index;
    unsigned int insert_board_index;

    const int USE_SCORE = 3;

    if (g_row_size == row) {
        decrease_player_score(color, USE_SCORE);
        ++g_row_size;
        return TRUE;
    } else if (g_row_size > row && g_row_size < g_max_board_size && get_score(color) >= USE_SCORE) {
        for (col_index = 0; col_index < g_column_size; ++col_index) {
            for (row_index = g_row_size; row_index > row; --row_index) {
                raw_board_index = get_board_index(row_index - 1, col_index);
                insert_board_index = get_board_index(row_index, col_index);

                g_board[insert_board_index] = g_board[raw_board_index];
            }
        }

        for (col_index = 0; col_index < g_column_size; ++col_index) {
            raw_board_index = get_board_index(row, col_index);
            g_board[raw_board_index] = -1;
        }

        decrease_player_score(color, USE_SCORE);
        ++g_row_size;
        return TRUE;
    }

    return FALSE;
}

int insert_column(const color_t color, const unsigned int col)
{
    size_t row_index;
    size_t col_index;

    unsigned int raw_board_index;
    unsigned int insert_board_index;

    const int USE_SCORE = 3;

    if (g_column_size == col) {
        decrease_player_score(color, USE_SCORE);
        ++g_column_size;
        return TRUE;
    } else if (g_column_size > col && g_column_size < g_max_board_size && get_score(color) >= USE_SCORE) {
        for (col_index = g_column_size; col_index > col; --col_index) {
            for (row_index = 0; row_index < g_row_size; ++row_index) {
                raw_board_index = get_board_index(row_index, col_index - 1);
                insert_board_index = get_board_index(row_index, col_index);

                g_board[insert_board_index] = g_board[raw_board_index];
            }
        }

        for (row_index = 0; row_index < g_row_size; ++row_index) {
            raw_board_index = get_board_index(row_index, col);
            g_board[raw_board_index] = -1;
        }
        decrease_player_score(color, USE_SCORE);
        ++g_column_size;

        return TRUE;
    }

    return FALSE;
}

int remove_row(const color_t color, const unsigned int row)
{
    size_t row_index;
    size_t col_index;

    unsigned int raw_board_index;
    unsigned int remove_board_index;

    const int USE_SCORE = 3;

    if (g_row_size > row && g_row_size > g_min_board_size && get_score(color) >= USE_SCORE) {
        for (col_index = 0; col_index < g_column_size; ++col_index) {
            for (row_index = row; row_index < g_row_size; ++row_index) {
                raw_board_index = get_board_index(row_index + 1, col_index);
                remove_board_index = get_board_index(row_index, col_index);

                g_board[remove_board_index] = g_board[raw_board_index];
            }
        }

        decrease_player_score(color, USE_SCORE);
        --g_row_size;

        for (col_index = 0; col_index < g_column_size; ++col_index) {
            raw_board_index = get_board_index(g_row_size, col_index);
            g_board[raw_board_index] = -1;
        }

        return TRUE;
    }

    return FALSE;
}

int remove_column(const color_t color, const unsigned int col)
{
    size_t row_index;
    size_t col_index;

    unsigned int raw_board_index;
    unsigned int remove_board_index;

    const int USE_SCORE = 3;

    if (g_column_size > col && g_column_size > g_min_board_size && get_score(color) >= USE_SCORE) {
        for (col_index = col; col_index < g_column_size; ++col_index) {
            for (row_index = 0; row_index < g_row_size; ++row_index) {
                raw_board_index = get_board_index(row_index, col_index + 1);
                remove_board_index = get_board_index(row_index, col_index);

                g_board[remove_board_index] = g_board[raw_board_index];
            }
        }

        decrease_player_score(color, USE_SCORE);
        --g_column_size;

        for (row_index = 0; row_index < g_row_size; ++row_index) {
            raw_board_index = get_board_index(row_index, g_column_size);
            g_board[raw_board_index] = -1;
        }

        return TRUE;
    }

    return FALSE;
}

int swap_rows(const color_t color, const unsigned int row0, const unsigned int row1)
{
    size_t col_index;

    size_t row0_board_index;
    size_t row1_board_index;

    const int USE_SCORE = 2;

    if (g_row_size > row0 && g_row_size > row1 && row0 != row1 && get_score(color) >= USE_SCORE) {
        for (col_index = 0; col_index < g_column_size; ++col_index) {
            row0_board_index = get_board_index(row0, col_index);
            row1_board_index = get_board_index(row1, col_index);

            g_board[row0_board_index] = g_board[row0_board_index] ^ g_board[row1_board_index];
            g_board[row1_board_index] = g_board[row0_board_index] ^ g_board[row1_board_index];
            g_board[row0_board_index] = g_board[row0_board_index] ^ g_board[row1_board_index];
        }

        decrease_player_score(color, USE_SCORE);
        return TRUE;
    }

    return FALSE;
}

int swap_columns(const color_t color, const unsigned int col0, const unsigned int col1)
{
    size_t row_index;

    size_t col0_board_index;
    size_t col1_board_index;

    const int USE_SCORE = 2;

    if (g_column_size > col0 && g_column_size > col1 && col0 != col1 && get_score(color) >= USE_SCORE) {
        for (row_index = 0; row_index < g_row_size; ++row_index) {
            col0_board_index = get_board_index(row_index, col0);
            col1_board_index = get_board_index(row_index, col1);

            g_board[col0_board_index] = g_board[col0_board_index] ^ g_board[col1_board_index];
            g_board[col1_board_index] = g_board[col0_board_index] ^ g_board[col1_board_index];
            g_board[col0_board_index] = g_board[col0_board_index] ^ g_board[col1_board_index];
        }

        decrease_player_score(color, USE_SCORE);
        return TRUE;
    }

    return FALSE;
}

int copy_row(const color_t color, const unsigned int src, const unsigned int dst)
{
    int col_loop_index;

    size_t src_board_index;
    size_t dst_board_index;

    const int USE_SCORE = 4;

    if (g_row_size > src && g_row_size > dst && src != dst && get_score(color) >= USE_SCORE) {
        for (col_loop_index = 0; col_loop_index < g_column_size; ++col_loop_index) {
            src_board_index = get_board_index(src, col_loop_index);
            dst_board_index = get_board_index(dst, col_loop_index);

            g_board[dst_board_index] = g_board[src_board_index];
        }

        decrease_player_score(color, USE_SCORE);
        return TRUE;
    }

    return FALSE;
}

int copy_column(const color_t color, const unsigned int src, const unsigned int dst)
{
    int row_loop_index;

    size_t src_board_index;
    size_t dst_board_index;

    const int USE_SCORE = 4;

    if (g_column_size > src && g_column_size > dst && src != dst && get_score(color) >= USE_SCORE) {
        for (row_loop_index = 0; row_loop_index < g_row_size; ++row_loop_index) {
            src_board_index = get_board_index(row_loop_index, src);
            dst_board_index = get_board_index(row_loop_index, dst);

            g_board[dst_board_index] = g_board[src_board_index];
        }

        decrease_player_score(color, USE_SCORE);
        return TRUE;
    }
    return FALSE;
}
