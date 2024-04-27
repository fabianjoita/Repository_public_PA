#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} NODE;

typedef struct G {
    int v;
    int *vis;
    struct Node **alst;
} GPH;

typedef struct S {
    int t;
    int *arr;
    int scap;
} STK;

NODE *create_node(int v) {
    NODE *nn = malloc(sizeof(NODE));
    nn->data = v;
    nn->next = NULL;
    return nn;
}

void add_edge(GPH *g, int src, int dest) {
    NODE *nn = create_node(dest);
    nn->next = g->alst[src];
    g->alst[src] = nn;

    nn = create_node(src);
    nn->next = g->alst[dest];
    g->alst[dest] = nn;
}

GPH *create_g(int v) {
    GPH *g = malloc(sizeof(GPH));
    g->v = v;
    g->alst = malloc(v * sizeof(NODE *));
    g->vis = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        g->alst[i] = NULL;
        g->vis[i] = 0;
    }

    return g;
}

STK *create_s(int scap) {
    STK *s = malloc(sizeof(STK));
    s->arr = malloc(scap * sizeof(int));
    s->t = -1;
    s->scap = scap;
    return s;
}

void push(int pshd, STK *s) {
    s->t++;
    s->arr[s->t] = pshd;
}

void DFS(GPH *g, STK *s, int v_nr) {
    NODE *adj_list = g->alst[v_nr];
    NODE *aux = adj_list;

    g->vis[v_nr] = 1;
    push(v_nr, s);

    while (aux != NULL) {
        int con_ver = aux->data;
        if (g->vis[con_ver] == 0)
            DFS(g, s, con_ver);
        aux = aux->next;
    }
}

void insert_edges(GPH *g, int edg_nr, int nrv) {
    int src, dest;
    for (int i = 0; i < edg_nr; i++) {
        printf("Introduceti nodul sursa si nodul destinatie pentru muchia %d: ", i + 1);
        scanf("%d%d", &src, &dest);
        add_edge(g, src, dest);
    }
}

void wipe(GPH *g, int nrv) {
    for (int i = 0; i < nrv; i++) {
        g->vis[i] = 0;
    }
}

void canbe(GPH *g, int nrv, STK *s1, STK *s2) {
    int *canbe = calloc(nrv, sizeof(int));

    for (int i = 0; i < nrv; i++) {
        DFS(g, s1, i);
        wipe(g, nrv);
        DFS(g, s2, i);

        for (int j = 0; j < nrv; j++) {
            if ((s1->arr[i] == j) && (s2->arr[j] == i)) {
                canbe[i] = 1;
                break;
            }
        }
    }

    printf("Nodurile accesibile intre cele doua stive sunt: ");
    for (int i = 0; i < nrv; i++) {
        if (canbe[i]) {
            printf("%d ", i);
        }
    }
    printf("\n");
    free(canbe);
}

int main() {
    int nrv, edg_nr;
    printf("Introduceti numarul de noduri ale grafului: ");
    scanf("%d", &nrv);

    GPH *g = create_g(nrv);

    printf("Introduceti numarul de muchii ale grafului: ");
    scanf("%d", &edg_nr);

    insert_edges(g, edg_nr, nrv);

    STK *s1 = create_s(2 * nrv);
    STK *s2 = create_s(2 * nrv);

    canbe(g, nrv, s1, s2);

    free(g->vis);
    free(g->alst);
    free(g);
    free(s1->arr);
    free(s1);
    free(s2->arr);
    free(s2);

    return 0;
}
