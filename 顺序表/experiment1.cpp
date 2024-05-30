/* Linear Table On Sequence Structure */
/*头文件*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

/*status*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

/*数据元素类型*/
typedef int status; 
typedef int ElemType;

/*初始表长与单位表长*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

/*顺序表*/
typedef struct
{
    char name[30];
	ElemType *elem;
	int length;
	int listsize;
}SqList;

/*线性表的管理表*/
typedef struct
{
    SqList L[10];
    int length;
    int listsize;
}LISTS;

/*零件函数*/
status Compare(ElemType e, ElemType elem);
void visit(ElemType elem);

/*零件函数指针*/
status (*CompareArr)(ElemType e, ElemType elem) = Compare;
void (*visitArr)(ElemType elem) = visit;

/*单表基础操作函数*/
status InitList(SqList &L);
status DestroyList(SqList &L);
status ClearList(SqList &L);
status ListEmpty(SqList L);
int ListLength(SqList L);
status GetElem(SqList L, int i, ElemType &e);
int LocateElem(SqList L, ElemType e, status (*CompareArr)(ElemType, ElemType)); 
status PriorElem(SqList L, ElemType cur, ElemType &pre_e);
status NextElem(SqList L, ElemType cur, ElemType &next_e);
status ListInsert(SqList &L, int i, ElemType e);
status ListDelete(SqList &L, int i, ElemType &e);
status ListTraverse(SqList L, void (*visitArr)(ElemType));

/*选做操作函数*/
int MaxSubArray(SqList L);
int SubArrayNum(SqList L, int k);
status sortList(SqList &L);

/*文件读写函数*/
status SaveList(SqList L, char FileName[]);
status LoadList(SqList &L, char FileName[]);

/*多表操作函数*/
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
SqList* ChooseList(SqList *L, LISTS &Lists, int i);


