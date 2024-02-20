#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct list
{
	int id ;
	struct list *next ;			
} list;

list *create_node(int data){

    list *p = malloc(sizeof(list));
    if(NULL = p) {
        printf("malloc error!\n");
        return NULL ;
    }
    memset(p,0,sizeof(list));
    p->id=data;
    p->next = NULL;
}

void top_insert(list *pH , list *new){
    list *p =pH;
    new ->next =p->next;
}
void Print_node(list *pH){
    list *p =pH;
    p-p->next;
    while(NULL != p->next){
        printf("id:%d\n",p->id);
        p = p->next ;
    }
    printf("id:%d\n",p->id);
}