/* Linear Table On Linked Structure */
/*头文件*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

/*status*/
#define TRUE 1      //判定结果为正确
#define FALSE 0     //判定结果为错误
#define OK 1        //功能运行正常
#define ERROR 0     //功能出现错误无法运行
#define INFEASIBLE -1//操作对象不存在
#define OVERFLOW -2 //内存溢出

/*数据元素类型*/
typedef int status; 
typedef int ElemType;

/*初始表长与单位表长*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

/*单链表结点*/
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

/*线性表的管理表*/
typedef struct{
    struct{ 
        char name[30];
     	LinkList L;	
    }elem[10];
    int length;
    int listsize;
}LISTS;

/*零件函数*/
status Compare(ElemType e, ElemType elem);  //比较函数
void visit(ElemType elem);                  //访问函数

/*零件函数指针*/
status (*CompareArr)(ElemType e, ElemType elem) = Compare;
void (*visitArr)(ElemType elem) = visit;

/*单表基础操作函数*/
status InitList(LinkList &L);
status DestroyList(LinkList &L);
status ClearList(LinkList &L);
status ListEmpty(LinkList L);
int ListLength(LinkList L);
status GetElem(LinkList L,int i,ElemType &e);
int LocateElem(LinkList L, ElemType e, status (*CompareArr)(ElemType, ElemType)); 
status PriorElem(LinkList L, ElemType cur, ElemType &pre_e);
status NextElem(LinkList L, ElemType cur, ElemType &next_e);
status ListInsert(LinkList &L, int i, ElemType e);
status ListDelete(LinkList &L, int i, ElemType &e);
status ListTraverse(LinkList L, void (*visitArr)(ElemType));

/*选做操作函数*/
status reverseList(LinkList &L);
int RemoveNthFromEnd(LinkList &L, int n);
status sortList(LinkList &L);

/*文件读写函数*/
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList &L, char FileName[]);

/*多表操作函数*/
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
LinkList* ChooseList(LinkList *L, LISTS &Lists, int i);





