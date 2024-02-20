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
    if(NULL == p) {
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
int delete_list_node(list * pH , int data){
    list *p =pH;
    list *prev = NULL;
    while(NULL != p->next) {
        prev = p;
        p = p->next;
        if(p->id == data) {
            if(p->next != NULL) {
                prev ->next = p->next;
                free(p);
            } else {
                prev->next = NULL;
                free(p);
            }
            return 0;
        }
        printf("没有要删除的节点\n");
	    return -1 ;
    }
}

void trave_list(list * pH)
{
	//保存第一个节点的位置 
	list *p = pH->next;
	list *pBack;
	int i = 0 ;
	if(p->next == NULL || p == NULL)
		return ;
		
	while(NULL != p->next) //遍历链表 
	{
		//保存第一个节点的下一个节点 
		pBack = p->next ; 
		//找到第一个有效节点,其实就是头指针的下一个节点 
		if(p == pH->next) 
		{
			//第一个有效节点就是最后一个节点，所以要指向NULL 
			p->next = NULL ; 
		} 
		else
		{
			p->next = pH->next ; //尾部连接 
		}
		pH->next = p ; //头部连接 
		p = pBack ; //走下一个节点 
	}
	top_insert(pH,p); //插入最后一个节点 
}

int main(int argc , char **argv) 
{
	//创建第一个节点 
	int i ;
	list *header = create_node(0); 
	for(i = 1 ; i < 10 ; i++)
	{
		tail_insert(header,create_node(i));
	}
	Print_node(header);

	return 0 ;
}
