#define TRUE 1
#define FALSE 0
typedef struct StackNode
{
	struct StackNode *Next;
	char data;
} StackNode; //此处定义了链栈的节点

typedef struct LinkNode
{
	int weight; //权值
	char data;
	struct LinkNode *Next, *Pre;
	struct LinkNode *LChild, *RChild;
} LinkNode; //此处定义了单链表的节点，用来保存出现的都有哪些字符，还有字符出现的次数

typedef struct HuffmanNode
{//这个定义的节点类型没有用，可以删除
	struct HuffmanNode *LChind, *RChild;
	int weight;
	char data; //叶子结点记录值
} HuffmanNode;

