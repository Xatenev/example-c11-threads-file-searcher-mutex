#include <string.h>
#include <stdio.h>

#ifdef __STDC_NO_THREADS__
#include "vendor/tinycthread.h"
#else
#include <threads.h>
#endif

#include "worker.h"

#include "shared.h"

int worker_start(struct thread_arg *arg) {
    fprintf(stdout, "Worker %d started to handle path: %s\n", arg->id, arg->path);
    strcpy(found[0], "test");

    fprintf(stdout, "Worker %d finished handling path: %s\n", arg->id, arg->path);
    return 0;
}