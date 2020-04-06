/*
 * tio - a simple TTY terminal I/O application
 *
 * Copyright (c) 2014-2017  Martin Lund
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tio/error.h"
#include "tio/print.h"

char * current_time(void)
{
    static char tmp_string[20];
    static char time_string[24];
    struct tm *tmp;
    struct tm gmtval;
    struct timespec curtime;
    int msec;

    if (clock_gettime(CLOCK_REALTIME, &curtime) != 0)
    {
        error_printf("Retrieving clock_gettime failed");
        exit(EXIT_FAILURE);
    }
    msec = curtime.tv_nsec/1.0e6;

    tmp = gmtime_r(&curtime.tv_sec, &gmtval);
    if (tmp == NULL)
    {
        error_printf("Retrieving gmtime failed");
        exit(EXIT_FAILURE);
    }

    strftime(tmp_string, sizeof(tmp_string), "%Y-%m-%dT%H:%M:%S", tmp);
    snprintf(time_string, sizeof(time_string), "%s.%03d", tmp_string, msec);

    return time_string;
}

void delay(long ms)
{
    struct timespec ts;

    ts.tv_sec = ms / 1000;
    ts.tv_nsec = (ms % 1000) * 1000000;

    nanosleep(&ts, NULL);
}
