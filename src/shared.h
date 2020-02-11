#ifndef SHARED_H
#define SHARED_H

struct thread_arg {
    int id;
    char *path;
};

char found[8192][1024];

#endif
