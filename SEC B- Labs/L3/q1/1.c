// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>

// // Maximum number of sub-directories in each directory
// #define MAX_SUB_DIRS 20

// // Structure to represent a directory
// struct Directory {
//     char name[20]; // Name of the directory
//     int num_sub_dirs; // Number of sub-directories
//     struct Directory *parent; // Pointer to the parent directory
//     struct Directory *sub_dirs[MAX_SUB_DIRS]; // Array of pointers to sub-directories
// };

// // Pointer to the current directory
// struct Directory *current_dir;

// // Function to create a new directory
// struct Directory *create_directory(char *name, struct Directory *parent) {
//     // Allocate memory for the new directory
//     struct Directory *dir = (struct Directory*) malloc(sizeof(struct Directory));
//     if (dir == NULL) {
//         printf("-1\n");
//         return NULL;
//     }

//     // Initialize the fields of the new directory
//     strcpy(dir->name, name);
//     dir->num_sub_dirs = 0;
//     dir->parent = parent;

//     // Return the pointer to the new directory
//     return dir;
// }

// // Function to add a sub-directory to the current directory
// void mkdir(char *name) {
//     // Check if the current directory has reached the maximum number of sub-directories
//     if (current_dir->num_sub_dirs == MAX_SUB_DIRS) {
//         printf("-1\n");
//         return;
//     }

//     // Check if the directory with the same name already exists
//     int i;
//     for (i = 0; i < current_dir->num_sub_dirs; i++) {
//         if (strcmp(current_dir->sub_dirs[i]->name, name) == 0) {
//             printf("-1\n");
//             return;
//         }
//     }

//     // Create a new directory and add it to the current directory
//     struct Directory *dir = create_directory(name, current_dir);
//     current_dir->sub_dirs[current_dir->num_sub_dirs++] = dir;
// }

// // Function to change the current directory to a sub-directory
// void cd(char *name) {
//     // Check if the name is ".." to move to the parent directory
//     if (strcmp(name, "..") == 0) {
//         // Check if the current directory is not the root directory
//         if (current_dir->parent != NULL) {
//             current_dir = current_dir->parent;
//         }
//         else {
//             printf("-1\n");
//         }
//         return;
//     }

//     // Find the sub-directory with the given name
//     int i;
//     for (i = 0; i < current_dir->num_sub_dirs; i++) {
//         if (strcmp(current_dir->sub_dirs[i]->name, name) == 0) {
//             current_dir = current_dir->sub_dirs[i];
//             return;
//         }
//     }

//     // Directory not found
//     printf("-1\n");
// }

// // Function to delete a directory and all its sub-directories recursively
// void delete_directory(struct Directory *dir) {
//     // Delete all the sub-directories recursively
//     int i;
//     for (i = 0; i < dir->num_sub_dirs; i++) {
//         delete_directory(dir->sub_dirs[i]);
//     }

//     // Free the memory for the current directory
//     free(dir);
// }

// // Function to delete a directory and its sub-directories
// void rmdir(char *name) {
//     // Find the sub-directory with the given name
//     int i;
//     for (i = 0; i < current_dir->num_sub_dirs; i++) {
//         if (strcmp(current_dir->sub_dirs[i]->name, name) == 0)
//             break;
//     }
//     if (i == current_dir->num_sub_dirs) {
//         // Sub-directory with given name not found
//         printf("-1\n");
//         return;
//     }
//     // Delete the sub-directory and its contents
//     struct Directory *sub_dir = current_dir->sub_dirs[i];
//     current_dir->sub_dirs[i] = current_dir->sub_dirs[current_dir->num_sub_dirs-1];
//     current_dir->num_sub_dirs--;
//     free(sub_dir);
//     printf("\n");
// }
// // Function to delete a directory and its sub-directories
// void rmdir(char *name) {
//     // Find the sub-directory with the given name
//     int i;
//     for (i = 0; i < current_dir->num_sub_dirs; i++) {
//         if (strcmp(current_dir->sub_dirs[i]->name, name) == 0)
//             break;
//     }
//     if (i == current_dir->num_sub_dirs) {
//         // Sub-directory with given name not found
//         printf("-1\n");
//         return;
//     }
//     // Delete the sub-directory and its contents
//     Directory *sub_dir = current_dir->sub_dirs[i];
//     current_dir->sub_dirs[i] = current_dir->sub_dirs[current_dir->num_sub_dirs-1];
//     current_dir->num_sub_dirs--;
//     free(sub_dir);
//     printf("\n");
// }

