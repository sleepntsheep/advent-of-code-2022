#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/wait.h>

#define NDAYS 25

bool day_exists[NDAYS + 1];

bool compile(const char *path, const char *out)
{
    pid_t pid;
    int status;
    pid = fork();
    if (pid == 0) {
        // child
        execl("/usr/bin/cc", "cc", path, "-o", out, NULL);
        // unreachable if execl successful
        exit(127);
    }
    else if (pid > 0) {
        if (waitpid(pid, &status, 0) > 0) {
            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {
                /* the program terminated normally and executed successfully */
                return true;
            } else if (WIFEXITED(status) && WEXITSTATUS(status)) {
                if (WEXITSTATUS(status) == 127) {
                    fprintf(stderr, "compile(): execl failed\n");
                    return false;
                } else {
                    fprintf(stderr, "compile(): cc failed with exit code %d\n",
                            WEXITSTATUS(status));
                }
            } else {
                fprintf(stderr, "compile(): didn't terminate normally");
            }
        } else {
            fprintf(stderr, "compile(): waitpid failed");
        }
    }
    return false;
}

int main(void)
{
    DIR *dir = opendir(".");
    struct dirent *ent = NULL;

    while ((ent = readdir(dir))) {
        int day, part;
        if (!strstr(ent->d_name, ".c"))
            continue;
        if (sscanf(ent->d_name, "%d_%d.c", &day, &part) != 2)
            continue;
        char bin[256];
        sprintf(bin, "%d_%d.bin", day, part);
        day_exists[day] = true;
        if (!compile(ent->d_name, bin)) {
            fprintf(stderr, "Failed compiling: %s\n", ent->d_name);
        }
    }

    closedir(dir);
    return EXIT_SUCCESS;
}

