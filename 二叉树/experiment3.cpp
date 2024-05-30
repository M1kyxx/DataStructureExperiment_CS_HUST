/* Binary Tree On BiLinked Structure */
/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/* status */
#define TRUE 1       //判定结果为正确
#define FALSE 0      //判定结果为错误
#define OK 1         //功能运行正常
#define ERROR 0      //功能出现错误无法运行
#define INFEASIBLE -1//操作对象不存在
#define OVERFLOW -2  //内存溢出

/* 数据元素类型 */
typedef int status;  //状态
typedef int KeyType; //关键字类型

/* 二叉树结点类型 */
typedef struct{
        KeyType key;     //关键字
        char others[20]; //内容
}TElemType; 

/* 二叉链表结点 */
typedef struct BiTNode{
        TElemType  data;                //数据域
        struct BiTNode *lchild,*rchild; //指针域(左孩子与右孩子)
}BiTNode, *BiTree;

/* 循环队列元素类型 */
typedef BiTNode* ElemType;

/* 循环队列容量 */
#define MAXLENGTH 100

/* 循环队列结构 */
typedef struct QUEUE{
    ElemType elem[MAXLENGTH];   //循环队列元素
    int front, length;          //循环队列定位用变量
}QUEUE;

/* 二叉树的管理表 */
typedef struct{
    struct{ 
        char name[30];  //二叉树名称
     	BiTree T;
    }elem[10];
    int length;         //管理表长度(二叉树棵数)
    int listsize;       //管理表容量
}LISTS;


static int flag_create = 0, k = 0;      //flag_create, k用于创建函数的标记
static BiTNode *p = NULL, *pt = NULL;   //p与pt用于查找兄弟和结点赋值时临时储存结点
static int flag1 = 0, flag3 = 0;        //flag1与flag3用于删除结点和结点赋值时进行标记

/* 零件函数 */
status Compare(KeyType e, TElemType elem);  //比较函数
void visit(BiTree elem);                    //访问函数
int max(int x, int y);                      //求较大值函数

/* 零件函数指针 */
status (*CompareArr)(KeyType e, TElemType elem) = Compare;
void (*visitArr)(BiTree elem) = visit;

/* 队列操作函数 */
void iniQueue(QUEUE &Q);
status enQueue(QUEUE &Q, ElemType e);
status deQueue(QUEUE &Q, ElemType &e);

/* 单树基础操作函数 */
status CreateBiTree(BiTree &T, TElemType definition[]);
status ClearBiTree(BiTree &T);
status DestroyBiTree(BiTree &T);
status ClearBiTree(BiTree &T);
status BiTreeEmpty(BiTree T);
int BiTreeDepth(BiTree T);
BiTNode* LocateNode(BiTree T, KeyType e);
status Assign(BiTree &T, KeyType e, TElemType value);
BiTNode* GetSibling(BiTree T, KeyType e);
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);
status DeleteNode(BiTree &T, KeyType e);
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));
status InOrderTraverse(BiTree T, void (*visit)(BiTree));
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

/*选做操作函数*/
int MaxPathSum(BiTree T);
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
status InvertTree(BiTree &T);

/*文件读写函数*/
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);