/*---------------------main函数-----------------------*/
int main(void)
{
    //定义单表并初始化
    LinkList L1 = NULL;
	LinkList *L = &L1;

    //定义管理表并初始化
    LISTS Lists;
    Lists.length = 0, Lists.listsize = 0;

	int op = 1, len, flag, i, e, pre, next, num, k;
    char FileName[30], ListName[30];
	while(op)
	{
		system("cls");
		printf("\n\n");
		printf("       Menu for Linear Table On Linked Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. 创建         12. 遍历\n");
		printf("    	  2. 销毁         13. 翻转链表\n");
		printf("    	  3. 清空         14. 删除链表倒数第n个结点\n");
		printf("    	  4. 判空         15. 排序\n");
		printf("    	  5. 求长         16. 写入文件\n");
		printf("    	  6. 获取元素     17. 读取文件\n");
        printf("    	  7. 查找元素     18. 增加线性表\n");
        printf("    	  8. 获取前驱     19. 删除线性表\n");
        printf("    	  9. 获取后继     20. 查找线性表\n");
        printf("    	 10. 输入元素     21. 遍历总表\n");
        printf("    	 11. 删除元素     22. 选择单表进行操作\n");
		printf("    	  0. 退出\n");
		printf("------------------------------------------------------\n");
        printf("    请确保多按几次回车键至窗口刷新后再选择操作\n");
		printf("    请选择你的操作[0~22]:");
		scanf("%d", &op);
		switch(op)
		{
			case 1://创建
				if(InitList(*L) == OK)
					printf("线性表创建成功！\n这是一个与独立于多表的单表，你可以对它进行1~17操作！\n");
				else
					printf("线性表创建失败！\n");
                getchar();getchar();
				break;
			case 2://销毁
				if(DestroyList(*L) == OK)
                    printf("成功销毁线性表并释放数据元素的空间！\n");
                else
                    printf("不能对不存在的线性表进行销毁操作！\n");
                getchar();getchar();
				break;
			case 3://清空
				if(ClearList(*L) == OK)
                    printf("成功删除线性表中所有的元素！\n");
                else
                    printf("不能对不存在的线性表进行清空操作！\n");
                getchar();getchar();
				break;
			case 4://判空
				flag = ListEmpty(*L);
                if(flag == TRUE)
                    printf("线性表为空！\n");
                else if(flag == FALSE)
                    printf("线性表非空！\n");
                else
                    printf("不能对不存在的线性表判空！\n");
                getchar();getchar();
				break;
			case 5://求长
				len = ListLength(*L);
                if(len >= 0)
                    printf("线性表的长度为%d！\n", len);
                else
                    printf("不能对不存在的线性表求长！\n");
                getchar();getchar();
				break;
			case 6://获取元素
				printf("请输入想要从线性表中获取的元素序号：");
                scanf("%d", &i);
                getchar();
                flag = GetElem(*L, i, e);
                if(flag == OK)
                    printf("线性表中第%d个元素为%d！\n", i, e);
                else if(flag == ERROR)
                    printf("输入的序号不合法！\n");
                else
                    printf("不能对不存在的线性表进行此操作！\n");
                getchar();getchar();
				break;
			case 7://查找元素
				printf("请输入想要在线性表中查找的元素：");
                scanf("%d", &e);
                getchar();
                flag = LocateElem(*L, e, Compare);
                if (flag == 0)
                    printf("线性表中不存在%d这个元素。\n", e);
                else if (flag == INFEASIBLE)
                    printf("不能对不存在的线性表进行此操作！\n");
                else
                    printf("元素%d在线性表中的序号为%d\n", e, flag);
                getchar();getchar();
				break;
			case 8://查找前驱
				printf("请输入想要在线性表中查找其前驱的元素：");     
				scanf("%d", &e);
                getchar();
                flag = PriorElem(*L, e, pre);
                if(flag == OK)
                    printf("元素%d在线性表中的前驱为%d！\n", e, pre);
                else if(flag == ERROR)
                    printf("元素%d在线性表中没有前驱！\n", e);
                else
                    printf("不能对不存在的线性表进行此操作！\n");
                getchar();getchar();
				break;
			case 9://查找后继
				printf("请输入想要在线性表中查找其后继的元素：");     
				scanf("%d", &e);
                getchar();
                flag = NextElem(*L, e, next);
                if(flag == OK)
                    printf("元素%d在线性表中的后继为%d！\n", e, next);
                else if(flag == ERROR)
                    printf("元素%d在线性表中没有后继！\n", e);
                else
                    printf("不能对不存在的线性表进行此操作！\n");
                getchar();getchar();
				break;
			case 10://输入元素
                printf("1.插入单个元素\n2.在表尾输入多个元素\n请选择将要进行的操作：");
                scanf("%d", &flag);
                getchar();
                switch (flag)
                {
                    case 1:
                        printf("请输入该元素：");
                        scanf("%d", &e);
                        getchar();
                        printf("请输入想要它作为第几个元素：");
                        scanf("%d", &i);
                        getchar();
                        flag = ListInsert(*L, i, e);
                        if(flag == OK)
                            printf("元素已插入线性表中！\n");
                        else if(flag == ERROR)
                            printf("位置插入非法！\n");
                        else
                            printf("不能对不存在的线性表进行插入！\n");
                        break;
                    case 2:
                        printf("请输入元素个数：");
                        scanf("%d", &num);
                        getchar();
                        printf("请输入这些元素，以空格间隔：");
                        LNode *p = *L;
                        for(; p->next != NULL; p = p->next)
                            ;
                        for(int i = 0; i < num; i++)
                        {
                            p->next = (LNode *)malloc(sizeof(LNode));
                            p = p->next;
                            scanf("%d", &p->data);
                            p->next = NULL;
                        }
                        getchar();
                        printf("元素已输入于线性表中！\n");
                        break;
                }
                getchar();getchar();
				break;
			case 11://删除元素
				printf("请输入想要删除的元素序号：");
                scanf("%d", &i);
                getchar();
                flag = ListDelete(*L, i, e);
                if(flag == OK)
                    printf("序号为 %d 的元素 %d 已经从线性表中删除！\n", i, e);
                else if(flag == ERROR)
                    printf("位置输入非法！\n");
                else
                    printf("不能对不存在的线性表进行删除！\n");     
				getchar();getchar();
				break;
			case 12://遍历
				if(ListTraverse(*L, visit) == INFEASIBLE)
                    printf("不能对不存在的线性表进行遍历！\n");
				getchar();getchar();
                break;
            case 13://翻转链表
                flag = reverseList(*L);
                if(flag == OK)
                    printf("当前链表已翻转！\n");
                else
                    printf("不能对不存在的线性表进行翻转！\n");
                getchar();getchar();
                break;
            case 14://删除倒数第n个结点
                int n;
                printf("本功能实现删除链表倒数第n个结点，请输入n：");
                scanf("%d", &n);
                flag = RemoveNthFromEnd(*L, n);
                if(flag == INFEASIBLE)
                    printf("不能对不存在的线性表进行删除操作！\n");
                else if(flag == ERROR)
                    printf("不能对空线性表进行删除操作或n不合法！\n");
                else
                    printf("链表倒数第 %d 个元素 %d 已被删除！\n", n, flag);
                getchar();getchar();
                break;
            case 15://排序
                flag = sortList(*L);
                if(flag == INFEASIBLE)
                    printf("不能对不存在的线性表进行排序！\n");
                else
                    printf("线性表已从小到大排序！\n");
                getchar();getchar();
                break;
            case 16://写入文件
				printf("请输入文件名称：");
                scanf("%s", FileName);
                flag = SaveList(*L, FileName);
                if (flag == ERROR)
                    printf("文件打开失败！\n");
                else if (flag == OK)
                    printf("线性表的内容已经复制到名称为 %s 的文件中！\n", FileName);
                else if (flag == INFEASIBLE)
                    printf("不能对不存在的线性表进行进行写文件操作！\n");
				getchar();getchar();
				break;
            case 17://读取文件
				printf("请输入文件名称：");
                scanf("%s", FileName);
                flag = LoadList(*L, FileName);
                if (flag == ERROR)
                    printf("文件打开失败！\n");
                else if (flag == OK)
                    printf("名称为 %s 的文件中的内容已复制到线性表中！\n", FileName);
                else if (flag == INFEASIBLE)
                    printf("不能对已存在的线性表进行进行读文件操作！请先销毁线性表！\n");
                else if (flag == OVERFLOW)
                    printf("溢出！\n");
				getchar();getchar();
				break;
            case 18://新增线性表
				printf("请输入新增线性表的名称：");
                scanf("%s", ListName);
                flag = AddList(Lists, ListName);
                if (flag == OK)
                    printf("成功新增名称为 %s 的线性表！\n", ListName);
                else
                    printf("新增失败！\n");
				getchar();getchar();
				break;
            case 19://删除线性表
				if(Lists.length)
                {
                    printf("\n---------------- all lists --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("线性表的集合为空！无法进行此操作！\n");
                    getchar();getchar();
                    break;
                }
				printf("请输入想要删除的线性表的名称：");
                scanf("%s", ListName);
                flag = RemoveList(Lists, ListName);
                if (flag == OK)
                    printf("成功删除名称为 %s 的线性表！\n", ListName);
                else if (flag == ERROR)
                    printf("删除失败！\n");
                getchar();getchar();
				break;
            case 20://查找线性表
				if(!Lists.length)
                {
                    printf("线性表的集合为空！无法进行此操作！\n");
                    getchar();getchar();
                    break;
                }
				printf("请输入想要查找的线性表的名称：");
                scanf("%s", ListName);
                i = LocateList(Lists, ListName);
                if (i == 0)
                    printf("不存在名称为 %s 的线性表！\n", ListName);
                else printf("名称为 %s 的线性表的序号为 %d ！\n", ListName, i);
                getchar();getchar();
				break;
            case 21://遍历总表
                flag = ListsTraverse(Lists);
                if (flag == ERROR)
                    printf("线性表的集合为空！\n");
                getchar();getchar();
                break;
            case 22://选择多表中的表进行单独操作
                if(Lists.length)
                {
                    printf("\n---------------- all lists --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("线性表的集合为空！无法进行此操作！\n");
                    getchar();getchar();
                    break;
                }
                printf("请输入想要进行操作的线性表的序号（从1开始）：");
                scanf("%d", &i);
                getchar();
                L = ChooseList(L, Lists, i);
                if (L == NULL)
                    printf("输入的序号不合法！单表已置空！\n");
                else
                    printf("下面可对线性表集合中序号为 %d 的线性表进行操作！\n", i);
                getchar();getchar();
                break;
			case 0:
				break;
		}
	}
	printf("欢迎下次再使用本系统！\n");
    return 0;
}
/*---------------------main函数-----------------------*/





// 排序函数
status Compare(ElemType e, ElemType elem)
{
    if(elem == e)
        return OK;
    return ERROR;
}

// 访问函数
void visit(ElemType elem)
{
    printf("%d ", elem);
}

// 功能1 创建线性表
// 若线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
status InitList(LinkList &L)
{
    if(L != NULL)
        return INFEASIBLE;
    else
    {
        L = (LNode *)malloc(sizeof(LNode));
        L->next = NULL;
        return OK;
    }
}

// 功能2 销毁线性表
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
status DestroyList(LinkList &L)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        LNode *p = NULL;
        while(L)
        {
            p = L;
            L = L->next;
            free(p);
        }
        L = NULL;
        return OK;
    }
}

