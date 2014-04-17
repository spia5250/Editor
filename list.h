

typedef struct ListNodet{
	struct ListNodet* next;
	int key;
	char* dataPtr;
}ListNode;

typedef struct{
	ListNode* head;
	ListNode* tail;
	int count;
}LIST;

LIST* createList(void);

ListNode* InsertList(LIST* plist, ListNode* prevlist, char* pData);

void KEY_view(LIST* pList);

int itemNum(LIST* plist);

ListNode* SearchNode(LIST* pList, int keyNum);

void DeleteListNode(LIST* pList, int keyNum);

void DeleteListAll(LIST* pList, char select);

char* headData(LIST* pList);

char* tailData(LIST* pList);


