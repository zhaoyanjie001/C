#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct  list_node
{
	int data ; 
	struct list_node *next ;
};
 
typedef struct list_node list_single ; 	
 
int main(void)
{
	list_single *node = NULL ;          //1、首先，当然是定义一个头指针
	node = (list_single *)malloc(sizeof(list_single)); //2、然后分配内存空间
	list_single *node1 = NULL ;          //1、首先，当然是定义一个头指针
	node1 = (list_single *)malloc(sizeof(list_single)); //2、然后分配内存空间
	if(node == NULL){
		printf("malloc fair!\n");
	}
	memset(node,0,sizeof(list_single)); //3、清一下
	node->data = 100 ;		    		//4、给链表节点的数据赋值
	       
	memset(node1,0,sizeof(list_single)); //3、清一下
	node1->data = 101 ;		    		//4、给链表节点的数据赋值
	node->next = node1;     
	node1->next = NULL ;                 //5、将链表的指针域指向空
	printf("%d\n",node->data);
	printf("%d\n",node->next->data);
	free(node);
	return 0 ;
}