/*--------------------------------------------*/
int main(void)
{
    //定义单表并初始化
    SqList L1;
    L1.elem = NULL, L1.length = 0, L1.listsize = 0;
    memset(L1.name, 0, sizeof(L1.name));
	SqList *L = &L1;

    //定义管理表并初始化
    LISTS Lists;
    Lists.length = 0, Lists.listsize = 0;

	int op = 1, len, flag, i, e, pre, next, num, k;
    char FileName[30], ListName[30];
	while(op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Linear Table On Sequence Structure \n");
		printf("-------------------------------------------------\n");
		printf("    	  1. 创建         12. 遍历\n");
		printf("    	  2. 销毁         13. 求最大连续子数组和\n");
		printf("    	  3. 清空         14. 求和为K的子数组数目\n");
		printf("    	  4. 判空         15. 排序\n");
		printf("    	  5. 求长         16. 写入文件\n");
		printf("    	  6. 获取元素     17. 读取文件\n");
        printf("    	  7. 查找元素     18. 增加线性表\n");
        printf("    	  8. 获取前驱     19. 删除线性表\n");
        printf("    	  9. 获取后继     20. 查找线性表\n");
        printf("    	 10. 输入元素     21. 遍历总表\n");
        printf("    	 11. 删除元素     22. 选择单表进行操作\n");
		printf("    	  0. 退出\n");
		printf("-------------------------------------------------\n");
        printf("    请确保多按几次回车键至窗口刷新后再选择操作\n");
		printf("    请选择你的操作[0~22]:");
		scanf("%d", &op);
		switch(op)
		{
			case 1:
				if(InitList(*L) == OK)
					printf("线性表创建成功！\n这是一个与独立于多表的单表，你可以对它进行1~17操作！\n");
				else
					printf("线性表创建失败！\n");
                getchar();getchar();
				break;
			case 2:
				if(DestroyList(*L) == OK)
                    printf("成功销毁线性表并释放数据元素的空间！\n");
                else
                    printf("不能对不存在的线性表进行销毁操作！\n");
                getchar();getchar();
				break;
			case 3:
				if(ClearList(*L) == OK)
                    printf("成功删除线性表中所有的元素！\n");
                else
                    printf("不能对不存在的线性表进行清空操作！\n");
                getchar();getchar();
				break;
			case 4:
				flag = ListEmpty(*L);
                if(flag == TRUE)
                    printf("线性表为空！\n");
                else if(flag == FALSE)
                    printf("线性表非空！\n");
                else
                    printf("不能对不存在的线性表判空！\n");
                getchar();getchar();
				break;
			case 5:
				len = ListLength(*L);
                if(len >= 0)
                    printf("线性表的长度为 %d ！\n", len);
                else
                    printf("不能对不存在的线性表求长！\n");
                getchar();getchar();
				break;
			case 6:
				printf("请输入想要从线性表中获取的元素序号：");
                scanf("%d", &i);
                getchar();
                flag = GetElem(*L, i, e);
                if(flag == OK)
                    printf("线性表中第 %d 个元素为 %d ！\n", i, e);
                else if(flag == ERROR)
                    printf("输入的序号不合法！\n");
                else
                    printf("不能对不存在的线性表进行此操作！\n");
                getchar();getchar();
				break;
			case 7:
				printf("请输入想要在线性表中查找的元素：");
                scanf("%d", &e);
                getchar();
                flag = LocateElem(*L, e, Compare);
                if (flag == 0)
                    printf("线性表中不存在 %d 这个元素！\n", e);
                else if (flag == INFEASIBLE)
                    printf("不能对不存在的线性表进行此操作！\n");
                else
                    printf("元素 %d 在线性表中的序号为 %d ！\n", e, flag);
                getchar();getchar();
				break;
			case 8:
				printf("请输入想要在线性表中查找其前驱的元素：");     
				scanf("%d", &e);
                getchar();
                flag = PriorElem(*L, e, pre);
                if(flag == OK)
                    printf("元素 %d 在线性表中的前驱为 %d ！\n", e, pre);
                else if(flag == ERROR)
                    printf("元素 %d 在线性表中没有前驱！\n", e);
                else
                    printf("不能对不存在的线性表进行此操作！\n");
                getchar();getchar();
				break;
			case 9:
				printf("请输入想要在线性表中查找其后继的元素：");     
				scanf("%d", &e);
                getchar();
                flag = NextElem(*L, e, next);
                if(flag == OK)
                    printf("元素 %d 在线性表中的后继为 %d ！\n", e, next);
                else if(flag == ERROR)
                    printf("元素 %d 在线性表中没有后继！\n", e);
                else
                    printf("不能对不存在的线性表进行此操作！\n");
                getchar();getchar();
				break;
			case 10:
                printf("1.插入单个元素\n2.输入多个元素\n请选择将要进行的操作：");
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
                        for(int k = 0; k < num; k++)
                            scanf("%d", &L->elem[L->length++]);
                        getchar();
                        printf("元素已输入于线性表中！\n");
                        break;
                }
                getchar();getchar();
				break;
			case 11:
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
			case 12:   
				if(ListTraverse(*L, visit) == INFEASIBLE)
                    printf("不能对不存在的线性表进行遍历！\n");
				getchar();getchar();
                break;
            case 13:
                num = MaxSubArray(*L);
                if(num == INFEASIBLE)
                    printf("不能对不存在的线性表进行此操作！\n");
                else if(num == ERROR)
                    printf("线性表为空表！无法操作！\n");
                else
                    printf("本线性表最大连续子数组和为 %d ！\n", num);
                getchar();getchar();
                break;
            case 14:
                printf("请输入所求子数组的和：");
                scanf("%d", &k);
                getchar();
                num = SubArrayNum(*L, k);
                if(num == INFEASIBLE)
                    printf("不能对不存在的线性表进行此操作！\n");
                else if(num == ERROR)
                    printf("线性表为空表！无法操作！\n");
                else
                    printf("本线性表中和为 %d 的子数组的个数为 %d ！\n", k, num);
                getchar();getchar();
                break;
            case 15:
                flag = sortList(*L);
                if(flag == INFEASIBLE)
                    printf("不能对不存在的线性表进行排序！\n");
                else
                    printf("线性表已从小到大排序！\n");
                getchar();getchar();
                break;
            case 16:
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
            case 17:
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
            case 18:
				printf("请输入新增线性表的名称：");
                scanf("%s", ListName);
                flag = AddList(Lists, ListName);
                if (flag == OK)
                    printf("成功新增名称为 %s 的线性表！\n", ListName);
                else
                    printf("新增失败！\n");
				getchar();getchar();
				break;
            case 19:
                if(Lists.length)
                {
                    printf("\n---------------- all lists --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.L[i].name);
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
            case 20:
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
            case 21:
                flag = ListsTraverse(Lists);
                if (flag == ERROR)
                    printf("线性表的集合为空！\n");
                getchar();getchar();
                break;
            case 22:
                if(Lists.length)
                {
                    printf("\n---------------- all lists --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.L[i].name);
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

status Compare(ElemType e, ElemType elem)
{
    if(elem == e)
        return OK;
    return ERROR;
}

void visit(ElemType elem)
{
    printf("%d ", elem);
}

// 功能1 创建线性表
// 若线性表L不存在，构造一个空的线性表，返回OK，否则返回INFEASIBLE。
status InitList(SqList &L)
{
    if(L.elem != NULL)
        return INFEASIBLE;
    else
    {
        L.elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
        L.length = 0;
	    L.listsize = LIST_INIT_SIZE;
	    return OK;
    }
}

// 功能2 销毁线性表
// 如果线性表L存在，销毁线性表L，释放数据元素的空间，返回OK，否则返回INFEASIBLE。
status DestroyList(SqList &L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        free(L.elem);
        L.elem = NULL;  //必须置空，free后指针仍指向原处
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
}

// 功能3 清空线性表
// 如果线性表L存在，删除线性表L中的所有元素，返回OK，否则返回INFEASIBLE。
status ClearList(SqList& L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        memset(L.elem, 0, sizeof(ElemType) * L.length);
        L.length = 0;
        return OK;
    }
}

// 功能4 线性表判空
// 如果线性表L存在，判断线性表L是否为空，空就返回TRUE，否则返回FALSE；如果线性表L不存在，返回INFEASIBLE。
status ListEmpty(SqList L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        if(L.length)
            return FALSE;
        else
            return TRUE;
    }
}

// 功能5 线性表求长
// 如果线性表L存在，返回线性表L的长度，否则返回INFEASIBLE。
int ListLength(SqList L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
        return L.length;
}

// 功能6 获取元素
// 如果线性表L存在，获取线性表L的第i个元素，保存在e中，返回OK；如果i不合法，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status GetElem(SqList L,int i,ElemType &e)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        if(i < 1 || i > L.length)
            return ERROR;
        else
        {
            e = L.elem[i - 1];
            return OK;
        }
    }
}

// 功能7 查找元素
// 如果线性表L存在，查找元素e在线性表L中的位置序号并返回该序号；如果e不存在，返回0；当线性表L不存在时，返回INFEASIBLE。
int LocateElem(SqList L,ElemType e, status (*CompareArr)(ElemType, ElemType))
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        for(int i = 0; i < L.length; i++)
        {
            if(Compare(e, L.elem[i]) == OK)
                return (i + 1);
        }
        return ERROR;
    }
}

