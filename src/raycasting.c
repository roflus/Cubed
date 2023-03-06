#include "/Users/rolfharing/Documents/Codam/thuiswerkenaanschool/cub3d_github/includes/cub3D.h"

void put(mlx_image_t *img)
{
    int i;
    int k;

    i = 0;
    while (i < 12)
    {
        k = 0;
        while (k < 12)
        {
            mlx_put_pixel(img, k, i, 0x7D2AFA);
            k++;
        }
        i++;
    }
}

void raycaster(t_vars *vars)
{
    int x;
    int w;

    x = 0;
    w = WIDTH;
    mlx_image_t *muur;

    mlx_delete_image(vars->mlx, vars->display);
    // mlx_delete_image(vars->mlx, muur);
    // muur = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
    vars->display = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
    if (!vars->display)
        ft_error("failed to allocate image", 4);
    draw_background(vars->display, HEIGHT / 2, 0, 1232323);
    draw_background(vars->display, HEIGHT, HEIGHT / 2, vars->floor_rgb);
    while (x < w)
    {

        // Calculate ray position and direction
        vars->ray.camera_x = 2 * x / (float)w - 1;
        vars->ray.ray_dir_x = vars->ray.dir_x + vars->ray.plane_x * vars->ray.camera_x;
        vars->ray.ray_dir_y = vars->ray.dir_y + vars->ray.plane_y * vars->ray.camera_x;

        // Wich box of the map are we in
        vars->ray.map_x = (int)vars->ray.pos_x;
        vars->ray.map_y = (int)vars->ray.pos_y;
        // calculate lengt of ray from one x or y-side to next x or y-side
        if (vars->ray.ray_dir_x == 0)
            vars->ray.ray_dir_x = 1e30;
        vars->ray.delta_dist_x = sqrt(1 + (vars->ray.ray_dir_y * vars->ray.ray_dir_y) / (vars->ray.ray_dir_x * vars->ray.ray_dir_x));
        if (vars->ray.ray_dir_y == 0)
            vars->ray.ray_dir_y = 1e30;
        vars->ray.delta_dist_y = sqrt(1 + (vars->ray.ray_dir_x * vars->ray.ray_dir_x) / (vars->ray.ray_dir_y * vars->ray.ray_dir_y));

        // calculate step and initial side_dist
        // side_dist is the distance from the ray starting posisiont to the first side x or y
        vars->ray.hit = 0;
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

        // DDA algoritm
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
            // printf("\neerste mapx: %i", vars->ray.map_x);
            // // check if ray has hit a wall
            // misshieen omdraaien x en y?
            if (vars->map.map[vars->ray.map_x][vars->ray.map_y] == '1')
                vars->ray.hit = 1;
            // printf("\nvars->ray.step_x; %i\n", vars->ray.step_x);
            // printf("\nmap posittie : x%i  \n y: %i", vars->ray.map_x, vars->ray.map_y);
            // print_map(vars);
        }

        // printf("\nmap posittie : x%i  \n y: %i", vars->ray.map_x, vars->ray.map_y);
        // printf("mapmap[][] :%c\n", vars->map.map[2][2]);
        // print_map(vars);

        // Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
        // hit to the camera plane. Euclidean to center camera point would give fisheye effect!
        // This can be computed as (mapX - posX + (1 - stepX) / 2) / rayDirX for side == 0, or same formula with Y
        // for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
        // because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
        // steps, but we subtract deltaDist once because one step more into the wall was taken above.
        if (vars->ray.side == 0)
            vars->ray.perp_wall_dist = (vars->ray.side_dist_x - vars->ray.delta_dist_x);
        else
            vars->ray.perp_wall_dist = (vars->ray.side_dist_y - vars->ray.delta_dist_y);

        // Calculate heigt of line to draw on screen
        int h = HEIGHT;
        vars->ray.lineheight = (int)(h / vars->ray.perp_wall_dist);

        // Calculate lowest and highest pixel to fill in current stripe
        vars->ray.drawstart = (-vars->ray.lineheight / 2) + (h / 2);
        if (vars->ray.drawstart < 0)
            vars->ray.drawstart = 0;
        vars->ray.drawend = (vars->ray.lineheight / 2) + (h / 2);
        if (vars->ray.drawend >= h)
            vars->ray.drawend = h - 1;
        // drawpixel
        // vars->ray.drawend -= 50;
        // printf("stest: %i\n", vars->ray.side);
        int color = 0xFF0000FF;
        if (vars->ray.side == 1)
        {
            // printf("kom je hier");
            color = 0xFF8D00FF;
        }
        int i = vars->ray.drawstart;
        // vars->ray.drawend += 50;
        while (i < vars->ray.drawend)
        {
            mlx_put_pixel(vars->display, x, i, color);
            i++;
        }
        x++;
    }
    mlx_image_to_window(vars->mlx, vars->display, 0, 0);
    // mlx_image_to_window(vars->mlx, muur, 0, 0);
    // image to window
}
