//const int max_line = 25;
//const int max_col = 80;

typedef struct ListNodet{
	struct ListNodet* next;
	int key;
	char data[81];
}ListNode;//for line
	
typedef struct{
	ListNode* head;
	ListNode* tail;
	int line_count;
}LIST;//for all line

LIST* createList(void);

void save_list(LIST* plist, FILE* fp);

void key_modify(LIST* plist,ListNode* line, int line_num);

void print_Data(LIST* plist, int line, int col);

ListNode* SearchLine(LIST* pList, int keyNum);

int SearchData_NULL(LIST* plist, ListNode* startline, int start_col);

ListNode* InsertLine(LIST* plist, int prevline_num);

void InsertData(LIST* plist, int line_num, int col_num, char dat);

//void EnterLine(LIST* plist, int line_num, int col_num);

void KEY_view(LIST* pList);

int itemNum(LIST* plist);

void DeleteLineNode(LIST* pList, int keyNum);

void DeleteLine(LIST* pList, int keyNum);

void DeleteLine_N(LIST* pList, ListNode* DeleteNode);

void DeleteLineAll(LIST* plist, char mode);

void DeleteData(LIST* pList, int line, int col);

//char* headData(LIST* pList);

//char* tailData(LIST* pList);


