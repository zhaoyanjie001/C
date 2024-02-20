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
void tail_insert(list *pH , list *new)
{
	//获取当前的位置 
	list *p = pH ; 
	//如果当前位置的下一个节点不为空 
	while(NULL != p->next)
	{
		//移动到下一个节点 
		p = p->next ;
	}
	//如果跳出以上循环，所以已经到了NULL的这个位置
	//此时直接把新插入的节点赋值给NULL这个位置 
	p->next = new ;
}
void top_insert(list *pH , list *new){
    list *p =pH;
    new ->next =p->next;
	p->next = new;
}
void Print_node(list *pH)
{
	//获取当前的位置 
	list *p = pH ;
	//获取第一个节点的位置 
	p= p->next ;
	//如果当前位置的下一个节点不为空 
	while(NULL != p->next)
	{
		//(1)打印节点的数据 
		printf("id:%d\n",p->id);
		//(2)移动到下一个节点,如果条件仍为真，则重复(1)，再(2) 
		p = p->next ;
	}
	//如果当前位置的下一个节点为空，则打印数据
	//说明只有一个节点 
	printf("id:%d\n",p->id);
}
int delete_list_node(list * pH , int data){
    list *p = pH;
    list *prev = NULL;
    while(NULL != p->next) {
        prev = p;
        p = p->next;
		printf("删除的节点信息:%d\n", p->id);
        if(p->id == data) {
            if(p->next != NULL) {
                prev ->next = p->next;
                
				printf("删除的节点:%d\n", p->id);
				free(p);
            } else {
                prev->next = NULL;
				printf("删除的节点:%d\n", p->id);
                free(p);
            }
            return 0;
        }
    }
	printf("没有要删除的节点\n");
	return -1 ;
}

void trave_list(list * pH)
{
	list *p = pH->next;
	list *pBack;
	int i = 0 ;
	if(p->next == NULL || p == NULL)
		return ;
		
	while(NULL != p->next)
	{ 
		pBack = p->next ; 
		if(p == pH->next) 
		{
			p->next = NULL ; 
		} 
		else
		{
			p->next = pH->next ; 
		}
		pH->next = p ;
		p = pBack ;
	}
	top_insert(pH,p);
}

int main(int argc , char **argv) 
{
	int i ;
	list *header = create_node(0); 
	for(i = 1 ; i < 10 ; i++)
	{
		tail_insert(header,create_node(i));
	}
	Print_node(header);
	
	delete_list_node(header,5);
	Print_node(header);
	putchar('\n');
	printf("-------\n");
	trave_list(header);
	Print_node(header);
	return 0 ;
}