//2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIRS 20
#define MAX_COMMAND_LEN 100

typedef struct Directory {
    char name[50];
    struct Directory *parent;
    struct Directory *subdirs[MAX_DIRS];
    int num_subdirs;
} Directory;

Directory *root, *cwd;

// Forward declarations
void print_path(Directory *dir);
void print_subdirs(Directory *dir);
Directory *create_directory(char *name);
Directory *find_directory(char *name);
int add_subdir(Directory *dir, Directory *subdir);
int remove_subdir(Directory *dir, Directory *subdir);
void remove_directory(Directory *dir);

int main() {
    int q;
    scanf("%d", &q);
    root = create_directory("root");
    cwd = root;
    for (int i = 0; i < q; i++) {
        int n;
        scanf("%d", &n);
        char command[MAX_COMMAND_LEN];
        scanf(" %[^\n]", command);
        char *token = strtok(command, " ");
        if (strcmp(token, "pwd") == 0) {
            print_path(cwd);
            printf("\n");
        } else if (strcmp(token, "ls") == 0) {
            print_subdirs(cwd);
            printf("\n");
        } else if (strcmp(token, "mkdir") == 0) {
            token = strtok(NULL, " ");
            Directory *dir = create_directory(token);
            if (add_subdir(cwd, dir) == -1) {
                printf("-1\n");
            }
        } else if (strcmp(token, "cd") == 0) {
            token = strtok(NULL, " ");
            if (strcmp(token, "..") == 0) {
                cwd = cwd->parent;
            } else {
                Directory *dir = find_directory(token);
                if (dir == NULL) {
                    printf("-1\n");
                } else {
                    cwd = dir;
                }
            }
        } else if (strcmp(token, "rm") == 0) {
            token = strtok(NULL, " ");
            token = strtok(NULL, " ");
            Directory *dir = find_directory(token);
            if (dir == NULL) {
                printf("-1\n");
            } else {
                remove_directory(dir);
            }
        }
    }
    return 0;
}

void print_path(Directory *dir) {
    if (dir == root) {
        printf("root");
    } else {
        print_path(dir->parent);
        printf("/%s", dir->name);
    }
}

void print_subdirs(Directory *dir) {
    for (int i = 0; i < dir->num_subdirs; i++) {
        printf("%s ", dir->subdirs[i]->name);
    }
}

Directory *create_directory(char *name) {
    Directory *dir = (Directory *) malloc(sizeof(Directory));
    strcpy(dir->name, name);
    dir->parent = NULL;
    dir->num_subdirs = 0;
    return dir;
}

Directory *find_directory(char *name) {
    Directory *dir = NULL;
    for (int i = 0; i < cwd->num_subdirs; i++) {
        if (strcmp(cwd->subdirs[i]->name, name) == 0) {
            dir = cwd->subdirs[i];
            break;
        }
    }
    return dir;
}
/* Function to create a new subdirectory inside the current directory */
int add_subdir(Directory *dir, Directory *subdir) {
    if (dir->num_subdirs == MAX_DIRS) {
        return -1;
    }
    dir->subdirs[dir->num_subdirs] = subdir;
    subdir->parent = dir;
    dir->num_subdirs++;
    return 0;
}
// Function to remove a subdirectory from a directory
int remove_subdir(Directory *dir, Directory *subdir) {
    int i, j;
    for (i = 0; i < dir->num_subdirs; i++) {
        if (dir->subdirs[i] == subdir) {
            // Shift all subsequent subdirs to left by one position
            for (j = i; j < dir->num_subdirs - 1; j++) {
                dir->subdirs[j] = dir->subdirs[j + 1];
            }
            // Update the number of subdirs in the parent directory
            dir->num_subdirs--;
            // Free the memory allocated for the subdir
            free(subdir);
            return 0;
        }
    }
    // Subdirectory not found
    return -1;
}

// Function to remove a directory recursively
void remove_directory(Directory *dir) {
    int i;
    // Recursively remove all subdirectories
    for (i = 0; i < dir->num_subdirs; i++) {
        remove_directory(dir->subdirs[i]);
    }
    // Free the memory allocated for the subdirs array
    free(dir->subdirs);
    // Free the memory allocated for the directory name
    free(dir->name);
    // Free the memory allocated for the directory itself
    free(dir);
}