/*多树操作函数*/
status AddTree(LISTS &Lists, char ListName[]);
status RemoveTree(LISTS &Lists, char ListName[]);
int LocateTree(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
BiTree* ChooseTree(BiTree *L, LISTS &Lists, int i);










/*---------------------main函数-----------------------*/
int main(void)
{
    //定义单树并初始化
    BiTree T1 = NULL;
	BiTree *T = &T1;

    //定义管理表并初始化
    LISTS Lists;
    Lists.length = 0, Lists.listsize = 10;

	int op = 1, flag = 0, j = 0;     //op记录功能选择情况，flag记录功能运行情况
    char FileName[30], ListName[30]; //储存文件名与表名
    BiTNode *BTN = NULL;             //储存临时二叉结点
    TElemType definition[100];       //储存前序遍历序列
    memset(definition, 0, 100 * sizeof(TElemType));
	while(op)
	{
		system("cls");
		printf("\n\n");
		printf("       Menu for Binary Tree On BiLinked Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. 创建         13. 后序遍历\n");
		printf("    	  2. 销毁         14. 层序遍历\n");
		printf("    	  3. 清空         15. 求最大路径和\n");
		printf("    	  4. 判空         16. 求最近公共祖先\n");
		printf("    	  5. 求深         17. 翻转二叉树\n");
		printf("    	  6. 查找结点     18. 写入文件\n");
        printf("    	  7. 结点赋值     19. 读取文件\n");
        printf("    	  8. 获取兄弟     20. 增加二叉树\n");
        printf("    	  9. 插入结点     21. 删除二叉树\n");
        printf("    	 10. 删除结点     22. 查找二叉树\n");
        printf("    	 11. 前序遍历     23. 遍历总表\n");
        printf("    	 12. 中序遍历     24. 选择单树进行操作\n");
		printf("    	  0. 退出\n");
		printf("------------------------------------------------------\n");
        printf("    请确保多按几次回车键至窗口刷新后再选择操作\n");
		printf("    请选择你的操作[0~24]:");
		scanf("%d", &op);
		switch(op)
		{
			case 1://创建
                if(*T != NULL)
                    printf("二叉树已存在！无法再创建！\n");
                else
                {
                    flag_create = 0, k = 0;//重置static变量
                    printf("请输入前序遍历序列：");
                    do
                    {
                        scanf("%d %s", &definition[j].key, definition[j].others);
                    } while (definition[j++].key != -1);
                    flag = CreateBiTree(*T, definition);
                    if(flag == OK)
                        printf("二叉树创建成功！\n这是一个与独立于多树的单树，你可以对它进行1~19操作！\n");
                    else if(flag == ERROR)
                        printf("关键词不唯一！二叉树创建失败！\n");
                }
                getchar();getchar();
				break;
			case 2://销毁
                flag = DestroyBiTree(*T);
                if(flag == OK)
                    printf("成功销毁二叉树并释放数据元素的空间！\n");
                else
                    printf("不能对不存在的二叉树进行销毁操作！\n");
                getchar();getchar();
				break;
			case 3://清空
                flag = ClearBiTree(*T);
                if(flag == OK)
                    printf("成功清空二叉树！\n");
                else
                    printf("不能对不存在的二叉树进行清空操作！\n");
                getchar();getchar();
				break;
			case 4://判空
                flag = BiTreeEmpty(*T);
                if(flag == TRUE)
                    printf("二叉树为空！\n");
                else if(flag == FALSE)
                    printf("二叉树不为空！\n");
                else
                    printf("不能对不存在的二叉树进行判空操作！\n");
                getchar();getchar();
				break;
			case 5://求深
                // if(*T == NULL)
                //     printf("不能对不存在的二叉树进行求深操作！\n");
                // else
                {
                    flag = BiTreeDepth(*T);
                    printf("二叉树的深度为 %d！\n", flag);
                }
                getchar();getchar();
				break;
			case 6://查找结点
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行查找结点操作！\n");
                else
                {
                    int e = 0;//存储关键字
                    BTN = NULL;//存储所求结点
                    printf("请输入想要查找的结点的关键字：");
                    scanf("%d", &e);
                    BTN = LocateNode(*T, e);
                    if(BTN == NULL)
                        printf("查找失败！不存在关键字为 %d 的结点！\n", e);
                    else
                        printf("查找成功！该结点关键字为 %d，内容为 %s！\n", BTN->data.key, BTN->data.others);
                }
                getchar();getchar();
				break;
			case 7://结点赋值
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行结点赋值操作！\n");
                else
                {
                    pt = NULL, flag3 = 0;//重置static变量
                    int e = 0;//存储关键字
                    TElemType value[5];//存储新关键字与内容
                    memset(value, 0, 5 * sizeof(TElemType));//初始化
                    printf("请输入想要赋值的结点的关键字：");
                    scanf("%d", &e);
                    printf("请输入将赋的关键字与内容：");
                    scanf("%d %s", &value->key, value->others);
                    flag = Assign(*T, e, *value);
                    if(flag == OK)
                        printf("赋值成功！\n");
                    else
                        printf("赋值失败！关键词已存在！\n");
                }
                getchar();getchar();
				break;
			case 8://获取兄弟
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行获取兄弟操作！\n");
                else
                {
                    p = NULL;//重置static变量
                    int e = 0;//存储关键字
                    BTN = NULL;//存储所求结点
                    printf("请输入想要获取其兄弟结点的结点的关键字：");
                    scanf("%d", &e);
                    BTN = GetSibling(*T, e);
                    if(BTN == NULL)
                        printf("获取失败！不存在关键字为 %d 的结点或该结点没有兄弟！\n", e);
                    else
                        printf("获取成功！该结点的兄弟结点的关键字为 %d，内容为 %s！\n", BTN->data.key, BTN->data.others);
                }
                getchar();getchar();
				break;
			case 9://插入结点
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行插入结点操作！\n");
                else
                {
                    int e = 0, LR = 0;//存储关键字与插入方式
                    printf("请输入想要插入的结点的父结点的关键字：");
                    scanf("%d", &e);
                    printf("LR = 0 作为左孩子\nLR = 1 作为右孩子\nLR = -1 作为根结点\n");
                    printf("请输入插入方式：");
                    scanf("%d", &LR);
                    if(LR == -1 || LR == 0 || LR == 1)
                    {
                        TElemType c[5];//存储新关键字与内容
                        memset(c, 0, 5 * sizeof(TElemType));//初始化
                        printf("请输入将插入的关键字与内容：");
                        scanf("%d %s", &c[0].key, c[0].others);
                        flag = InsertNode(*T, e, LR, c[0]);
                        if(flag == OK)
                            printf("插入成功！\n");
                        else
                            printf("插入失败！关键词已存在！\n");
                    }
                    else
                        printf("插入失败！插入方式输入有误！\n");
                }
                getchar();getchar();
				break;
			case 10://删除结点
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行插入结点操作！\n");
                else
                {
                    flag1 = 0;//重置static变量
                    int e = 0;//存储关键字
                    printf("请输入想删除的结点的关键字：");
                    scanf("%d", &e);
                    flag = DeleteNode(*T, e);
                    if(flag == OK)
                        printf("删除成功！\n");
                    else
                        printf("删除失败！\n");
                }
                getchar();getchar();
				break;
			case 11://前序遍历
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行前序遍历操作！\n");
                else
                {
                    printf("\n-------------- all elements -------------------\n");
                    PreOrderTraverse(*T, visit);
                    printf("\n------------------ end ------------------------\n");
                }
				getchar();getchar();
				break;
			case 12://中序遍历
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行中序遍历操作！\n");
                else
                {
                    printf("\n-------------- all elements -------------------\n");
                    InOrderTraverse(*T, visit);
                    printf("\n------------------ end ------------------------\n");
                }
				getchar();getchar();
                break;
            case 13://后序遍历
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行后序遍历操作！\n");
                else
                {
                    printf("\n-------------- all elements -------------------\n");
                    PostOrderTraverse(*T, visit);
                    printf("\n------------------ end ------------------------\n");
                }
                getchar();getchar();
                break;
            case 14://层序遍历
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行层序遍历操作！\n");
                else
                {
                    printf("\n-------------- all elements -------------------\n");
                    LevelOrderTraverse(*T, visit);
                    printf("\n------------------ end ------------------------\n");
                }
                getchar();getchar();
                break;
            case 15://求最大路径和
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行该操作！\n");
                else
                {
                    flag = MaxPathSum(*T);
                    printf("该二叉树最大路径和为 %d！", flag);
                }
                getchar();getchar();
                break;
            case 16://求最近公共祖先
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行该操作！\n");
                else
                {
                    int e1 = 0, e2 = 0;//存储关键字
                    BTN = NULL;//存储所求结点
                    printf("请输入二叉树中两个结点的关键字：\n");
                    scanf("%d %d", &e1, &e2);
                    BTN = LowestCommonAncestor(*T, e1, e2);
                    if(BTN == NULL)
                        printf("操作失败！关键字输入有误！\n");
                    else
                        printf("关键字为 %d 和 %d 的两个结点的最近公共祖先为 %d %s！\n", e1, e2, BTN->data.key, BTN->data.others);
                }
				getchar();getchar();
				break;
            case 17://翻转二叉树
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行该操作！\n");
                else
                    if(InvertTree(*T) == OK)
                        printf("二叉树翻转成功！");
				getchar();getchar();
				break;
            case 18://写入文件
                if(*T == NULL)
                    printf("不能对不存在的二叉树进行该操作！\n");
                else
                {
                    printf("请输入文件名称：");
                    scanf("%s", FileName);
                    flag = SaveBiTree(*T, FileName);
                    if (flag == ERROR)
                        printf("文件打开失败！\n");
                    else if (flag == OK)
                        printf("二叉树的内容已经复制到名称为 %s 的文件中！\n", FileName);
                }
				getchar();getchar();
				break;
            case 19://读取文件
                    printf("请输入文件名称：");
                    scanf("%s", FileName);
                    flag = LoadBiTree(*T, FileName);
                    if (flag == ERROR)
                        printf("文件打开失败！\n");
                    else if (flag == OK)
                        printf("名称为 %s 的文件中的内容已复制到二叉树中！\n", FileName);
                    else if (flag == INFEASIBLE)
                        printf("不能对已存在的二叉树进行进行读文件操作！请先销毁二叉树！\n");
                    else if (flag == OVERFLOW)
                        printf("溢出！\n");
                getchar();getchar();
				break;
            case 20://增加二叉树
                flag_create = 0, k = 0;
                printf("请输入新增二叉树的名称：");
                scanf("%s", ListName);
                flag = AddTree(Lists, ListName);
                if (flag == OK)
                    printf("成功新增名称为 %s 的二叉树！\n", ListName);
                else
                    printf("新增失败！\n");
                getchar();getchar();
				break;
            case 21://删除二叉树
                if(Lists.length)
                {
                    printf("\n---------------- all trees --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("二叉树的集合为空！无法进行此操作！\n");
                    getchar();getchar();
                    break;
                }
				printf("请输入想要删除的二叉树的名称：");
                scanf("%s", ListName);
                flag = RemoveTree(Lists, ListName);
                if (flag == OK)
                    printf("成功删除名称为 %s 的二叉树！\n", ListName);
                else if (flag == ERROR)
                    printf("删除失败！\n");
                getchar();getchar();
                break;
            case 22://查找二叉树
            {
                if(!Lists.length)
                {
                    printf("二叉树的集合为空！无法进行此操作！\n");
                    getchar();getchar();
                    break;
                }
                int loc = 0;
				printf("请输入想要查找的二叉树的名称：");
                scanf("%s", ListName);
                loc = LocateTree(Lists, ListName);
                if (loc == 0)
                    printf("不存在名称为 %s 的二叉树！\n", ListName);
                else
                    printf("名称为 %s 的二叉树的序号为 %d ！\n", ListName, loc);
                getchar();getchar();
                break;
            }
            case 23://遍历总表
                flag = ListsTraverse(Lists);
                if (flag == ERROR)
                    printf("二叉树的集合为空！\n");
                getchar();getchar();
                break;
            case 24://选择单树进行操作
            {
                if(Lists.length)
                {
                    printf("\n---------------- all lists --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("二叉树的集合为空！无法进行此操作！\n");
                    getchar();getchar();
                    break;
                }
                int e = 0;
                printf("请输入想要进行操作的二叉树的序号（从1开始）：");
                scanf("%d", &e);
                getchar();
                T = ChooseTree(T, Lists, e);
                if (T == NULL)
                    printf("输入的序号不合法！单表已置空！\n");
                else
                    printf("下面可对二叉树集合中序号为 %d 的二叉树进行操作！\n", e);
                getchar();getchar();
                break;
            }
			case 0:
				break;
		}
	}
	printf("欢迎下次再使用本系统！\n");
    return 0;
}
/*---------------------main函数-----------------------*/












// 排序函数
status Compare(KeyType e, TElemType elem)
{
    if(elem.key == e)
        return OK;
    return ERROR;
}

// 访问函数
void visit(BiTree elem)
{
    printf("| %d %s |", elem->data.key, elem->data.others);
}

// 求最大值函数
int max(int x, int y)
{
    return (x >= y) ? x : y;
}

// 初始化队列Q
void iniQueue(QUEUE &Q)
{
    Q.front = 0;
    Q.length = 0;   //队列长度为0
}

// 元素入队
status enQueue(QUEUE &Q, ElemType e)
{
    if(Q.length >= MAXLENGTH)   //队列溢出
        return ERROR;
    Q.elem[(Q.front + Q.length++) % MAXLENGTH] = e;
    return OK;
}

// 元素出队
// 将Q队首元素出队，赋值给e。成功出队返回1，否则返回0
status deQueue(QUEUE &Q, ElemType &e)
{
    if(Q.length == 0)   //队列为空
        return ERROR;
    e = Q.elem[Q.front];
    Q.front = (Q.front + 1) % MAXLENGTH;
    Q.length--;
    return OK;
}

// 功能1 创建
// 根据带空枝的二叉树先根遍历序列definition构造一棵二叉树，将根节点指针赋值给T并返回OK，如果有相同的关键字，返回ERROR。
status CreateBiTree(BiTree &T,TElemType definition[])
{
    if (flag_create == 0)
    {
        int i = 0, j = 0;   //关键字检查循环用变量
        for (i = 0; definition[i].key != -1; i++)
        {
            if(definition[i].key == 0)
                continue;
            for (j = i + 1;definition[j].key != -1;j++)
                if (definition[j].key != 0)
                    if (definition[i].key == definition[j].key)
                        return ERROR;
        }
        flag_create = 1;    //标记已经进行关键字检查，后续递归无需再次检查
    }
    if (flag_create == 1)
    {
        if (definition[k].key == 0) //关键字为0时赋NULL
        {
            T = NULL;
            k++;    //definition向前推进至下一结点
        }
        else    //关键字不为0时生成结点
        {
            if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
                return OVERFLOW;
            T->data = definition[k];
            k++;    //definition向前推进至下一结点
            CreateBiTree(T->lchild, definition);//递归生成左子树
            CreateBiTree(T->rchild, definition);//递归生成右子树
        }
        return OK;
    }
}

// 功能2 销毁
// 初始条件是二叉树T已存在；操作结果是销毁二叉树T。
status DestroyBiTree(BiTree &T)
{
   if (T)
   {
        DestroyBiTree(T->lchild);//递归销毁左子树
        DestroyBiTree(T->rchild);//递归销毁右子树
        free(T);    //销毁分配的空间
        T = NULL;   //必须置空，free后指针仍指向原处
        return OK;
   }
   return ERROR;
}

// 功能3 清空
// 初始条件是二叉树T存在；操作结果是将二叉树T清空。
status ClearBiTree(BiTree &T)
{
    if(T)
    {
        ClearBiTree(T->lchild);//递归清空左子树
        ClearBiTree(T->rchild);//递归清空右子树
        memset(T, 0, sizeof(BiTNode));//清空不销毁
        return OK;
    }
    return ERROR;
}

// 功能4 判空
// 初始条件是二叉树T存在；操作结果是若T为空二叉树则返回TRUE，否则返回FALSE。
status BiTreeEmpty(BiTree T)
{
    if(T == NULL)   //二叉树不存在
        return INFEASIBLE;
    else if(T->data.key == 0)
        return TRUE;
    return FALSE;
}

// 功能5 求深
// 初始条件是二叉树T存在；操作结果是返回T的深度。
int BiTreeDepth(BiTree T)
{
    int depthL = 0, depthR = 0;
    if(T == NULL)
        return 0;
    depthL = BiTreeDepth(T->lchild);//递归求左子树深度
    depthR = BiTreeDepth(T->rchild);//递归求右子树深度
    if(depthL > depthR)
        return (depthL + 1);
    else
        return (depthR + 1);
}

// 功能6 查找结点
// 初始条件是二叉树T已存在，e是和T中结点关键字类型相同的给定值。
// 操作结果是返回查找到的结点指针，如无关键字为e的结点，返回NULL。
BiTNode* LocateNode(BiTree T,KeyType e)
{
    BiTNode *p = NULL, *q = NULL;//保存左子树与右子树中查找到的结点
    if(T == NULL)
        return NULL;
    if(T->data.key == e)
        return T;
    p = LocateNode(T->lchild, e);//递归查找左子树
    q = LocateNode(T->rchild, e);//递归查找右子树
    if(p != NULL)//所查结点在左子树中
        return p;
    if(q != NULL)//所查结点在右子树中
        return q;
    return NULL;
}

// 功能7 结点赋值
// 初始条件是二叉树T已存在，e是和T中结点关键字类型相同的给定值。
// 操作结果是关键字为e的结点赋值为value。
status Assign(BiTree &T,KeyType e,TElemType value)
{
    if(T == NULL)
        return OK;
    if(T->data.key == value.key && T->data.key != e)//关键词冲突
    {
        pt = NULL;
        flag3 = 1;
        return ERROR;
    }
    if(T->data.key == e && !flag3)
    {
        pt = T;
        return OK;
    }
    Assign(T->lchild, e, value);//递归查找左子树
    Assign(T->rchild, e, value);//递归查找右子树
    if(pt != NULL)
    {
        pt->data.key = value.key;
        strcpy(pt->data.others, value.others);
        return OK;
    }
    else
        return ERROR;
}

// 功能8 获取兄弟
// 初始条件是二叉树T存在，e是和T中结点关键字类型相同的给定值。
// 操作结果是返回关键字为e的结点的（左或右）兄弟结点指针。若关键字为e的结点无兄弟，则返回NULL。
BiTNode* GetSibling(BiTree T,KeyType e)
{
    
    if(T == NULL)
        return NULL;
    if(T->data.key == e)
        return T;
    if(GetSibling(T->lchild, e) != NULL && !p)
        p = T->rchild;
    if(GetSibling(T->rchild, e) != NULL && !p)
        p = T->lchild;
    return p;
}

// 功能9 插入结点
// 初始条件是二叉树T存在，e是和T中结点关键字类型相同的给定值，LR为0或1，c是待插入结点。
// 操作结果是根据LR为0或者1，插入结点c到T中，作为关键字为e的结点的左或右孩子结点，结点e的原有左子树或右子树则为结点c的右子树；
// LR为-1时，作为根结点插入，原根结点作为c的右子树。
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
{
    static BiTNode *p = NULL;
    if(LR == -1)//作为根结点插入
    {
        p = (BiTNode *)malloc(sizeof(BiTNode));
        p->data = c;
        p->lchild = NULL;
        p->rchild = T;
        T = p;
        return OK;
    }
    if(T == NULL)
        return OK;
    if(T->data.key == c.key)
        return ERROR;
    if(T->data.key == e)
    {
        p = (BiTNode *)malloc(sizeof(BiTNode));
        p->data = c;
        if(!LR)//作为左子树插入
        {
            p->rchild = T->lchild;
            T->lchild = p;
            p->lchild = NULL;
        }
        else//作为右子树插入
        {
            p->rchild = T->rchild;
            T->rchild = p;
            p->lchild = NULL;
        }
        return OK;
    }
    InsertNode(T->lchild, e, LR, c);
    InsertNode(T->rchild, e, LR, c);
    if(p != NULL)  
        return OK;
    else
        return ERROR;
}

// 功能10 删除结点
// 初始条件是二叉树T存在，e是和T中结点关键字类型相同的给定值。
// 操作结果是删除T中关键字为e的结点；同时，如果关键字为e的结点度为0，删除即可。
// 如关键字为e的结点度为1，用关键字为e的结点孩子代替被删除的e位置。
// 如关键字为e的结点度为2，用e的左孩子代替被删除的e位置，e的右子树作为e的左子树中最右结点的右子树。
status DeleteNode(BiTree &T,KeyType e)
{
    if(T == NULL)
        return OK;
    if(T->data.key == e)
    {
        flag1 = 1;
        if(T->lchild == NULL && T->rchild == NULL)//度为0，直接删除
        {
            free(T);
            T = NULL;
            return OK;
        }
        else if(T->lchild != NULL && T->rchild == NULL)//度为1，用孩子代替e
        {
            BiTNode *p = T->lchild;
            free(T);
            T = p;
            return OK;
        }
        else if(T->lchild == NULL && T->rchild != NULL)//度为1，用孩子代替e
        {
            BiTNode *p = T->rchild;
            free(T);
            T = p;
            return OK;
        }
        else//度为2，用左孩子代替e，右子树作为左子树中最右结点的右子树
        {
            BiTNode *p = T->lchild;
            BiTNode *q = T->rchild;
            free(T);
            T = p;
            BiTNode *tmp = T;
            for(; tmp->rchild != NULL; tmp = tmp->rchild)
                ;
            tmp->rchild = q;
            return OK;
        }
    }
    DeleteNode(T->lchild, e);
    DeleteNode(T->rchild, e);
    if(!flag1)
        return ERROR;
    else
        return OK;
}

// 功能11 前序遍历
// 初始条件是二叉树T存在，Visit是一个函数指针的形参（可使用该函数对结点操作）。
// 操作结果：先序遍历，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T)
    {
        visit(T);//访问当前结点
        PreOrderTraverse(T->lchild, visit);//递归遍历左子树
        PreOrderTraverse(T->rchild, visit);//递归遍历右子树
    }
        return OK;
}

// 功能12 中序遍历
// 初始条件是二叉树T存在，Visit是一个函数指针的形参（可使用该函数对结点操作）。
// 操作结果是中序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T)
    {
        InOrderTraverse(T->lchild, visit);//递归遍历左子树
        visit(T);//访问当前结点
        InOrderTraverse(T->rchild, visit);//递归遍历右子树
        return OK;
    }
    else
        return OK;
}

// 功能13 后序遍历
// 初始条件是二叉树T存在，Visit是一个函数指针的形参（可使用该函数对结点操作）。
// 操作结果是后序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T)
    {
        PostOrderTraverse(T->lchild, visit);//递归遍历左子树
        PostOrderTraverse(T->rchild, visit);//递归遍历右子树
        visit(T);//访问当前结点
        return OK;
    }
    else
        return OK;
}

