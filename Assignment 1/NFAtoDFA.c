/*
Number of states in NFA = 4 (It stands for state q0, q1, q2, and q3)
Number of symbols in NFA = 2 (It stands for symbol 0 and 1)
Start State = 0 (It stands for state q0)
Final States = 1  (There is only one final/accepting state, named q3)
3
Transition Function

1 0 3 0 1 2           Transition for q0 ->  q0  q0,q1,q2
1 2 1 3               Transition for q1 ->  q2  q3
0 1 3                 Transition for q2 ->  -   q3
1 3 1 3               Transition for q3 ->  q3  q3

Input:

4
2
0
1 3
1 0 3 0 1 2
1 2 1 3
0 1 3
1 3 1 3


Transition for q0 ->  q1  q3
Transition for q1 ->  -   q3
Transition for q2 ->  q2  q2,q0,q1
Transition for q3 ->  q3  q3

4
2
2
1 3
1 1 1 3
0 1 3
1 2 3 2 0 1
1 3 1 3

4
2
0
1 3
1 0 2 0 1
1 2 1 2
1 3 1 3
0 0
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct trans {
    int **state;
    int *DFAstate;
    int isFinal;
    int isStart;
    struct trans *next;
} trans;

trans *head;
trans *curr;
trans *tail;
int   DFAstateID = 0;

int populateDFATransitionTable(int n, int m, int j, int curr_state[], int new_state[], int TF[][m][n]);
void printNFATransitionTable(int n, int m, int st, int isFinal[], int TF[][m][n]);
void printDFATransitionTable(int n, int m, int st, int isFinal[]);
trans *initializeTransition(int n, int m);
trans *getStartStateNFA(int n, int m, int st, int X[][m]);
int isFinalState(int n, int state[], int st, int isFinal[]);

int main()
{
    int i, j, k;
    int n, m, st, fn;

    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &st);
    scanf("%d", &fn);

    int isFinal[n];
    for(i = 0; i < n; i++)
        isFinal[i] = 0;
    for(i = 0; i < fn; i++) {
        scanf("%d", &k);
        isFinal[k] = 1;
    }

    int TF[n][m][n], nState, state;
    for(i = 0; i < n; i++)
        for(j = 0; j < m; j++)
            for(k = 0; k < n; k++)
                TF[i][j][k] = 0;

    for(i = 0; i < n; i++) {
        for(j = 0; j < m; j++) {
            scanf("%d", &nState);
            if(nState == 0)
                continue;
            for(k = 0; k < nState; k++) {
                scanf("%d", &state);
                TF[i][j][state] = 1;
            }
        }
    }

    printNFATransitionTable(n, m, st, isFinal, TF);

    head = initializeTransition(n, m);

    head = getStartStateNFA(n, m, st, TF[st]);

    while(curr != NULL) {
        for(j = 0; j < m; j++) {
            int new_state[n];
            int idDFAstate = populateDFATransitionTable(n, m, j, curr->state[0], new_state, TF);
            if(idDFAstate == -1) {
                trans *t = initializeTransition(n, m);
                idDFAstate = DFAstateID-1;
                for(i = 0; i < n; i++) {
                    t->state[0][i] = new_state[i];
                    if(new_state[i] == 1 && isFinal[i] == 1)
                        t->isFinal = 1;
                }
                tail->next = t;
                tail = t;
            }
            for(i = 0; i < n; i++)
                curr->state[j+1][i] = new_state[i];
            curr->DFAstate[j+1] = idDFAstate;
        }
        curr = curr->next;
    }

    printDFATransitionTable(n, m, st, isFinal);

    return 0;
}

int populateDFATransitionTable(int n, int m, int j, int curr_state[], int new_state[], int TF[][m][n])
{
    int i, k;
    for(i = 0; i < n; i++)
        new_state[i] = 0;

    for(i = 0; i < n; i++) {
        int x = curr_state[i];
        if(x == 1) {
            for(k = 0; k < n; k++) {
                new_state[k] = new_state[k] | TF[i][j][k];
            }
        }
    }

    trans *t = head;
    while(t != NULL) {
        for(i = 0; i < n; i++) {
            if(new_state[i] != t->state[0][i])
                break;
        }
        if(i == n)
            return t->DFAstate[0];
        t = t->next;
    }
    return -1;
}

trans *getStartStateNFA(int n, int m, int st, int T[][n])
{
    head->state[0][st] = 1;
    head->isStart = 1;
    curr = head;
    tail = head;
    return head;
}

trans *initializeTransition(int n, int m)
{
    int i;
    trans *t = (trans *)malloc(sizeof(trans));
    t->isStart = 0;
    t->isFinal = 0;
    t->next = NULL;
    t->state = (int **)calloc(m+1, sizeof(int *));
    for(i = 0; i < m+1; i++)
        t->state[i] = (int *)calloc(n, sizeof(int));
    t->DFAstate = (int *)calloc(m+1, sizeof(int));
    t->DFAstate[0] = DFAstateID++;
    return t;
}

void printDFATransitionTable(int n, int m, int st, int isFinal[])
{
    trans *t = head;
    while(t != NULL) {
        int j, k;
        for(j = 0; j < m+1; j++) {
            printf("{");
            for(k = 0; k < n; k++) {
                if(t->state[j][k] == 1)
                    printf("q%d", k);
                else
                    printf("  ");
            }
            printf("} = ");
            printf("Q%d", t->DFAstate[j]);
            if(j == 0 && t->isStart == 0 && t->isFinal == 0)
                printf("(  )  |  ");
            else if(j == 0 && t->isStart == 0 && t->isFinal == 1)
                printf("(F )  |  ");
            else if(j == 0 && t->isStart == 1 && t->isFinal == 0)
                printf("(S )  |  ");
            else if(j == 0 && t->isStart == 1 && t->isFinal == 1)
                printf("(SF)  |  ");
            else
                printf("  |  ");
        }
        t = t->next;
        printf("\n");
    }
}

void printNFATransitionTable(int n, int m, int st, int isFinal[], int TF[][m][n])
{
    printf("\n");
    int i, j, k;

    for(i = 0; i < n; i++) {
        if(i == st && isFinal[i] == 1)
            printf(" q%d(SF) | ", i);
        else if(i == st)
            printf(" q%d(S ) | ", i);
        else if(isFinal[i] == 1)
            printf(" q%d(F ) | ", i);
        else
            printf(" q%d(  ) | ", i);

        for(j = 0; j < m; j++) {
            for(k = 0; k < n; k++) {
                if(TF[i][j][k] == 1)
                    printf("q%d", k);
                else
                    printf("q_");
            }
            printf(" | ");
        }
        printf("\n");
    }
    printf("\n");
}

