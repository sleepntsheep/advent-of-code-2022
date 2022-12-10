#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <assert.h>
#include <curses.h>

#define NAME_MAX_LEN 1023
#define MAX_DEPTH 1024
#define MAX_NODE 100000

int maxi(int a, int b) { return a > b ? a : b; }
int mini(int a, int b) { return a < b ? a : b; }

typedef enum {
    File,
    Directory
} EntType;

struct Entity {
    bool type;
    char name[NAME_MAX_LEN + 1];
    size_t size;
    struct Entity **children;
    struct Entity *parent;
    size_t children_count;
    size_t children_alloc;
};

struct Entity *Directory_New(char *name) {
    assert(strlen(name) <= NAME_MAX_LEN);
    struct Entity *dir = malloc(sizeof(struct Entity));
    assert(dir);
    strcpy(dir->name, name);
    dir->type = Directory;
    dir->size = 0;
    dir->children = NULL;
    dir->parent = NULL;
    dir->children_count = dir->children_alloc = 0;
    return dir;
}

struct Entity *File_New(char *name, size_t size) {
    assert(strlen(name) <= NAME_MAX_LEN);
    struct Entity *file = malloc(sizeof(struct Entity));
    assert(file);
    strcpy(file->name, name);
    file->type = File;
    file->size = size;
    file->children = NULL;
    file->parent = NULL;
    file->children_count = file->children_alloc = 0;
    return file;
}

void Entity_Update_Size(struct Entity *ent, size_t delta) {
    ent->size += delta;
    if (ent->parent)
        Entity_Update_Size(ent->parent, delta);
}

void Directory_Add_Entity(struct Entity *parent, struct Entity *child) {
    assert(parent && child);
    Entity_Update_Size(parent, child->size);
    if (parent->children_alloc == parent->children_count) {
        parent->children_alloc = maxi(4, parent->children_alloc * 2);
        parent->children = realloc(parent->children, sizeof *(parent->children) * parent->children_alloc);
    }
    parent->children[parent->children_count++] = child;
    child->parent = parent;
}

void Entity_Free(struct Entity *ent) {
    for (size_t i = 0; i < ent->children_count; i++)
        Entity_Free(ent->children[i]);
    free(ent->children);
    free(ent);
}

void Directory_DepthTraverse(struct Entity *rootnode, void (callback)(struct Entity *, void*), void *userdata) {
    assert(rootnode && callback);
    struct Entity *stack[MAX_NODE] = { rootnode };
    size_t sp = 1;
    while (sp) {
        struct Entity *ent = stack[--sp];
        callback(ent, userdata);
        for (size_t i = 0; i < ent->children_count; i++) {
            assert(sp < MAX_NODE);
            stack[sp++] = ent->children[i];
        }
    }
}

void traverse_get_sum_of_ent_with_sub1e5_size(struct Entity *ent, void *count) {
    if (ent->type == Directory && ent->size < 100000)
        (*(size_t*)count) += ent->size;
}

void traverse_get_smallest_directory_with_atleast_n_size(struct Entity *ent, void *data) {
    if (ent->type == Directory && ent->size >= ((size_t*)data)[0])
        ((size_t*)data)[1] = mini(((size_t*)data)[1], ent->size);
}

int main(void) {
    struct Entity *root = Directory_New("/");
    struct Entity *cwd = root;
    assert(root && cwd);

    char buf[2048];
    while (fgets(buf, sizeof buf, stdin)) {
        assert(strchr(buf, '\n') && "Buffer too small");
        *strchr(buf, '\n') = 0;
        if (buf[0] == 0) {
        } else if (buf[2] == 'c') {
            if (buf[5] == '.' && buf[6] == '.') {
                assert(cwd->parent);
                cwd = cwd->parent;
            } else if (buf[5] == '/') {
                cwd = root;
            } else {
                // TODO - use hashmap to make this faster
                bool found = 0;
                //for (size_t i = 0; i < cwd->children_count; i++) {
                //    if (cwd->children[i]->type == Directory && !strcmp(cwd->children[i]->name, buf + 5)) {
                //        cwd = cwd->children[i];
                //        found = 1;
                //        break;
                //    }
                //}
                if (!found) {
                    struct Entity *subdir = Directory_New(buf + 5);
                    Directory_Add_Entity(cwd, subdir);
                    cwd = subdir;
                }
            }
        } else if (buf[2] == 'l') {
        } else if (buf[2] == 'r') {
        } else {
            int size = 0;
            char name[1024];
            assert(sscanf(buf, "%d %s", &size, name) == 2);
            struct Entity *file = File_New(name, size);
            assert(file);
            Directory_Add_Entity(cwd, file);
        }
    }

    // part 1
    size_t count = 0;
    Directory_DepthTraverse(root, traverse_get_sum_of_ent_with_sub1e5_size, &count);

    // part 2
    assert(root->size < 70000000);
    size_t need = 30000000 - (70000000 - root->size);
    size_t data[2] = { need, 1e9 /* return */ };
    Directory_DepthTraverse(root, traverse_get_smallest_directory_with_atleast_n_size, data);

    Entity_Free(root);

    printf("%zu %zu", count, data[1]);
    return EXIT_SUCCESS;
}

