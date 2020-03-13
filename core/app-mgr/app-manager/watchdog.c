/*
 * Copyright (C) 2019 Intel Corporation.  All rights reserved.
 * SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
 */

#include "watchdog.h"
<<<<<<< HEAD
#include "bh_queue.h"
#include "bh_thread.h"
=======
#include "bh_platform.h"
>>>>>>> intel/internal/feature

#define WATCHDOG_THREAD_PRIORITY 5

/* Queue of watchdog */
static bh_queue *watchdog_queue;

#ifdef WATCHDOG_ENABLED /* TODO */
static void watchdog_timer_callback(void *timer)
{
    watchdog_timer *wd_timer = app_manager_get_wd_timer_from_timer_handle(
            timer);

    watchdog_timer_stop(wd_timer);

<<<<<<< HEAD
    vm_mutex_lock(&wd_timer->lock);
=======
    os_mutex_lock(&wd_timer->lock);
>>>>>>> intel/internal/feature

    if (!wd_timer->is_stopped) {

        wd_timer->is_interrupting = true;

        bh_post_msg(watchdog_queue, WD_TIMEOUT, wd_timer->module_data,
                sizeof(module_data));
    }

<<<<<<< HEAD
    vm_mutex_unlock(&wd_timer->lock);
=======
    os_mutex_unlock(&wd_timer->lock);
>>>>>>> intel/internal/feature
}
#endif

bool watchdog_timer_init(module_data *m_data)
{
#ifdef WATCHDOG_ENABLED /* TODO */
    watchdog_timer *wd_timer = &m_data->wd_timer;

<<<<<<< HEAD
    if (0 != vm_mutex_init(&wd_timer->lock))
=======
    if (0 != os_mutex_init(&wd_timer->lock))
>>>>>>> intel/internal/feature
        return false;

    if (!(wd_timer->timer_handle =
                    app_manager_timer_create(watchdog_timer_callback, wd_timer))) {
<<<<<<< HEAD
        vm_mutex_destroy(&wd_timer->lock);
=======
        os_mutex_destroy(&wd_timer->lock);
>>>>>>> intel/internal/feature
        return false;
    }

    wd_timer->module_data = m_data;
    wd_timer->is_interrupting = false;
    wd_timer->is_stopped = false;
#endif
    return true;
}

void watchdog_timer_destroy(watchdog_timer *wd_timer)
{
#ifdef WATCHDOG_ENABLED /* TODO */
    app_manager_timer_destroy(wd_timer->timer_handle);
<<<<<<< HEAD
    vm_mutex_destroy(&wd_timer->lock);
=======
    os_mutex_destroy(&wd_timer->lock);
>>>>>>> intel/internal/feature
#endif
}

void watchdog_timer_start(watchdog_timer *wd_timer)
{
<<<<<<< HEAD
    vm_mutex_lock(&wd_timer->lock);
=======
    os_mutex_lock(&wd_timer->lock);
>>>>>>> intel/internal/feature

    wd_timer->is_interrupting = false;
    wd_timer->is_stopped = false;
    app_manager_timer_start(wd_timer->timer_handle,
            wd_timer->module_data->timeout);

<<<<<<< HEAD
    vm_mutex_unlock(&wd_timer->lock);
=======
    os_mutex_unlock(&wd_timer->lock);
>>>>>>> intel/internal/feature
}

void watchdog_timer_stop(watchdog_timer *wd_timer)
{
    app_manager_timer_stop(wd_timer->timer_handle);
}

#ifdef WATCHDOG_ENABLED /* TODO */
static void watchdog_queue_callback(void *queue_msg)
{
    if (bh_message_type(queue_msg) == WD_TIMEOUT) {
        module_data *m_data = (module_data *) bh_message_payload(queue_msg);
        if (g_module_interfaces[m_data->module_type]
                && g_module_interfaces[m_data->module_type]->module_watchdog_kill) {
            g_module_interfaces[m_data->module_type]->module_watchdog_kill(
                    m_data);
            app_manager_post_applets_update_event();
        }
    }
}
#endif

#ifdef WATCHDOG_ENABLED /* TODO */
static void*
watchdog_thread_routine(void *arg)
{
    /* Enter loop run */
    bh_queue_enter_loop_run(watchdog_queue, watchdog_queue_callback);

    (void) arg;
    return NULL;
}
#endif

bool watchdog_startup()
{
    if (!(watchdog_queue = bh_queue_create())) {
        app_manager_printf(
                "App Manager start failed: create watchdog queue failed.\n");
        return false;
    }
#if 0
//todo: enable watchdog
    /* Start watchdog thread */
    if (!jeff_runtime_create_supervisor_thread_with_prio(watchdog_thread_routine, NULL,
                    WATCHDOG_THREAD_PRIORITY)) {
        bh_queue_destroy(watchdog_queue);
        return false;
    }
#endif
    return true;
}