// 功能3 清空线性表
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
status ClearList(LinkList &L)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        LNode *p = L->next, *q = NULL;
        
        while(p)
        {
            q = p;
            p = p->next;
            free(q);
        }
        L->next = NULL;
        return OK;
    }
}

// 功能4 线性表判空
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
status ListEmpty(LinkList L)
{
    if(L == NULL)
        return INFEASIBLE;
    else if(L->next == NULL)
        return TRUE;
    return FALSE;
}

// 功能5 线性表求长
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
int ListLength(LinkList L)
{
    int num = 0;
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        for(LNode *p = L->next; p != NULL; p = p->next)
            num++;
        return num;
    }
}

// 功能6 获取元素
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status GetElem(LinkList L,int i,ElemType &e)
{
    int j = 1;
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        if(L->next == NULL)
            return ERROR;
        if(i < 1)
            return ERROR;
        for(LNode *p = L->next; j <= i; p = p->next, j++)
        {
            if(p == NULL)
                return ERROR;
            if(j == i)
            {
                e = p->data;
                return OK;
            }
        }
    }
}

// 功能7 查找元素
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回ERROR；当线性表L不存在时，返回INFEASIBLE。
int LocateElem(LinkList L,ElemType e, status (*CompareArr)(ElemType, ElemType))
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        LNode *p = L->next;
        for(int i = 1; p != NULL; p = p->next, i++)
            if(p->data == e)
                return i;
        return ERROR;
    }
}