// 功能14 层序遍历
// 初始条件是二叉树T存在，Visit是对结点操作的应用函数。
// 操作结果是层序遍历t，对每个结点调用函数Visit一次且一次，一旦调用失败，则操作失败。
status LevelOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    BiTNode *p = NULL;
    QUEUE qu;
    iniQueue(qu);
    enQueue(qu, T);
    while(qu.length)
    {
        deQueue(qu, p);
        visit(p);
        if(p->lchild != NULL)
            enQueue(qu, p->lchild);//左孩子进队
        if(p->rchild != NULL)
            enQueue(qu, p->rchild);//右孩子进队
    }
    return OK;
}

// 附加功能15 求最大路径和
// 初始条件是二叉树T存在；操作结果是返回根节点到叶子结点的最大路径和。
int MaxPathSum(BiTree T)
{
    if(T == NULL)
        return 0;
    else
        return max(T->data.key + MaxPathSum(T->lchild), T->data.key + MaxPathSum(T->rchild));
}

// 附加功能16 求最近公共祖先
// 初始条件是二叉树T存在；操作结果是该二叉树中e1节点和e2节点的最近公共祖先。
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2)
{
    if(T == NULL)
        return NULL;
    if(T->data.key == e1 || T->data.key == e2)
        return T;
    BiTNode *left = LowestCommonAncestor(T->lchild, e1, e2);
    BiTNode *right = LowestCommonAncestor(T->rchild, e1, e2);
    if(left == NULL)
        return right;
    if(right == NULL)
        return left;
    return T;
}

