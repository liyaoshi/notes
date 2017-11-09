
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <linux/input.h>

#define PNG_DEBUG 3
#include <png.h>

void abort_(const char * s, ...)
{
        va_list args;
        va_start(args, s);
        vfprintf(stderr, s, args);
        fprintf(stderr, "\n");
        va_end(args);
        abort();
}

int x, y;

int width, height;

png_byte bit_depth=8;

png_structp png_ptr;
png_infop info_ptr;

png_bytep * row_pointers;
static int fbfd = -1;

char *fbp;
unsigned char *fbmmap ;
char *fbdev;
static struct fb_var_screeninfo scrinfo;

void read_png_file(void)
{
        width = scrinfo.xres_virtual;
        height = scrinfo.yres_virtual;
        row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
        for (y=0; y<height; y++)
                row_pointers[y] = (png_byte*) malloc(scrinfo.xres_virtual*4);
	for (y=0; y<height; y++)
	memcpy((unsigned char *)row_pointers[y],(unsigned char *)&fbmmap[y*width*4],scrinfo.xres_virtual*4);
}


void write_png_file(char* file_name)
{
        /* create file */
        FILE *fp = fopen(file_name, "wb");
        if (!fp)
                abort_("[write_png_file] File %s could not be opened for writing", file_name);


        /* initialize stuff */
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

        if (!png_ptr)
                abort_("[write_png_file] png_create_write_struct failed");

        info_ptr = png_create_info_struct(png_ptr);
        if (!info_ptr)
                abort_("[write_png_file] png_create_info_struct failed");

        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during init_io");

       png_init_io(png_ptr, fp);
	png_set_bgr( png_ptr );
	png_set_expand( png_ptr );

        /* write header */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing header");

        png_set_IHDR(png_ptr, info_ptr, width, height,
                     bit_depth, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE,
                     PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

        png_write_info(png_ptr, info_ptr);


        /* write bytes */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during writing bytes");

        png_write_image(png_ptr, row_pointers);


        /* end write */
        if (setjmp(png_jmpbuf(png_ptr)))
                abort_("[write_png_file] Error during end of write");

        png_write_end(png_ptr, NULL);

        /* cleanup heap allocation */
        for (y=0; y<height; y++)
                free(row_pointers[y]);
        free(row_pointers);

        fclose(fp);
}

static void init_fb(char *fb_dev)
{
        size_t pixels;
        size_t bytespp;

        if ((fbfd = open(fb_dev, O_RDONLY)) == -1)
        {
                printf("cannot open fb device %s\n", fb_dev);
                exit(EXIT_FAILURE);
        }

        if (ioctl(fbfd, FBIOGET_VSCREENINFO, &scrinfo) != 0)
        {
                printf("ioctl error\n");
                exit(EXIT_FAILURE);
        }

        pixels = scrinfo.xres * scrinfo.yres;
        bytespp = scrinfo.bits_per_pixel / 8;
/*
        fprintf(stderr, "xres=%d, yres=%d, xresv=%d, yresv=%d, xoffs=%d, yoffs=%d, bpp=%d\n",
          (int)scrinfo.xres, (int)scrinfo.yres,
          (int)scrinfo.xres_virtual, (int)scrinfo.yres_virtual,
          (int)scrinfo.xoffset, (int)scrinfo.yoffset,
          (int)scrinfo.bits_per_pixel);
*/
	    fbmmap = mmap(NULL, pixels * bytespp*2, PROT_READ, MAP_SHARED, fbfd, 0);


        if (fbmmap == MAP_FAILED)
        {
                printf("mmap failed\n");
                exit(EXIT_FAILURE);
        }
}

int main(int argc, char **argv)
{
        if (argc != 3)
                abort_("Usage: program_name /tmp/test.png /dev/fbx");
	init_fb(argv[2]);
       read_png_file();
       write_png_file(argv[1]);
       return 0;
}

/* fb2png */
