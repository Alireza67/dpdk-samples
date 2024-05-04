/* SPDX-License-Identifier: BSD-3-Clause
 * Copyright(c) 2010-2014 Intel Corporation
 */

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <string>
#include <errno.h>
#include <sys/queue.h>

#include <rte_memory.h>
#include <rte_launch.h>
#include <rte_eal.h>
#include <rte_per_lcore.h>
#include <rte_lcore.h>
#include <rte_debug.h>

/* Launch a function on lcore. 8< */
static int
lcore_hello(__rte_unused void *arg)
{
        unsigned lcore_id;
        lcore_id = rte_lcore_id();
        printf("hello from core %u\n", lcore_id);
        return 0;
}
/* >8 End of launching function on lcore. */

/* Initialization of Environment Abstraction Layer (EAL). 8< */
int main(int argc, char **argv)
{
        unsigned lcore_id;

        int ret{};
        if (argc == 1)
        {
            // If no arguments are passed, use default ones
            char *default_args[] = {argv[0], "-l", "0-3", "-n", "4"};
            argc = sizeof(default_args) / sizeof(default_args[0]);
   ret = rte_eal_init(argc, default_args);
        }
        else
        {
            ret = rte_eal_init(argc, argv);
        }

        if (ret < 0)
        {
            rte_panic("Cannot init EAL\n");
        }
        /* >8 End of initialization of Environment Abstraction Layer */

        /**
         * @brief Once the EAL is initialized, the application is ready to launch a function on an lcore.
         * lcore_hello() is called on every available lcore.
         */
        RTE_LCORE_FOREACH_WORKER(lcore_id){
                rte_eal_remote_launch(lcore_hello, NULL, lcore_id);
        }

        /* call it on main lcore too */
        lcore_hello(NULL);
        /* >8 End of launching the function on each lcore. */

        rte_eal_mp_wait_lcore();

        /* clean up the EAL */
        rte_eal_cleanup();

        return 0;
}