// 附加功能17 翻转二叉树
// 初始条件是线性表L已存在；操作结果是将T翻转，使其所有节点的左右节点互换。
status InvertTree(BiTree &T)
{
    if(T == NULL)
        return OK;
    InvertTree(T->lchild);//递归翻转左子树
    InvertTree(T->rchild);//递归翻转右子树
    BiTree tmp = NULL;//交换左右结点时的临时存储结点
    tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    return OK;
}

// 附加功能18 写入文件
// 如果二叉树T存在，将二叉树T的的元素写到FileName文件中，返回OK。
status SaveBiTree(BiTree T, char FileName[])
{
    static FILE *fp1 = fopen(FileName, "w");
    if(T == NULL)
    {
        fprintf(fp1, "%d %s ", 0, "null");
        return OK;
    }
    else
    {
        fprintf(fp1, "%d %s ", T->data.key, T->data.others);
        SaveBiTree(T->lchild, FileName);
        SaveBiTree(T->rchild, FileName);
    }
    if(T->data.key == 1)
        fclose(fp1);
    return OK;
}

// 附加功能19 读取文件
// 如果二叉树T不存在，将FileName文件中的数据读入到二叉树T中，返回OK。
status LoadBiTree(BiTree &T,  char FileName[])
{
    static FILE *fp2 = fopen(FileName, "r");
    int t = 0;  //存储关键字
    char s[20]; //存储内容
    memset(s, 0, 20);
    if(feof(fp2))
        return OK;
    fscanf(fp2, "%d%s", &t, s);
    if(t == 0)
        T = NULL;
    else
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));//生成新树
        T->data.key = t;
        strcpy(T->data.others, s);
        LoadBiTree(T->lchild, FileName);//递归建立左子树
        LoadBiTree(T->rchild, FileName);//递归建立右子树
    }
    if(feof(fp2))
        fclose(fp2);
    return OK;
}

