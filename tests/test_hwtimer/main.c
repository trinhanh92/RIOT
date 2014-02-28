/*
 * Copyright (C) 2013 INRIA
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup tests
 * @{
 *
 * @file
 * @brief Hwtimer test application
 *
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 *
 * @}
 */

#include <stdio.h>

#include "hwtimer.h"

#define BASE_DELAY (1000UL * 1000UL)
#define DELTA_DELAY (1000UL * 1000UL)
#define MSGLEN 12 // == strlen("callback %2i")
char msg[MSGLEN * ARCH_MAXTIMERS]; // == [callback  1\0callback  2\0...]

void callback(void *ptr)
{
    puts((char *) ptr);
}

int main(void)
{
    puts("hwtimer test application...");

    puts("Initializing hwtimer...");
    hwtimer_init();

    puts("Initializing hwtimer [OK].");

    puts("");
    puts("  Timers should print \"callback x\" when they run out.");
    puts("  The order for x is 1, n-1, n-2, ..., 2 where n is the number of available hardware timers.");
    puts("  One timer should fire every second.");
    puts("  Additionally the message \"hwtimer set.\" should be printed in 1 second.");
    puts("");
    puts("Settings timers:");
    puts("");

    unsigned long delay = BASE_DELAY + ((ARCH_MAXTIMERS - 1) * DELTA_DELAY);

    /* make the first timer first to fire so timers do not run out linearly */
    char *msgn = msg;
    snprintf(msgn, MSGLEN, "callback %2x", 1);
    hwtimer_set(HWTIMER_TICKS(BASE_DELAY), callback, (void *) msgn);
    printf("set %s\n", msgn);

    /* set up to ARCH_MAXTIMERS-1 because hwtimer_wait below also
     * needs a timer */
    for (int i = 1; i < (ARCH_MAXTIMERS - 1); i++) {
        msgn = msg + (i * MSGLEN);
        delay -= DELTA_DELAY;
        snprintf(msgn, MSGLEN, "callback %2x", i + 1);
        hwtimer_set(HWTIMER_TICKS(delay), callback, (void *) msgn);
        printf("set %s\n", msgn);
    }

    puts("");
    puts("All timers set.");
    puts("");

    hwtimer_wait(HWTIMER_TICKS(1000UL * 1000UL));

    puts("hwtimer set.");
}
