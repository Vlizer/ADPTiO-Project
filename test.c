#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    true=1, false=0
}bool;
struct position{
    int x;
    int y;
};

struct move{
    struct position from;
    struct position to;
    struct move* next;
};



void print(int n, int **t, int k);
void findMoves(int n, int **t, int startX, int startY,struct move **headMoveList);
void addToMovesList(int fromY, int fromX, int toY, int toX,struct move **headMoveList);
int countTab(int n, int **t);


//DEBUGS
void printTab(int n, int **t);
void printList(struct move* head);

int main(){
    int size = 8;
    int ** t = malloc(size * sizeof(int*));
    for(int i=0;i<size;i++){
        t[i] = malloc(size*sizeof(int));
    }
    t[0][0] = 0; t[0][1] = 1;  t[0][2]=0;  t[0][3] = 0; t[0][4] = 0; t[0][5] = 0; t[0][6] = 0; t[0][7] = 0;
    t[1][0] = 1; t[1][1] = 2;  t[1][2]=8;  t[1][3] = 8; t[1][4] = 0; t[1][5] = 0; t[1][6] = 8; t[1][7] = 0;
    t[2][0] = 0; t[2][1] = 2;  t[2][2]=16; t[0][3] = 0; t[2][4] = 0; t[2][5] = 0; t[2][6] = 0; t[2][7] = 0;
    t[3][0] = 0; t[3][1] = 16; t[3][2]=0;  t[3][3] = 0; t[3][4] = 0; t[3][5] = 0; t[3][6] = 0; t[3][7] = 0;
    t[4][0] = 0; t[4][1] = 0;  t[4][2]=0;  t[4][3] = 0; t[4][4] = 0; t[4][5] = 0; t[4][6] = 0; t[4][7] = 0;
    t[5][0] = 0; t[5][1] = 0;  t[5][2]=0;  t[5][3] = 0; t[5][4] = 1; t[5][5] = 0; t[5][6] = 1; t[5][7] = 0;
    t[6][0] = 0; t[6][1] = 0;  t[6][2]=0;  t[6][3] = 0; t[6][4] = 0; t[6][5] = 0; t[6][6] = 0; t[6][7] = 0;
    t[7][0] = 0; t[7][1] = 0;  t[7][2]=0;  t[7][3] = 0; t[7][4] = 0; t[7][5] = 0; t[7][6] = 0; t[7][7] = 0;
    print(size,t,1);
    
    
    for(int i=0;i<size;i++){
        free(t[i]);
    }
    free(t);
    return 0;
}

void print(int n, int **t, int k){
    
    struct move *headMoveList = NULL;
    for(int y = 0 ; y < n ; y++){
        for(int x = 0; x < n ; x++){
            if(t[y][x] != 0 ){
            	findMoves(n,t,y,x,&headMoveList);
            }
        }
    }
    if(countTab(n,t) == k ){
        return;
    }
    struct move *m = headMoveList;
    while(m!= NULL){
            t[m->to.y][m->to.x] = t[m->to.y][m->to.x] * 2;
            t[m->from.y][m->from.x] = 0;
            print(n,t,k);
            if(countTab(n,t)==k){
                printf("%d %d %d %d\n",m->from.x,m->from.y,m->to.x,m->to.y);
                return;
            }
            t[m->to.y][m->to.x] = t[m->to.y][m->to.x] / 2;
            t[m->from.y][m->from.x] = t[m->to.y][m->to.x];
            m = m->next;
    }

}
void findMoves(int n, int **t, int posY, int posX, struct move **headMoveList){
    //lewo
    for(int i=posX-1;i>=0;i--){
        if(t[posY][i] != 0 && t[posY][i] != t[posY][posX])
            break;
        if(t[posY][posX] == t[posY][i]){
           addToMovesList(posY,posX,posY,i,headMoveList);
        }
    }
    //gora
    for(int i=posY-1;i>=0;i--){
        if(t[i][posX] != 0 && t[i][posX] != t[posY][posX])
            break;
        if(t[posY][posX] == t[i][posX]){
           addToMovesList(posY,posX,i,posX,headMoveList);
        }
    }
    //prawo
    for(int i=posX+1;i < n;i++){
        if(t[posY][i] != 0 && t[posY][i] != t[posY][posX])
            break;
        if(t[posY][posX] == t[posY][i]){
           addToMovesList(posY,posX,posY,i,headMoveList);
        }
    }
    //dol
    for(int i=posY+1;i < n;i++){
        if(t[i][posX] != 0 && t[i][posX] != t[posY][posX])
            break;
        if(t[posY][posX] == t[i][posX]){
           addToMovesList(posY,posX,i,posX,headMoveList);
        }
    }
    //lewo gora
    for(int i = 1 ; posX-i >= 0 && posY - i >= 0; i++){
        if(t[posY - i][posX - i] != 0 && t[posY - i][posX - i] != t[posY][posX])
            break;
        if(t[posY][posX] == t[posY - i][posX - i]){
           addToMovesList(posY,posX,posY-i,posX-i,headMoveList);
        }
    }
    //prawo gora
    for(int i = 1 ; posX+i < n && posY - i >= 0; i++){
        if(t[posY - i][posX + i] != 0 && t[posY - i][posX + i] != t[posY][posX])
            break;
        if(t[posY][posX] == t[posY - i][posX + i]){
           addToMovesList(posY,posX,posY-i,posX+i,headMoveList);
        }
    }
    //prawo dol
    for(int i = 1 ; posX+i < n && posY + i < n; i++){
        if(t[posY + i][posX + i] != 0 && t[posY + i][posX + i] != t[posY][posX])
            break;
        if(t[posY][posX] == t[posY + i][posX + i]){
           addToMovesList(posY,posX,posY+i,posX+i,headMoveList);
        }
    }
    ///lewo dol
    for(int i = 1 ; posX-i >= 0  && posY + i < n; i++){
        if(t[posY + i][posX - i] != 0 && t[posY + i][posX - i] != t[posY][posX])
            break;
        if(t[posY][posX] == t[posY + i][posX - i]){
            addToMovesList(posY,posX,posY+i,posX-i,headMoveList);
        }
    }
}

void addToMovesList(int fromY, int fromX, int toY, int toX, struct move **headMoveList){
    struct move *result = malloc(sizeof(struct move));
    result->from.x = fromX;
    result->from.y = fromY;
    result->to.x = toX;
    result->to.y = toY;
    
    if(*headMoveList == NULL){
        *headMoveList = result;
        (*headMoveList)->next = NULL;
    }else{
        result->next = *headMoveList;
        *headMoveList = result;
    }
}

int countTab(int n, int **t){
    int count = 0;
    for(int y = 0 ; y < n ; y++){
        for(int x = 0; x < n ; x++){
            if(t[y][x] != 0 ){
            	count +=1;
            }
        }
    }
    return count;
}


//DEBUGS

void printTab(int n, int **t){
    printf("\n\t\t\tPRINTING TAB\n");
    for(int y = 0; y < n; y++){
        for(int x = 0; x < n; x++){
            printf("\t%d",t[y][x]);
        }
        printf("\n");
    }
        
}
void printList(struct move *head){
    printf("\n\t\t\tPRINTING LIST\n");
    struct move* temp = head;
    while(temp != NULL){
        printf("%d\t%d\t%d\t%d\n",temp->from.x,temp->from.y,temp->to.x,temp->to.y);
        temp = temp->next;
    }
}