/*
 * arch/arm/mach-tegra/include/mach/fb.h
 *
 * Copyright (C) 2010 Google, Inc.
 * Author: Erik Gilling <konkers@google.com>
 *
 * Copyright (c) 2010-2013, NVIDIA CORPORATION, All rights reserved.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#ifndef __MACH_TEGRA_FB_H
#define __MACH_TEGRA_FB_H

#include <linux/fb.h>

struct platform_device;
struct tegra_dc;
struct tegra_fb_data;
struct resource;

int tegra_fb_get_mode(struct tegra_dc *dc);
int tegra_fb_set_mode(struct tegra_dc *dc, int fps);
struct tegra_fb_info {
	struct tegra_dc_win     win;
	struct platform_device  *ndev;
	struct fb_info          *info;
	bool                    valid;

	struct resource         *fb_mem;

	int                     xres;
	int                     yres;
	int                     curr_xoffset;
	int                     curr_yoffset;

	struct fb_videomode     mode;
	phys_addr_t             phys_start;
};

#ifdef CONFIG_FB_TEGRA
struct tegra_fb_info *tegra_fb_register(struct platform_device *ndev,
					struct tegra_dc *dc,
					struct tegra_fb_data *fb_data,
					struct resource *fb_mem);
void tegra_fb_unregister(struct tegra_fb_info *fb_info);
void tegra_fb_pan_display_reset(struct tegra_fb_info *fb_info);
void tegra_fb_update_monspecs(struct tegra_fb_info *fb_info,
			      struct fb_monspecs *specs,
			      bool (*mode_filter)(const struct tegra_dc *dc,
						  struct fb_videomode *mode));
#else
static inline struct tegra_fb_info *tegra_fb_register(
	struct platform_device *ndev, struct tegra_dc *dc,
	struct tegra_fb_data *fb_data, struct resource *fb_mem)
{
	return NULL;
}

static inline void tegra_fb_unregister(struct tegra_fb_info *fb_info)
{
}

static inline void tegra_fb_pan_display_reset(struct tegra_fb_info *fb_info)
{
}

static inline void tegra_fb_update_monspecs(struct tegra_fb_info *fb_info,
					    struct fb_monspecs *specs,
					    bool (*mode_filter)(struct fb_videomode *mode))
{
}
#endif

#endif
