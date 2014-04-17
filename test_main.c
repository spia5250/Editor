#include<stdio.h>
#include<stdlib.h>
#include"list.h"
//i is global variable in list.h
extern int i;

int main(void){
	char* item;//for pointing data
	LIST* list = createList();//create new list
	int a;
	char b;//for selecting yes or no
	int key;//for deleting node using key
	ListNode* prvNode = (ListNode*)malloc(sizeof(ListNode));
	prvNode = NULL;
	//receive data 10times. data is string
	for(a = 0 ; a < 10 ; a++){
		item = (char*)malloc(sizeof(char)*80);//maximum number of charater is 80
		fgets(item,sizeof(char)*80,stdin);//data receiving  until receive enter
		prvNode = InsertList(list,prvNode,item);//insert node
	}
	KEY_view(list);//printf node data
	
	//delete data using key 5times
	for(a = 0 ; a<5 ; a++){
		printf("Enter the key : ");
		scanf("%d",&key);
		DeleteListNode(list,key);
		KEY_view(list);
		__fpurge(stdin);//for empty buffer
	}
	//select remove all or no
	printf("Do you want to remove remain nodes? (Y / N) : ");
	scanf("%c",&b);

	if(b == 'Y')
		DeleteListAll(list,'D');//remove all but remain list.
	printf("Remain nodes\n");
	KEY_view(list);
	
	return 0;//program is ended.
}

