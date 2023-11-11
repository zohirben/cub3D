/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:48:07 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/11/11 21:13:08 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char **lst_to_2darr(t_list *lst)
{
    char **map;
    int len;
    int i;

    i = 0;
    len = ft_lstsize(lst);
    map = malloc((len + 1) * sizeof(char *));
    if (!map)
        return (0);
    while (lst)
    {
        map[i] = ft_strdup(lst->content);
        i++;
        lst = lst->next;
    }
    map[i] = NULL;
    return (map);
}
void read_2d(char **array)
{
    while (*array != NULL)
    {
        printf("%s\n", *array);
        array++;
    }
}

void make_map(t_data *data, int fd)
{
    char *line;
    t_list *map_read;

    map_read = NULL;
    line = get_next_line(fd);
    data->width = ft_strlen(line) - 1;
    while (line)
    {
        ft_lstadd_back(&map_read, ft_lstnew(line));
        line = get_next_line(fd);
    }
    data->map = lst_to_2darr(map_read);
    data->height = ft_lstsize(map_read);
}
void mlx_draw_line(t_data *data, int x1, int y1, int x2, int y2, uint32_t color)
{
    data->dda->dx = abs(x2 - x1);
    data->dda->dy = -abs(y2 - y1);
    data->dda->sx = x1 < x2 ? 1 : -1;
    data->dda->sy = y1 < y2 ? 1 : -1;
    data->dda->err = data->dda->dx + data->dda->dy;
    while (1)
    {
        if (x1 < WIDTH && y1 < HEIGHT && x1 > 0 && y1 > 0)
            mlx_put_pixel(data->img, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        data->dda->e2 = 2 * data->dda->err;
        if (data->dda->e2 >= data->dda->dy)
        {
            data->dda->err += data->dda->dy;
            x1 += data->dda->sx;
        }
        if (data->dda->e2 <= data->dda->dx)
        {
            data->dda->err += data->dda->dx;
            y1 += data->dda->sy;
        }
    }
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}


void find_player(t_data *data)
{
    int i;
    int j;

    i = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j] && data->map[i][j] != '\n')
        {
            if (data->map[i][j] == 'P')
            {
                data->player = assign_player(j, i, get_rgba(20, 100, 93, 255));
                break;
            }
            j++;
        }
        i++;
    }
}

t_player *assign_player(int x, int y, int color)
{
    t_player *player;

    player->x = x;
    player->y = y;
    return (player);
}