// 功能8 获取前驱元素
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status PriorElem(LinkList L,ElemType e,ElemType &pre)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        LNode *p = L->next, *q = L;
        for(; p != NULL; p = p->next, q = q->next)
            if(p->data == e && q != L)
            {
                pre = q->data;
                return OK;
            }
        return ERROR;
    }
}

// 功能9 获取后继元素
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status NextElem(LinkList L,ElemType e,ElemType &next)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        if(L->next == NULL)
            return ERROR;
        LNode *p = L->next, *q = L->next->next;
        for(; q != NULL; p = p->next, q = q->next)
            if(p->data == e && q != NULL)
            {
                next = q->data;
                return OK;
            }
        return ERROR;
    }
}

// 功能10 输入元素
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListInsert(LinkList &L,int i,ElemType e)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        int j = 1;
        for(LNode *p = L->next; p != NULL; p = p->next)
        {
            j++;
            if(j == i)
            {
                LNode *q = (LNode *)malloc(sizeof(LNode));
                q->data = e;
                q->next = p->next;
                p->next = q;
                return OK;
            }
        }
        return ERROR;
    }
}

// 功能11 删除元素
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListDelete(LinkList &L,int i,ElemType &e)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        int j = 1;
        for(LNode *p = L->next, *pre = L; p != NULL; p = p->next, pre = pre->next, j++)
            if(j == i)
            {
                e = p->data;
                if(p->next != NULL)
                    pre->next = p->next;
                else
                    pre->next = NULL;
                free(p);
                return OK;
            }
        return ERROR;
    }
}

// 功能12 遍历线性表
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
status ListTraverse(LinkList L, void (*visitArr) (ElemType))
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        printf("\n-------------- all elements -------------------\n");
        for(LNode *p = L->next; p != NULL; p = p->next)
            if(p != L)
                visit(p->data);
        printf("\n------------------ end ------------------------\n");
        return OK;
    }
}