// 功能8 获取前驱元素
// 如果线性表L存在，获取线性表L中元素e的前驱，保存在pre中，返回OK；如果没有前驱，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status PriorElem(SqList L, ElemType e, ElemType &pre)
{
    int loc = 0;
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        for(int i = 0; i < L.length; i++)
            if(e == L.elem[i])
            {
                loc = i;
                break;
            }
    }
    if(!loc)
        return ERROR;
    else
    {
        pre = L.elem[loc - 1];
        return OK;
    }
}

// 功能9 获取后继元素
// 如果线性表L存在，获取线性表L元素e的后继，保存在next中，返回OK；如果没有后继，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status NextElem(SqList L,ElemType e,ElemType &next)
{
    int loc = L.length - 1;
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        for(int i = 0; i < L.length; i++)
            if(e == L.elem[i])
            {
                loc = i;
                break;
            }
    }
    if(loc == (L.length - 1))
        return ERROR;
    else
    {
        next = L.elem[loc + 1];
        return OK;
    }
}

// 功能10 输入元素
// 如果线性表L存在，将元素e插入到线性表L的第i个元素之前，返回OK；当插入位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListInsert(SqList &L, int i, ElemType e)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        if(i < 1 || i > L.length + 1)
            return ERROR;
        else
        {
            if(i == L.length + 1)   //作为最后一个元素时，直接插入即可
            {
                L.elem[L.length] = e;
                L.length++;
                return OK;
            }
            for(int j = L.length - 1; j >= i - 1; j--)  //否则需要将后位元素向后移动
                L.elem[j + 1] = L.elem[j];
            L.elem[i - 1] = e;
            L.length++;
            return OK;
        }
    }
}

// 功能11 删除元素
// 如果线性表L存在，删除线性表L的第i个元素，并保存在e中，返回OK；当删除位置不正确时，返回ERROR；如果线性表L不存在，返回INFEASIBLE。
status ListDelete(SqList &L, int i, ElemType &e)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        if(i < 1 || i > L.length)
            return ERROR;
        else
        {
            e = L.elem[i - 1];
            for(int j = i - 1; j < L.length - 1; j++)
                L.elem[j] = L.elem[j + 1];
            L.length--;
            return OK;
        }
    }
}

// 功能12 遍历线性表
// 如果线性表L存在，依次显示线性表中的元素，每个元素间空一格，返回OK；如果线性表L不存在，返回INFEASIBLE。
status ListTraverse(SqList L, void (*visitArr) (ElemType))
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        printf("\n-------------- all elements -------------------\n");
        if(L.length)
            for(int i = 0; i < L.length; i++)
                visit(L.elem[i]);
        else
            printf("线性表是空表！");
        printf("\n------------------ end ------------------------\n");
        return OK;
    }
}

