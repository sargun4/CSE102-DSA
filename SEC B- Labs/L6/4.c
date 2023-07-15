#include <stdio.h>
#include <stdlib.h>
#define MAX_CHILDREN 100000
struct node {
    int child;
    struct node* next;
};
struct graph {
    int no_children;
    struct node** adjlist;
};

struct node* createnode(int child) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->child = child;
    temp->next = NULL;
    return temp;
}

struct graph* creategraph(int no_children) {
    struct graph* g = (struct graph*)malloc(sizeof(struct graph));
    g->no_children = no_children;
    g->adjlist = (struct node**)malloc(no_children * sizeof(struct node*));
    for (int i = 0; i < no_children; i++) {
        g->adjlist[i] = NULL;
    }

    return g;
}

void addEdge(struct graph* g, int child1, int child2) {
    struct node* temp = createnode(child2);
    temp->next = g->adjlist[child1];
    g->adjlist[child1] = temp;

    temp = createnode(child1);
    temp->next = g->adjlist[child2];
    g->adjlist[child2] = temp;
}
void DFS(struct graph* g, int vertex, int* visited, int* color, int team) {
    visited[vertex] = 1;
    color[vertex] = team;

    struct node* temp = g->adjlist[vertex];
    while (temp != NULL) {
        int child = temp->child;
        if (!visited[child]) {
            DFS(g, child, visited, color, !team);
        }
        temp = temp->next;
    }
}

int canformteams(struct graph* g) {
    int visited[MAX_CHILDREN] = {0};
    int color[MAX_CHILDREN] = {0};

    for (int vertex = 0; vertex < g->no_children; vertex++) {
        if (!visited[vertex]) {
            DFS(g, vertex, visited, color, 0);
        }
    }
    // Check if any adjacent children have the same team color
    for (int vertex = 0; vertex < g->no_children; vertex++) {
        struct node* temp = g->adjlist[vertex];
        while (temp != NULL) {
            int child = temp->child;
            if (color[vertex] == color[child]) {
                return 0;  // Children who are friends are in the same team
            }
            temp = temp->next;
        }
    }
    return 1;  // Children can be divided into two teams
}
void freegraph(struct graph* g) {
    for (int i = 0; i < g->no_children; i++) {
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

int main() {
    int no_children, n0_Friendships;
    scanf("%d %d", &no_children, &n0_Friendships);
    struct graph* g = creategraph(no_children);
    for (int i = 0; i < n0_Friendships; i++) {
        int child1, child2;
        scanf("%d %d", &child1, &child2);
        addEdge(g, child1 - 1, child2 - 1);  // Adjusting indices to 0-based
    }
    if (canformteams(g)) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    freegraph(g);
    return 0;
}
