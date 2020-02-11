#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __STDC_NO_THREADS__
#pragma message "C11 threads are not supported, will fallback to pthreads\n"
#include "vendor/tinycthread.h"
#else
#include <threads.h>
#endif

#include "worker.h"
#include "shared.h"

int main(int argc, char *argv[])
{
    if (argc == 1 || argc == 2)
    {
        fprintf(stderr, "Please supply one or multiple path argument(s): ./program string my-path [my-path-two] [my-path-three]\n");
        return -1;
    }
    if (argc > 128 + 2)
    {
        fprintf(stderr, "Too many arguments, please specify less than 128 paths\n");
        return -1;
    }

    mtx_init(&result_list_lock, mtx_plain);
    thrd_t threads[argc - 2];

    for (int i = 2; i < argc; i++)
    {
        struct thread_arg *ta = malloc(sizeof *ta);
        ta->id = i - 2;
        ta->path = argv[i];
        ta->search = argv[1];
        thrd_create(&threads[i - 2], worker_start, ta);
    }

    for (int i = 2; i < argc; i++)
    {
        int result;
        thrd_join(threads[i - 2], &result);

        if (result) // > 0
        {
            fprintf(stderr, "Error occured, could not scan filesystem for filename\n");
            return -1;
        }
    }

    mtx_destroy(&result_list_lock);

    if (result_list_index == 0)
    {
        fprintf(stdout, "No results found\n");
    }
    else
    {
        for (int i = 0; i < result_list_index; i++)
        {
            fprintf(stdout, "%s\n", result_list[i]);
        }
    }

    return 0;
}