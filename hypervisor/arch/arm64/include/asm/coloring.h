/*
 * Jailhouse Cache Coloring Support
 *
 * Copyright (C) Universit√† di Modena e Reggio Emilia, 2018
 * Copyright (C) Boston University, 2020
 * Copyright (C) Technical University of Munich, 2020
 *
 * Authors:
 *  Luca Miccio <lucmiccio@gmail.com>
 *  Renato Mancuso (BU) <rmancuso@bu.edu>
 *  Andrea Bastoni <andrea.bastoni@tum.de> at https://rtsl.cps.mw.tum.de
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See the
 * COPYING file in the top-level directory.
 */
#ifndef _JAILHOUSE_ASM_COLORING_H
#define _JAILHOUSE_ASM_COLORING_H

#include <jailhouse/cell-config.h>
#include <jailhouse/utils.h>
#include <jailhouse/control.h>

#ifdef CONFIG_DEBUG
#define col_print(fmt, ...)			\
	printk("[COL] " fmt, ##__VA_ARGS__)
#else
#define col_print(fmt, ...) do { } while (0)
#endif

/** Color operations */
#define COL_OP_CREATE	0x1
#define COL_OP_DESTROY	0x2
#define COL_OP_FLUSH	0x10

/**
 * Only parameter needed to determine the coloring.
 */
extern u64 coloring_way_size;

/**
 * Colored Operation
 */
struct color_op {
	const struct paging_structures *pg_structs;
	unsigned long phys;
	unsigned long size;
	unsigned long virt;
	unsigned long access_flags;
	unsigned long paging_flags;
	u64 color_mask;
	enum dcache_flush flush_type;
	unsigned int op;
};

/**
 * Colored operations on a cell / memory region.
 *
 * Encapsulate the loops needed to iterate through a region and identify
 * the color-compatible phys2virt mappings.
 */
extern int color_do_op(struct color_op *op);

static inline void arm_color_dcache_flush_memory_region(
	unsigned long phys,
	unsigned long size,
	unsigned long virt,
	u64 color_mask,
	enum dcache_flush flush_type)
{
	struct color_op op;

	if (coloring_way_size == 0)
		BUG();

	op.phys = phys;
	op.size = size;
	op.virt = virt;
	op.color_mask = color_mask;
	op.flush_type = flush_type;
	op.op = COL_OP_FLUSH;

	color_do_op(&op);
}

/**
 * Detection of coloring way size.
 */
static inline void arm_color_init(void)
{
	coloring_way_size = system_config->platform_info.color.way_size;

	printk("Init Coloring: Way size: 0x%llx\n",
	       coloring_way_size);
}

static inline int
color_paging_create(const struct paging_structures *pg_structs,
		    unsigned long phys, unsigned long size, unsigned long virt,
		    unsigned long access_flags, unsigned long paging_flags,
		    u64 color_mask)
{
	struct color_op op;

	if (coloring_way_size == 0)
		return -EINVAL;

	op.pg_structs = pg_structs;
	op.phys = phys;
	op.size = size;
	op.virt = virt;
	op.access_flags = access_flags;
	op.paging_flags = paging_flags;
	op.color_mask = color_mask;
	op.op = COL_OP_CREATE;

	return color_do_op(&op);
}

static inline int
color_paging_destroy(const struct paging_structures *pg_structs,
		     unsigned long phys, unsigned long size, unsigned long virt,
		     unsigned long paging_flags, u64 color_mask)
{
	struct color_op op;

	if (coloring_way_size == 0)
		return -EINVAL;

	op.pg_structs = pg_structs;
	op.phys = phys;
	op.size = size;
	op.virt = virt;
	op.paging_flags = paging_flags;
	op.color_mask = color_mask;
	op.op = COL_OP_DESTROY;

	return color_do_op(&op);
}

#endif
