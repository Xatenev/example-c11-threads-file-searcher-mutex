#ifndef SHARED_H
#define SHARED_H

struct thread_arg {
    int id;
    char *path;
    char *search;
};

mtx_t result_list_lock;
char result_list[8192][1024];
int result_list_index;

#endif
