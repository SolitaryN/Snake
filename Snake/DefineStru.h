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
{
	struct HuffmanNode *LChind, *RChild;
	int weight;
	char data; //叶子结点记录值
} HuffmanNode;

typedef struct MinNode
{
	LinkNode *Min1, *Min2;
} Min;

Min *getMinNode(LinkNode *head)
{
	LinkNode * temp = head;
	Min * retu = (Min *) malloc (sizeof(Min));
	while (temp->Next != NULL) //遍历单链表
	{
		temp = temp->Next;
		int min1 = 100000000, min2 = 100000000; //用来找权值最小的两个结点
		if (temp->weight < min1 || temp->weight < min2)
		{
			if (min1 > min2)
			{
				min1 = temp->weight;
				MinNode1 = temp;
			}
			else
			{
				min2 = temp->weight;
				MinNode2 = temp;
			}
		}
	}
}