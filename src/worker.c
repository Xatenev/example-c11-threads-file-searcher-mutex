#define _DEFAULT_SOURCE

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef __STDC_NO_THREADS__
#include "vendor/tinycthread.h"
#else
#include <threads.h>
#endif

#include "worker.h"

#include "shared.h"

struct file_list
{
    char entries[256][1024];
    int length;
};

struct file_list worker_list_dir(const char *name, const char *search);

/**
 * Starting point for one worker
 */
int worker_start(struct thread_arg *arg)
{
    fprintf(stdout, "Worker %d started to handle path: %s\n", arg->id, arg->path);

    struct file_list file_list = worker_list_dir(arg->path, arg->search);

    for (int i = 0; i < file_list.length; i++)
    {
        mtx_lock(&result_list_lock);
        strcpy(result_list[result_list_index], file_list.entries[i]);
        result_list_index++;
        mtx_unlock(&result_list_lock);
    }

    fprintf(stdout, "Worker %d finished handling path: %s\n", arg->id, arg->path);
    free(arg);
    return 0;
}

/**
 * Returns an array in the format char[256][1024]
 */
struct file_list worker_list_dir(const char *name, const char *search)
{
    _Thread_local static struct file_list file_list = {.length = 0};

    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name)))
        return file_list;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            char path[1024];

            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);

            worker_list_dir(path, search);
        }
        else
        {
            if (strstr(entry->d_name, search) != NULL)
            {
                file_list.length++;

                strcpy(file_list.entries[file_list.length - 1], name);
                strcat(file_list.entries[file_list.length - 1], "/");
                strcat(file_list.entries[file_list.length - 1], entry->d_name);
            }
        }
    }

    closedir(dir);
    return file_list;
}