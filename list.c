#include<stdio.h>
#include<stdlib.h>
#include"list.h"

int i = 0;

LIST* createList(void){
	LIST* list=(LIST*)malloc(sizeof(LIST));//allocate memory at list.
	if(list == NULL)
		return NULL;//if allocating memory is failed return  NULL
	//head, tail, count initialize
	list->head = NULL;
	list->tail = NULL;
	list->count = 0;
	return list;
}

ListNode*  InsertList(LIST* plist,ListNode* prevlist, char* pData){
	plist->count++;
	//allocate memory in new node
	ListNode* newPtr = (ListNode*)malloc(sizeof(ListNode));
	if(newPtr == NULL)
		return NULL;//if allocating memory failed return NULL
	newPtr->next = NULL;
	newPtr->key = i++;
	newPtr->dataPtr = pData;
	
	if(prevlist==NULL){//if previous node doesn't exist
		if(plist->tail == NULL)//when first node add
			plist->tail == newPtr;//tail = new node
		//when add new node at the end of list
		newPtr->next = plist->head;
		plist->head = newPtr;
	}
	else{//when add new node at between two already existing node
		newPtr->next = prevlist->next;
		prevlist->next = newPtr;
		if(newPtr->next == NULL)
			plist->tail == newPtr;
	}
	return newPtr;
}

void KEY_view(LIST* pList){
	
	if(pList->head == NULL)//it means list has not the node
		printf("There is no data.\n");
	else{//read start last input node
		ListNode *readNode = pList->head;
		//print  while readNode = first input node
		while(readNode->next != NULL || readNode == pList->tail){
			printf("key : %d \t data : %s",readNode->key,readNode->dataPtr);
			if(readNode == pList->tail)
				break;
			readNode = readNode->next;
		}
		printf("key : %d \t data : %s",readNode->key,readNode->dataPtr);
	}

	return ;//end this function
}

int itemNum(LIST* pList)
{
	return pList->count ;//receive number of list node
}

ListNode* SearchNode(LIST* pList, int keyNum){
	ListNode* tempNode = pList->head;
	//tempNode find the node having key that equal keyNum 
	while(tempNode->next != NULL){//while tempNode is not end node of list
		if(tempNode->key != keyNum)
			tempNode = tempNode->next;
		else
			break;//when key of tempNode equal keyNum, terminate this loop
	}
	//when keyNum doesn't exist
	if(tempNode->next == NULL && tempNode->key != keyNum){
		printf("Data you want does not exist.\n");
		return NULL;
	}
	
	return tempNode;
}

void DeleteListNode(LIST* pList, int keyNum){
	ListNode* DeleteNode = SearchNode(pList,keyNum);
	//if DeleteNode doesn't exist, this function is ended
	if (DeleteNode == NULL)
		return;
	//tempNode points previous node of DeleteNode
	ListNode* tempNode = pList->head;

	if(DeleteNode == tempNode){//if you want to delete last input node
		if(pList->tail == pList-> head){//if there is only one node in list
			pList->tail == NULL;
			pList->head == NULL;
		}
		else
			pList->head = DeleteNode->next;
	}
	else//if you want to delete node existing between of nodes
		while(tempNode->next != DeleteNode)
			tempNode = tempNode->next;//find previous node of DeletNode
	if(DeleteNode == pList->tail)//if you want to delete node first input node
		pList->tail = tempNode;
	//connect previous node of DeleteNode and next  node of it
	tempNode->next = DeleteNode->next;
	//delete Deletenode.
	DeleteNode->key = 0;
	DeleteNode->next = NULL;
	free(DeleteNode->dataPtr);
	free(DeleteNode);

	pList->count--;//count - 1
	return ;
}

void DeleteListAll(LIST*pList,char select){
//tempNode points next node of DeleteNode 
//for move DeleteNode after deleting node
	ListNode* DeleteNode = pList->head;
	ListNode* tempNode = pList->head;
	while(DeleteNode != NULL){
		tempNode = tempNode->next;
		DeleteNode->key = 0;
		DeleteNode->next = NULL;
		free(DeleteNode->dataPtr);
		free(DeleteNode);
		DeleteNode = tempNode;
	}

	free(DeleteNode);
	free(tempNode);
	//if you want to remain list selete = 'D'
	if(select == 'D'){
		pList->head = NULL;
		pList->tail = NULL;
		pList->count = 0;
	}
	else{//if you want to delete list completely
		pList->count = 0;
		free(pList->head);
		free(pList->tail);
		free(pList);
	}
	return ;
}

char* headData(LIST* pList){//receive data of last input node
	return pList->head->dataPtr;
}

char* tailData(LIST* pList){//receive data of first input node
	return pList->tail->dataPtr;
}
/*
void listPrint(LIST* plist){
	char* item;
	ListNode* temp = (ListNode*)malloc(sizeof(ListNode));
	temp = plist->tail;
	while(temp->next != NULL){
		item = temp->dataPtr;
		printf("%s\n",item);
		temp = temp->next;
	}
	
	printf("%s\n",temp->dataPtr);
	return ;
}


int main(void){
	
	char* item;
	LIST* list = createList();
	int a;
	int key;
	ListNode* prvNode = (ListNode*)malloc(sizeof(ListNode));
	prvNode = NULL;

	for(a = 0 ; a<10 ; a++)
	{
		item = (char*)malloc(sizeof(char)*80);
		fgets(item,sizeof(item),stdin);
		prvNode =  InsertList(list,prvNode,item);
	}

	KEY_veiw(list)
	for(a = 0; a<10 ; a++)	{
		printf("Enter the key : ");
		scanf("%d",&key);
		DeleteListNode(list,key);
		KEY_veiw(list);
	}
	DeleteListAll(list,'D');

	KEY_veiw(list);
	return 0;
}
*/
