#include <wolf3d.h>

SDL_Surface *resize_surface(t_main *main, SDL_Surface *img)
{
	SDL_Surface *new;
    int	*buffer;
	int *pixels = img->pixels;
	int newHeight;
	int newWidth;
	double ar;

	ar = (double)img->w / img->h;
	newWidth = (img->w * main->aspect_ratio) > main->width / 2 ? (img->w * main->aspect_ratio) : (img->w * main->aspect_ratio);
	newHeight = (newWidth / ar) * 3;
    newWidth *= 3;
	new = SDL_CreateRGBSurface(img->flags, newWidth, newHeight, 32, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
	buffer = new->pixels;
    int x_ratio = (int)((img->w << 16)/newWidth) + 1;
    int y_ratio = (int)((img->h << 16)/newHeight) + 1;

    int x2, y2 ;
    for (int i = 0; i < newHeight; i++) {
        for (int j = 0; j < newWidth; j++) {
            x2 = ((j * x_ratio) >> 16) ;
            y2 = ((i * y_ratio) >> 16) ;
            buffer[(i * newWidth) + j] = pixels[(y2 * img->w) + x2] ;
        }
    }
    return new;
}