// 附加功能20 多二叉树管理：增加新二叉树
// 在Lists中增加一个名称为TreeName的二叉树。
status AddTree(LISTS &Lists,char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))
        {
            printf("集合中已存在名称为 %s 的二叉树！\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);
    TElemType defi[100];
    memset(defi, 0, 100 * sizeof(TElemType));
    int j = 0, flag3 = 0;
    printf("请输入前序遍历序列：");
    do
    {
        scanf("%d %s", &defi[j].key, defi[j].others);
    } while (defi[j++].key != -1);
    flag3 = CreateBiTree(Lists.elem[Lists.length].T, defi);
    if(flag3 == OK)
    {
        printf("名称为 %s 的二叉树创建成功！\n", Lists.elem[Lists.length].name);
        Lists.length++;
    }
    else if(flag3 == ERROR)
        printf("关键词不唯一！二叉树创建失败！\n");
    return OK;
}

// 附加功能21 多二叉树管理:删除二叉树
// 在Lists中删除一个名称为TreeName的二叉树。
status RemoveTree(LISTS &Lists,char ListName[])
{
    int i;
    for(i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //匹配表名
            break;
    if(i == Lists.length)
        return ERROR;
    else
    {
        DestroyBiTree(Lists.elem[i].T);
        memset(Lists.elem[i].name, 0, strlen(Lists.elem[i].name));
        Lists.length--;
        for(int j = i; j < Lists.length; j++)
            Lists.elem[j] = Lists.elem[j + 1];
        return OK;
    }
}

// 附加功能22 多二叉树管理:查找二叉树
// 在Lists中查找一个名称为TreeName的二叉树，成功返回逻辑序号，否则返回0
int LocateTree(LISTS Lists, char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //匹配表名
            return (i + 1);
    return ERROR;
}

// 附加功能23 多二叉树管理:遍历多二叉树
// 在Lists中删除一个名称为TreeName的二叉树。
status ListsTraverse(LISTS Lists)
{
    if (Lists.length == 0)
        return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("表名为 %s 的元素有：", Lists.elem[n].name);
        PreOrderTraverse(Lists.elem[n].T, visit);
        putchar('\n');
    }
    return OK;
}

// 附加功能24 多二叉树管理:选择一个二叉树，输入其序号，后续可对其进行操作
BiTree *ChooseTree(BiTree *T, LISTS &Lists, int i) 
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        T = &(Lists.elem[i - 1].T);  //传递地址以同时改动单树与多树中的此树    
        return T;
    }
}