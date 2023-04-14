#include <stdbool.h>
#include "map.h"

#define MAP_ROWS 1
#define MAP_COlUMNS 1
#define TILE_WIDTH 1
#define TILE_HIGHT 1
#define FORBIDDEN_TILES 1

static int map_grid[MAP_ROWS][MAP_COlUMNS] = {};

int get_number_of_rows_in_map()
{
    return MAP_ROWS;
}
int get_number_of_columns_in_map()
{
    return MAP_COlUMNS;
}
int get_the_width_of_the_tiles()
{
    return TILE_WIDTH;
}

int get_the_height_of_the_tiles()
{
    return TILE_HIGHT;
}

int get_tile_information(int x, int y)
{
    return map_grid[x][y];
}

bool encounters_forbidden_tile(int x, int y)
{
    int tile_X = (y+8) >> 3;
    int tile_Y = (y+8) >> 3;

    if (map_grid[tile_X][tile_Y] >= FORBIDDEN_TILES)
    {
        return true;
    }
    else
    {
        return false;
    }
}