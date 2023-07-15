// Create a directed g with n vertices to represent the no_of_courses.
// Read the prerequisites from the input and add directed edges to the g accordingly.
// Perform a depth-first search (DFS) on the g to check for cycles.
// For each course, start a DFS visit if it hasn't been visited before.
// During the DFS visit, mark the current course as visited and recursively visit its prerequisites.
// If a visited course is encountered during the visit, it indicates a cycle.
// If a cycle is found in the g, print "No". Otherwise, print "Yes".

#include <stdio.h>
#include <stdlib.h>
#define MAX_COURSES 100000

struct node {
    int course;
    struct node* next;
};
struct node* createnode(int course) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->course = course;
    temp->next = NULL;
    return temp;
}
struct graph {
    int no_of_courses;
    struct node** adjlist;
};
struct graph* creategrph(int no_of_courses) {
    struct graph* g = (struct graph*)malloc(sizeof(struct graph));
    g->no_of_courses = no_of_courses;

    g->adjlist = (struct node**)malloc(no_of_courses * sizeof(struct node*));
    for (int i = 0; i < no_of_courses; i++) {
        g->adjlist[i] = NULL;
    }
    return g;
}
void addedge(struct graph* g, int course1, int course2) {
    struct node* temp = createnode(course2);
    temp->next = g->adjlist[course1];
    g->adjlist[course1] = temp;
}
void freeagrph(struct graph* g) {
    for (int i = 0; i < g->no_of_courses; i++) {
        struct node* temp = g->adjlist[i];
        while (temp != NULL) {
            struct node* prev = temp;
            temp = temp->next;
            free(prev);
        }
    }
    free(g->adjlist);
    free(g);
}
int has_cycle_DFS(struct graph* g, int course, int* visited, int* onStack) {
    visited[course] = 1;
    onStack[course] = 1;
    struct node* temp = g->adjlist[course];
    while (temp != NULL) {
        int prereq = temp->course;
        if (!visited[prereq]) {
            if (has_cycle_DFS(g, prereq, visited, onStack))
                return 1;
        } else if (onStack[prereq]) {
            return 1;  // Cycle detected
        }
        temp = temp->next;
    }
    onStack[course] = 0;

    return 0;
}
int has_cycle(struct graph* g) {
    int no_of_courses = g->no_of_courses;
    int* visited = (int*)calloc(no_of_courses, sizeof(int));
    int* onStack = (int*)calloc(no_of_courses, sizeof(int));

    for (int i = 0; i < no_of_courses; i++) {
        if (!visited[i]) {
            if (has_cycle_DFS(g, i, visited, onStack)) {
                free(visited);
                free(onStack);
                return 1;  // Cycle detected
            }
        }
    }

    free(visited);
    free(onStack);

    return 0;
}

int main() {
    int no_of_courses, numPrerequisites;
    scanf("%d %d", &no_of_courses, &numPrerequisites);

    struct graph* g = creategrph(no_of_courses);

    for (int i = 0; i < numPrerequisites; i++) {
        int course1, course2;
        scanf("%d %d", &course1, &course2);
        addedge(g, course1 - 1, course2 - 1);
    }

    if (has_cycle(g))
        printf("No\n");
    else
        printf("Yes\n");
    freeagrph(g);
    return 0;
}


// The visited array is used to mark a course as visited when it is first encountered during the DFS traversal. This helps in preventing infinite loops and ensures that each course is visited only once.

// The onStack array is used to detect cycles in the g. It keeps track of the courses that are currently in the call stack. If a course is encountered during the DFS traversal and it is already present in the onStack array, it means that there is a cycle in the g.

// Here's an explanation of how the arrays are used in the has_cycle_DFS function:

// When a course course is visited for the first time, it is marked as visited by setting visited[course] to 1.

// Then, course is added to the onStack array by setting onStack[course] to 1.

// The function recursively visits the prerequisites of course and checks if any of them are already visited or present in the onStack array. If a prereq is visited and also on the stack, it indicates a cycle in the g, and the function returns 1 to indicate the presence of a cycle.

// After visiting all the prerequisites of course, course is removed from the onStack array by setting onStack[course] to 0.

// Finally, if no cycle is detected during the DFS traversal, the function returns 0 to indicate the absence of a cycle.