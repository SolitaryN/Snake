#define TRUE 1
#define FALSE 0
typedef struct StackNode{
	struct StackNode * Next;                                                                                                                                                                                                                                                                                                              
	char data;
} StackNode;					//此处定义了链栈的节点 

typedef struct LinkNode{
	int weight;				//权值 
	char data;
	struct LinkNode * Next;
	int mark;				//标记是否这个点已经被遍历过
} LinkNode;					//此处定义了单链表的节点，用来保存出现的都有哪些字符，还有字符出现的次数 

typedef struct HuffmanNode{
	struct HuffmanNode * LChind, * RChild;
	int MarkWetherNull;
	int weight;
	char data;				//叶子结点记录值
} HuffmanNode;