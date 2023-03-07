#include "/Users/rolfharing/Documents/Codam/thuiswerkenaanschool/cub3d_github/includes/cub3D.h"

void draw_vertical_line(t_vars *vars, int x, int color)
{
    int i;

    i = vars->ray.drawstart;
    while (i < vars->ray.drawend)
    {
        mlx_put_pixel(vars->display, x, i, color);
        i++;
    }
}

void get_vertical_line_height(t_vars *vars, int h)
{
    vars->ray.lineheight = (int)(h / vars->ray.reflect_from_wall);

    // Calculate lowest and highest pixel to fill in current stripe
    vars->ray.drawstart = (-vars->ray.lineheight / 2) + (h / 2);
    if (vars->ray.drawstart < 0)
        vars->ray.drawstart = 0;
    vars->ray.drawend = (vars->ray.lineheight / 2) + (h / 2);
    if (vars->ray.drawend >= h)
        vars->ray.drawend = h - 1;
}

void calc_line_back_to_plane(t_vars *vars)
{
    if (vars->ray.side == 0)
        vars->ray.reflect_from_wall = ((vars->ray.map_x - vars->ray.pos_x + (1 - vars->ray.step_x) / 2) / vars->ray.ray_dir_x);
    else
        vars->ray.reflect_from_wall = ((vars->ray.map_y - vars->ray.pos_y + (1 - vars->ray.step_y) / 2) / vars->ray.ray_dir_y);
}

void setcolor(int side, int *color)
{
    if (side == 1)
        *color = 0xFF8D00FF;
    else
        *color = 0xFF0000FF;
}

void dda_algoritm(t_vars *vars)
{
    vars->ray.hit = 0;
    while (vars->ray.hit == 0)
    {
        // jump to next map square, in x or y direction
        if (vars->ray.side_dist_x < vars->ray.side_dist_y)
        {
            vars->ray.side_dist_x += vars->ray.delta_dist_x;
            vars->ray.map_x += vars->ray.step_x;
            vars->ray.side = 0;
        }
        else
        {
            vars->ray.side_dist_y += vars->ray.delta_dist_y;
            vars->ray.map_y += vars->ray.step_y;
            vars->ray.side = 1;
        }
        // // check if ray has hit a wall
        if (vars->map.map[vars->ray.map_x][vars->ray.map_y] == '1')
            vars->ray.hit = 1;
    }
}

void calc_ray_position_direction(t_vars *vars, int x, int w)
{
    vars->ray.camera_x = 2 * x / (float)w - 1;
    vars->ray.ray_dir_x = vars->ray.dir_x + vars->ray.plane_x * vars->ray.camera_x;
    vars->ray.ray_dir_y = vars->ray.dir_y + vars->ray.plane_y * vars->ray.camera_x;
    vars->ray.map_x = (int)vars->ray.pos_x;
    vars->ray.map_y = (int)vars->ray.pos_y;
}

void calc_ray_lenght_to_add(t_vars *vars)
{
    if (vars->ray.ray_dir_x == 0)
        vars->ray.ray_dir_x = 1e30;
    vars->ray.delta_dist_x = sqrt(1 + (vars->ray.ray_dir_y * vars->ray.ray_dir_y) / (vars->ray.ray_dir_x * vars->ray.ray_dir_x));
    if (vars->ray.ray_dir_y == 0)
        vars->ray.ray_dir_y = 1e30;
    vars->ray.delta_dist_y = sqrt(1 + (vars->ray.ray_dir_x * vars->ray.ray_dir_x) / (vars->ray.ray_dir_y * vars->ray.ray_dir_y));
}

void calc_initial_ray_length(t_vars *vars)
{
    if (vars->ray.ray_dir_x < 0)
    {
        vars->ray.step_x = -1;
        vars->ray.side_dist_x = (vars->ray.pos_x - vars->ray.map_x) * vars->ray.delta_dist_x;
    }
    else
    {
        vars->ray.step_x = 1;
        vars->ray.side_dist_x = (vars->ray.map_x + 1 - vars->ray.pos_x) * vars->ray.delta_dist_x;
    }
    if (vars->ray.ray_dir_y < 0)
    {
        vars->ray.step_y = -1;
        vars->ray.side_dist_y = (vars->ray.pos_y - vars->ray.map_y) * vars->ray.delta_dist_y;
    }
    else
    {
        vars->ray.step_y = 1;
        vars->ray.side_dist_y = (vars->ray.map_y + 1 - vars->ray.pos_y) * vars->ray.delta_dist_y;
    }
}

void setup_display(t_vars *vars)
{
    mlx_delete_image(vars->mlx, vars->display);
    vars->display = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
    if (!vars->display)
        ft_error("failed to allocate image", 4);
    draw_background(vars->display, HEIGHT / 2, 0, 1232323);
    draw_background(vars->display, HEIGHT, HEIGHT / 2, vars->floor_rgb);
}

void raycaster(t_vars *vars)
{
    int x;
    int w;
    int color;

    x = 0;
    w = WIDTH;
    setup_display(vars);
    while (x < w)
    {
        // Calculate ray position and direction
        calc_ray_position_direction(vars, x, w);
        // Wich box of the map are we in
        // vars->ray.map_x = (int)vars->ray.pos_x;
        // vars->ray.map_y = (int)vars->ray.pos_y;
        // calculate lengt of ray from one x or y-side to next x or y-side
        calc_ray_lenght_to_add(vars);
        // calculate step and initial side_dist
        // side_dist is the distance from the ray starting posisiont to the first side x or y
        calc_initial_ray_length(vars);
        // vars->ray.hit = 0;
        // DDA algoritm
        dda_algoritm(vars);
        // Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
        // hit to the camera plane. Euclidean to center camera point would give fisheye effect!
        // This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
        // for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
        // because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
        // steps, but we subtract deltaDist once because one step more into the wall was taken above.
        calc_line_back_to_plane(vars);
        // Calculate heigt of line to draw on screen
        // Calculate lowest and highest pixel to fill in current stripe
        get_vertical_line_height(vars, HEIGHT);
        setcolor(vars->ray.side, &color);
        draw_vertical_line(vars, x, color);
        x++;
    }
    mlx_image_to_window(vars->mlx, vars->display, 0, 0);
}
