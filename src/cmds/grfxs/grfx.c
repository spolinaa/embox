
#include <errno.h>

#include <drivers/video/fb.h>

int main(int argc, char *argv[]) {
	struct fb_info *fb = fb_lookup(0);
	if (NULL == fb) {
		return -ENOENT;
	}

	struct fb_var_screeninfo var;
	if (0 != fb_get_var(fb, &var)) {
		return -EINVAL;
	}

	/* portable */
	struct fb_fillrect rect;
	rect.dx = 200;
	rect.dy = 200;
	rect.width = 200;
	rect.height = 200;
	rect.color = 0xf00;
	rect.rop = ROP_COPY;
	fb_fillrect(fb, &rect);

	/* VERY not portable */
	for (int i = 0; i < 200; ++i) {
		for (int j = 0; j < 200; ++j) {
			*(((uint16_t*)fb->screen_base) + i * var.xres + j) = ((i * 32 / 200) << 11) + (0x1f & (j * 32 / 200));
		}
	}
}