// 附加功能13 链表翻转
// 如果线性表L存在，则操作结果为将L翻转
status reverseList(LinkList &L)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        LinkList p;
        LNode *q, *pnext = NULL;
        p = (LNode *)malloc(sizeof(LNode));
        p->next = pnext;
        for(q = L->next; q != NULL; q = q->next)
        {
            p->data = q->data;
            pnext = p;
            p = (LNode *)malloc(sizeof(LNode));
            p->next = pnext;
        }
        L = p;
        return OK;
    }
}

// 附加功能14 删除链表倒数第n个结点
// 如果线性表L存在且非空，操作结果是该链表倒数第n个结点
int RemoveNthFromEnd(LinkList &L, int n)
{
    if(L == NULL)
        return INFEASIBLE;
    else if(ListEmpty(L) == TRUE)
        return ERROR;
    else
    {
        int len, m, node;
        len = ListLength(L);
        if(n > len)
            return ERROR;
        m = len + 1 - n;
        ListDelete(L, m, n);
        return n;
    }
}

// 功能15 排序
// 若线性表L已存在，将L由小到大排序
status sortList(LinkList &L)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {   //暴力求解（冒泡排序）
        LNode *p, *q;
        for(p = L->next; p != NULL; p = p->next)
            for(q = p->next; q != NULL; q = q->next)
                if(q->data < p->data)
                {
                    int tmp = q->data;
                    q->data = p->data;
                    p->data = tmp;
                }
        return OK;
    }
}

// 附加功能16 线性表写文件
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
status SaveList(LinkList L,char FileName[])
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {
        FILE *fp = fopen(FileName, "w");
        for(LNode *p = L->next; p != NULL; p = p->next) 
            fprintf(fp, "%d ", p->data);
        fclose(fp);
        return OK;
    }
}

// 附加功能17 线性表读文件
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
status LoadList(LinkList &L,char FileName[])
{
    if(L != NULL)
        return INFEASIBLE;
    else
    {
        int tmp;
        FILE *fp = fopen(FileName, "r");
        L = (LNode *)malloc(sizeof(LNode));
        L->next = NULL;
        LNode *q = L;
        while(fscanf(fp, "%d", &tmp) == 1)
        {
            LNode *p = (LNode *)malloc(sizeof(LNode));
            p->data = tmp;
            q->next = p;
            p->next = NULL;
            q = p;
        }
        fclose(fp);
        return OK;
    }
}

// 附加功能18 多线性表管理：增加新线性表
// 在Lists中增加一个名称为ListName的线性表。
status AddList(LISTS &Lists,char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))
        {
            printf("集合中已存在名称为 %s 的线性表！\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L = (LNode *)malloc(sizeof(LNode));
	Lists.elem[Lists.length].L->next = NULL;
    Lists.length++;
    return OK;
}

// 附加功能19 多线性表管理：删除线性表
// Lists中删除一个名称为ListName的线性表
status RemoveList(LISTS &Lists,char ListName[])
{
    int i;
    for(i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //匹配表名
            break;
    if(i == Lists.length)
        return ERROR;
    else
    {
        DestroyList(Lists.elem[i].L);
        memset(Lists.elem[i].name, 0, strlen(Lists.elem[i].name));
        Lists.length--;
        for(int j = i; j < Lists.length; j++)
            Lists.elem[j] = Lists.elem[j + 1];
        return OK;
    }
}

// 附加功能20 多线性表管理：查找线性表
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
int LocateList(LISTS Lists, char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //匹配表名
            return (i + 1);
    return ERROR;
}

// 附加功能21 多线性表管理：遍历多线性表
status ListsTraverse(LISTS Lists)
{
    if (Lists.length == 0)
        return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("表名为 %s 的元素有：", Lists.elem[n].name);
        ListTraverse(Lists.elem[n].L, visit);
        putchar('\n');
    }
    return OK;
}

// 附加功能22 多线性表管理：选择一个线性表，输入其序号，后续可对其进行操作
LinkList *ChooseList(LinkList *L, LISTS &Lists, int i) 
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        L = &(Lists.elem[i - 1].L);  //传递地址以同时改动单表与多表中的此表    
        return L;
    }
}