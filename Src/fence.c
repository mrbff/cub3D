#include "../cub3D.h"

int flood_map(char **map, int x, int y)
{
    if (!map[x][y] || map[x][y] == 32)
        return (1);
    else if (map[x][y] == '1' || map[x][y] == 'x')
        return (0);
    else
    {
        map[x][y] = 'x';
        return
            (flood_map(map, x , y + 1) ||
            flood_map(map, x + 1, y + 1) ||
            flood_map(map, x + 1 , y) ||
            flood_map(map, x , y - 1) ||
            flood_map(map, x - 1, y - 1) ||
            flood_map(map, x - 1, y) ||
            flood_map(map, x + 1, y - 1) ||
            flood_map(map, x - 1, y + 1));
    }
}

char **matdup(char **mat)
{
    int i;
    char **dup;

    i = 0;
    while (mat[i])
        i++;
    dup = malloc(sizeof(char *) * i + 1);
    if (!dup)
        return (NULL);
    dup[i] = NULL;
    while (--i >= 0)
        dup[i] = ft_strdup(mat[i]);
    return (dup);
}

int not_fenced(char **map, int x, int y)
{
    char **dup;
    int ret;
    int i;

    ret = 0;
    dup = NULL;
    dup = matdup(map);
    if (!dup)
        return (1);
    ret = flood_map(dup, x, y);
    i = -1;
    while (dup[++i])
    {
        printf("%s\n", dup[i]);
        free(dup[i]);
    }
    free(dup);
    return (ret);
}