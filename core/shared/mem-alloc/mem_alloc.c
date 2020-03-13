/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "mem_alloc.h"
<<<<<<< HEAD
#include "config.h"
=======
>>>>>>> intel/internal/feature

#if DEFAULT_MEM_ALLOCATOR == MEM_ALLOCATOR_EMS

#include "ems/ems_gc.h"

mem_allocator_t mem_allocator_create(void *mem, uint32_t size)
{
    return gc_init_with_pool((char *) mem, size);
}

void mem_allocator_destroy(mem_allocator_t allocator)
{
    gc_destroy_with_pool((gc_handle_t) allocator);
}

void *
mem_allocator_malloc(mem_allocator_t allocator, uint32_t size)
{
    return gc_alloc_vo_h((gc_handle_t) allocator, size);
}

void *
mem_allocator_realloc(mem_allocator_t allocator, void *ptr, uint32_t size)
{
    return gc_realloc_vo_h((gc_handle_t) allocator, ptr, size);
}

void mem_allocator_free(mem_allocator_t allocator, void *ptr)
{
    if (ptr)
        gc_free_h((gc_handle_t) allocator, ptr);
}

#else /* else of DEFAULT_MEM_ALLOCATOR */

#include "tlsf/tlsf.h"
<<<<<<< HEAD
#include "bh_thread.h"
=======
>>>>>>> intel/internal/feature

typedef struct mem_allocator_tlsf {
    tlsf_t tlsf;
    korp_mutex lock;
}mem_allocator_tlsf;

mem_allocator_t
mem_allocator_create(void *mem, uint32_t size)
{
    mem_allocator_tlsf *allocator_tlsf;
    tlsf_t tlsf;
    char *mem_aligned = (char*)(((uintptr_t)mem + 3) & ~3);

    if (size < 1024) {
        printf("Create mem allocator failed: pool size must be "
                "at least 1024 bytes.\n");
        return NULL;
    }

    size -= mem_aligned - (char*)mem;
    mem = (void*)mem_aligned;

    tlsf = tlsf_create_with_pool(mem, size);
    if (!tlsf) {
        printf("Create mem allocator failed: tlsf_create_with_pool failed.\n");
        return NULL;
    }

    allocator_tlsf = tlsf_malloc(tlsf, sizeof(mem_allocator_tlsf));
    if (!allocator_tlsf) {
        printf("Create mem allocator failed: tlsf_malloc failed.\n");
        tlsf_destroy(tlsf);
        return NULL;
    }

    allocator_tlsf->tlsf = tlsf;

<<<<<<< HEAD
    if (vm_mutex_init(&allocator_tlsf->lock)) {
=======
    if (os_mutex_init(&allocator_tlsf->lock)) {
>>>>>>> intel/internal/feature
        printf("Create mem allocator failed: tlsf_malloc failed.\n");
        tlsf_free(tlsf, allocator_tlsf);
        tlsf_destroy(tlsf);
        return NULL;
    }

    return allocator_tlsf;
}

void
mem_allocator_destroy(mem_allocator_t allocator)
{
    mem_allocator_tlsf *allocator_tlsf = (mem_allocator_tlsf *)allocator;
    tlsf_t tlsf = allocator_tlsf->tlsf;

<<<<<<< HEAD
    vm_mutex_destroy(&allocator_tlsf->lock);
=======
    os_mutex_destroy(&allocator_tlsf->lock);
>>>>>>> intel/internal/feature
    tlsf_free(tlsf, allocator_tlsf);
    tlsf_destroy(tlsf);
}

void *
mem_allocator_malloc(mem_allocator_t allocator, uint32_t size)
{
    void *ret;
    mem_allocator_tlsf *allocator_tlsf = (mem_allocator_tlsf *)allocator;

    if (size == 0)
        /* tlsf doesn't allow to allocate 0 byte */
        size = 1;

<<<<<<< HEAD
    vm_mutex_lock(&allocator_tlsf->lock);
    ret = tlsf_malloc(allocator_tlsf->tlsf, size);
    vm_mutex_unlock(&allocator_tlsf->lock);
=======
    os_mutex_lock(&allocator_tlsf->lock);
    ret = tlsf_malloc(allocator_tlsf->tlsf, size);
    os_mutex_unlock(&allocator_tlsf->lock);
>>>>>>> intel/internal/feature
    return ret;
}

void *
mem_allocator_realloc(mem_allocator_t allocator, void *ptr, uint32_t size)
{
    void *ret;
    mem_allocator_tlsf *allocator_tlsf = (mem_allocator_tlsf *)allocator;

    if (size == 0)
        /* tlsf doesn't allow to allocate 0 byte */
        size = 1;

<<<<<<< HEAD
    vm_mutex_lock(&allocator_tlsf->lock);
    ret = tlsf_realloc(allocator_tlsf->tlsf, ptr, size);
    vm_mutex_unlock(&allocator_tlsf->lock);
=======
    os_mutex_lock(&allocator_tlsf->lock);
    ret = tlsf_realloc(allocator_tlsf->tlsf, ptr, size);
    os_mutex_unlock(&allocator_tlsf->lock);
>>>>>>> intel/internal/feature
    return ret;
}

void
mem_allocator_free(mem_allocator_t allocator, void *ptr)
{
    if (ptr) {
        mem_allocator_tlsf *allocator_tlsf = (mem_allocator_tlsf *)allocator;
<<<<<<< HEAD
        vm_mutex_lock(&allocator_tlsf->lock);
        tlsf_free(allocator_tlsf->tlsf, ptr);
        vm_mutex_unlock(&allocator_tlsf->lock);
=======
        os_mutex_lock(&allocator_tlsf->lock);
        tlsf_free(allocator_tlsf->tlsf, ptr);
        os_mutex_unlock(&allocator_tlsf->lock);
>>>>>>> intel/internal/feature
    }
}

#endif /* end of DEFAULT_MEM_ALLOCATOR */