// 附加功能13 求最大连续子数组和
// 若线性表L已存在且非空，找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和
int MaxSubArray(SqList L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else if(!L.length)
        return ERROR;
    else
    {   //暴力求解
        int max = 0, sum = 0, i, j;
        for(i = 0; i < L.length; i++)
        {
            sum = 0;
            for(j = i; j < L.length; j++)
            {
                sum += L.elem[j];
                if(sum > max)
                    max = sum;
            }
        }
        return max;
    }
}

// 附加功能14 求和为K的子数组数目
// 若线性表L已存在且非空, 返回该数组中和为k的连续子数组的个数
int SubArrayNum(SqList L, int k)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else if(!L.length)
        return ERROR;
    else
    {   //暴力求解
        int n = 0, sum = 0, i, j;
        for(i = 0; i < L.length; i++)
        {
            sum = 0;
            for(j = i; j < L.length; j++)
            {
                sum += L.elem[j];
                if(sum == k)
                    n++;
            }
        }
        return n;
    }
}

// 附加功能15 排序
// 若线性表L已存在，将L由小到大排序
status sortList(SqList &L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {   //暴力求解（冒泡排序）
        for(int i = 0; i < L.length; i++)
            for(int j = i; j < L.length; j++)
                if(L.elem[j] < L.elem[i])
                {
                    int tmp = L.elem[j];
                    L.elem[j] = L.elem[i];
                    L.elem[i] = tmp;
                }
        return OK;
    }
}

// 附加功能16 线性表写文件
// 如果线性表L存在，将线性表L的的元素写到FileName文件中，返回OK，否则返回INFEASIBLE。
status  SaveList(SqList L, char FileName[])
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        FILE *fp = fopen(FileName, "w");    //写模式打开文件
        for(int i = 0; i < L.length; i++)
            fprintf(fp, "%d ", L.elem[i]);  //对于int型数据，使用格式化输出
        fclose(fp);     //必须关闭文件
        return OK;
    }
}

// 附加功能17 线性表读文件
// 如果线性表L不存在，将FileName文件中的数据读入到线性表L中，返回OK，否则返回INFEASIBLE。
status  LoadList(SqList &L, char FileName[])
{
    if(L.elem != NULL)
        return INFEASIBLE;
    else
    {
        int i = 0;
        FILE *fp = fopen(FileName, "r");    //读模式打开文件
        L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);     //单表此前已销毁，需重新建立
        L.listsize = LIST_INIT_SIZE;
        while(!feof(fp))    //判断当前fp是否到达文件尾
            fscanf(fp, "%d", &L.elem[i++]);     //对于int型数据，使用格式化输入
        L.length = i - 1;
        fclose(fp);     //必须关闭文件
        return OK;
    }
}

// 附加功能18 多线性表管理：增加新线性表
// 在Lists中增加一个名称为ListName的线性表。
status AddList(LISTS &Lists,char ListName[])
{
    for(int i=0;i<Lists.length;i++)
        if (strcmp(Lists.L[i].name, ListName) == 0)
        {
            printf("集合中已存在名称为 %s 的线性表！\n", ListName);
            return ERROR;
        }
    strcpy(Lists.L[Lists.length].name, ListName);
    Lists.L[Lists.length].elem = (ElemType *)malloc(LIST_INIT_SIZE * sizeof(ElemType));
	if(!Lists.L[Lists.length].elem)
		exit(OVERFLOW);
	Lists.L[Lists.length].length = 0;
	Lists.L[Lists.length].listsize = LIST_INIT_SIZE;
    Lists.length++;
    return OK;
}

// 附加功能19 多线性表管理：删除线性表
// Lists中删除一个名称为ListName的线性表
status RemoveList(LISTS &Lists,char ListName[])
{
    int i;
    for(i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.L[i].name, ListName))  //匹配表名
            break;
    if(i == Lists.length)
        return ERROR;
    else
    {
        DestroyList(Lists.L[i]);
        Lists.length--;
        for(int j = i; j < Lists.length; j++)
            Lists.L[j] = Lists.L[j + 1];
        return OK;
    }
}

// 附加功能20 多线性表管理：查找线性表
// 在Lists中查找一个名称为ListName的线性表，成功返回逻辑序号，否则返回0
int LocateList(LISTS Lists, char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.L[i].name, ListName))  //匹配表名
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
        printf("当前表名：%s ", Lists.L[n].name);
        ListTraverse(Lists.L[n], visit);
        putchar('\n');
    }
    return OK;
}

// 附加功能22 多线性表管理：选择一个线性表，输入其序号，后续可对其进行操作
SqList *ChooseList(SqList *L, LISTS &Lists, int i) 
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        L = &(Lists.L[i - 1]);  //传递地址以同时改动单表与多表中的此表    
        L->length = Lists.L[i - 1].length;
        L->elem = Lists.L[i - 1].elem;
        return L;
    }
}