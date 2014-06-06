#include<stdio.h>
#include<stdlib.h>
#include"list.h"


const int max_line = 25;
const int max_col = 80;

int i = 0;

LIST* createList(void){
	LIST* list=(LIST*)malloc(sizeof(LIST));//allocate memory at list.
	if(list == NULL)
		return NULL;//if allocating memory is failed return  NULL
	//head, tail, count initialize
	list->head = NULL;
	list->tail = NULL;
	list->line_count = 0;
	return list;
}

void save_list(LIST* plist,FILE* fp){
//	char buff[81];
//	fp = fopen("TEST.txt","w");
	int n = 0;
	ListNode* temp = plist->head;
	while(temp->next != NULL){
		for(;n<=80;n++)
			fprintf(fp,"%c",temp->data[n]);
	//	fputs(buff,fp);
		temp = temp->next;
	}
	return ;
}

void key_modify(ListNode* line,int line_num){
	if(line == NULL)
		return;
	while(line->next != NULL){
		line->key = line_num++;		
	}
	return;
}

void print_Data(LIST* plist, int line, int col ){

	ListNode* temp = SearchLine(plist, line);
	if(col==80){
		printf("\n");
		col = 0;
		temp = temp->next;
	}
	while(temp->data[col] != '\0'){
		if(col <  max_col){
			printf("%c",temp->data[col]);
			col++;
			if(col==80){
				printf("\n");
				col = 0;
				temp = temp->next;
			}
		}
//		else{
//			printf("Ch");
//			printf("\n");
//			col = 0;
//			temp = temp->next;
//		}
	}
	return ;
}

ListNode* SearchLine(LIST* pList, int keyNum){
	ListNode* tempNode = pList->head;
	//tempNode find the node having key that equal keyNum
	if (tempNode == NULL) return tempNode;

	while(tempNode->next != NULL){//while tempNode is not end node of list
		if(tempNode->key != keyNum)
			tempNode = tempNode->next;
		else
			break;//when key of tempNode equal keyNum, terminate this loop
	}
	return tempNode;
}

//tail = last line, head = first line
ListNode* InsertLine(LIST* plist, int prevline_num){
	int n = 0;
	plist->line_count++;
	//allocate memory in new node
	ListNode* newPtr = (ListNode*)malloc(sizeof(ListNode));
	ListNode* prevline = SearchLine(plist,prevline_num);
	if(newPtr == NULL)
		return ;//if allocating memory failed return NULL
	newPtr->next = NULL;
	newPtr->key = prevline_num+1;
	while(n<=max_col){
		newPtr->data[n] = '\0';
		n++;
	}
	if(prevline==NULL){//if previous node doesn't exist
		if(plist->tail == NULL)//when first node add
			plist->tail = newPtr;//tail = new node
		//when add new node at the end of list
		newPtr->next = plist->head;
		plist->head = newPtr;
	}
	else{//when add new node at between two already existing node
		newPtr->next = prevline->next;
		prevline->next = newPtr;
		if(newPtr->next == NULL)
			plist->tail = newPtr;
	}

	key_modify(newPtr->next,newPtr->key+1);

	return newPtr;
}

int SearchData_NULL(LIST* plist, ListNode* startline, int start_col){
	char* nullp;
	int num = 0;
	nullp = &startline->data[start_col];
	while(*nullp != '\0'){
		if (start_col<=max_col-1){
			nullp = &startline->data[start_col];
			num++;
			start_col++;
		}
		else if(start_col==80){
				startline = startline->next;
				start_col -= max_col;
			
		}
	}
	return num;
}
	

//col_num = col_num(in main)-1
void InsertData(LIST* plist, int line_num, int col_num, char dat){
	ListNode* temp = SearchLine(plist,line_num);
	int a = col_num;
	int b = 0;
	char temp_c;
//	if(temp == NULL && plist->head ==NULL){
//		temp = InsertLine(plist, 0);
//		temp->data[max_col] = '\n';
//	}
	if(temp->next == NULL){
		temp->data[max_col] = ' ';
		temp = InsertLine(plist,line_num-1);
		temp->data[max_col] = '\n';
	}	
	if(temp->data[max_col]=='\n' && temp->data[max_col-1] !='\0'){//when enter array store '\n' char in data[80]	
			InsertLine(plist,line_num);
			temp->next->data[max_col] = '\n';
			temp->data[max_col] = ' ';
	}//end if

	if(temp->data[col_num] == '\0'){ 
		if (col_num < max_col)//empty data
			temp->data[col_num] = dat;//end if
		else{
			temp = temp->next;
			col_num = 0;
			temp->data[col_num] = dat;
		}
		
	}
	else{ //enter the middle
		int b = SearchData_NULL(plist,temp,col_num);
		while(b>=0){
			while(a < max_col){
				temp_c = temp->data[a];
				temp->data[a] = dat;
				dat = temp_c;
				a++;
				b--;
				if(b<0){
				//	temp->data[] = '\0';
					break;
				}
			}//end while(a);
			if(a == max_col && temp->data[max_col] =='\n'){
				temp->data[max_col] = ' ';
				temp = InsertLine(plist,temp->key);
				temp->data[max_col] = '\n';
			}//end if
			if(temp->next != NULL)
				temp = temp->next;
			else
				temp = InsertLine(plist,line_num);//end else
			a = 0;
		}//end while(b)
	}//end else
	print_Data(plist,line_num,col_num+1);
	return ;		
}


void KEY_view(LIST* pList){
	
	if(pList->head == NULL)//it means list has not the node
		printf("There is no data.\n");
	else{//read start last input node
		ListNode *readNode = pList->head;
		//print  while readNode = first input node
		while(readNode->next != NULL || readNode == pList->tail){
			printf("key : %d \t data : %s",readNode->key,readNode->data);
			if(readNode == pList->tail)
				break;
			readNode = readNode->next;
		}
		printf("key : %d \t data : %s",readNode->key,readNode->data);
	}

	return ;//end this function
}

int itemNum(LIST* pList)
{
	return pList->line_count ;//receive number of list node
}


/*
void DeleteListNode(LIST* pList, int keyNum){
	ListNode* DeleteNode = SearchLine(pList,keyNum);
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

