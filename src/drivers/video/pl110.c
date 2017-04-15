/**
 * @file
 * @brief
 *
 * @author
 * @date
 */

#include <errno.h>
#include <string.h>
#include <assert.h>
#include <sys/mman.h>
#include <drivers/video/fb.h>
#include <drivers/video/vesa_modes.h>
#include <framework/mod/options.h>
#include <mem/page.h>
#include <util/binalign.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(generic_init);

static int generic_set_var(struct fb_info *info, const struct fb_var_screeninfo *var) {
	return -ENOSYS;
}

static int generic_get_var(struct fb_info *info, struct fb_var_screeninfo *var) {

	memset(var, 0, sizeof(struct fb_var_screeninfo));

	var->xres_virtual = var->xres = 0; // TODO
	var->yres_virtual = var->yres = 0; // TODO
	var->bits_per_pixel = 0; // TODO

	return 0;
}

static const struct fb_ops generic_ops = {
	.fb_get_var = generic_get_var,
	.fb_set_var = generic_set_var,
};

static int generic_init(void) {
	char *mmap_base = NULL; // TODO
	size_t mmap_len = 0; // TODO
	struct fb_info *info;

	if (MAP_FAILED == mmap_device_memory(mmap_base,
				mmap_len,
			       	PROT_READ|PROT_WRITE|PROT_NOCACHE,
				MAP_FIXED,
				(unsigned long) mmap_base)) {
		return -EIO;
	}

	info = fb_create(&generic_ops, mmap_base, mmap_len);
	if (info == NULL) {
		munmap(mmap_base, mmap_len);
		return -ENOMEM;
	}

	return 0;
}
