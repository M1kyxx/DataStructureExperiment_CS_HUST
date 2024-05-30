/* Linear Table On Linked Structure */
/*ͷ�ļ�*/
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

/*status*/
#define TRUE 1      //�ж����Ϊ��ȷ
#define FALSE 0     //�ж����Ϊ����
#define OK 1        //������������
#define ERROR 0     //���ܳ��ִ����޷�����
#define INFEASIBLE -1//�������󲻴���
#define OVERFLOW -2 //�ڴ����

/*����Ԫ������*/
typedef int status; 
typedef int ElemType;

/*��ʼ���뵥λ��*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

/*��������*/
typedef struct LNode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

/*���Ա�Ĺ����*/
typedef struct{
    struct{ 
        char name[30];
     	LinkList L;	
    }elem[10];
    int length;
    int listsize;
}LISTS;

/*�������*/
status Compare(ElemType e, ElemType elem);  //�ȽϺ���
void visit(ElemType elem);                  //���ʺ���

/*�������ָ��*/
status (*CompareArr)(ElemType e, ElemType elem) = Compare;
void (*visitArr)(ElemType elem) = visit;

/*���������������*/
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

/*ѡ����������*/
status reverseList(LinkList &L);
int RemoveNthFromEnd(LinkList &L, int n);
status sortList(LinkList &L);

/*�ļ���д����*/
status SaveList(LinkList L, char FileName[]);
status LoadList(LinkList &L, char FileName[]);

/*����������*/
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
LinkList* ChooseList(LinkList *L, LISTS &Lists, int i);





/*---------------------main����-----------------------*/
int main(void)
{
    //���嵥����ʼ��
    LinkList L1 = NULL;
	LinkList *L = &L1;

    //����������ʼ��
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
		printf("    	  1. ����         12. ����\n");
		printf("    	  2. ����         13. ��ת����\n");
		printf("    	  3. ���         14. ɾ����������n�����\n");
		printf("    	  4. �п�         15. ����\n");
		printf("    	  5. ��         16. д���ļ�\n");
		printf("    	  6. ��ȡԪ��     17. ��ȡ�ļ�\n");
        printf("    	  7. ����Ԫ��     18. �������Ա�\n");
        printf("    	  8. ��ȡǰ��     19. ɾ�����Ա�\n");
        printf("    	  9. ��ȡ���     20. �������Ա�\n");
        printf("    	 10. ����Ԫ��     21. �����ܱ�\n");
        printf("    	 11. ɾ��Ԫ��     22. ѡ�񵥱���в���\n");
		printf("    	  0. �˳�\n");
		printf("------------------------------------------------------\n");
        printf("    ��ȷ���ఴ���λس���������ˢ�º���ѡ�����\n");
		printf("    ��ѡ����Ĳ���[0~22]:");
		scanf("%d", &op);
		switch(op)
		{
			case 1://����
				if(InitList(*L) == OK)
					printf("���Ա����ɹ���\n����һ��������ڶ��ĵ�������Զ�������1~17������\n");
				else
					printf("���Ա���ʧ�ܣ�\n");
                getchar();getchar();
				break;
			case 2://����
				if(DestroyList(*L) == OK)
                    printf("�ɹ��������Ա��ͷ�����Ԫ�صĿռ䣡\n");
                else
                    printf("���ܶԲ����ڵ����Ա�������ٲ�����\n");
                getchar();getchar();
				break;
			case 3://���
				if(ClearList(*L) == OK)
                    printf("�ɹ�ɾ�����Ա������е�Ԫ�أ�\n");
                else
                    printf("���ܶԲ����ڵ����Ա������ղ�����\n");
                getchar();getchar();
				break;
			case 4://�п�
				flag = ListEmpty(*L);
                if(flag == TRUE)
                    printf("���Ա�Ϊ�գ�\n");
                else if(flag == FALSE)
                    printf("���Ա�ǿգ�\n");
                else
                    printf("���ܶԲ����ڵ����Ա��пգ�\n");
                getchar();getchar();
				break;
			case 5://��
				len = ListLength(*L);
                if(len >= 0)
                    printf("���Ա�ĳ���Ϊ%d��\n", len);
                else
                    printf("���ܶԲ����ڵ����Ա��󳤣�\n");
                getchar();getchar();
				break;
			case 6://��ȡԪ��
				printf("��������Ҫ�����Ա��л�ȡ��Ԫ����ţ�");
                scanf("%d", &i);
                getchar();
                flag = GetElem(*L, i, e);
                if(flag == OK)
                    printf("���Ա��е�%d��Ԫ��Ϊ%d��\n", i, e);
                else if(flag == ERROR)
                    printf("�������Ų��Ϸ���\n");
                else
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                getchar();getchar();
				break;
			case 7://����Ԫ��
				printf("��������Ҫ�����Ա��в��ҵ�Ԫ�أ�");
                scanf("%d", &e);
                getchar();
                flag = LocateElem(*L, e, Compare);
                if (flag == 0)
                    printf("���Ա��в�����%d���Ԫ�ء�\n", e);
                else if (flag == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                else
                    printf("Ԫ��%d�����Ա��е����Ϊ%d\n", e, flag);
                getchar();getchar();
				break;
			case 8://����ǰ��
				printf("��������Ҫ�����Ա��в�����ǰ����Ԫ�أ�");     
				scanf("%d", &e);
                getchar();
                flag = PriorElem(*L, e, pre);
                if(flag == OK)
                    printf("Ԫ��%d�����Ա��е�ǰ��Ϊ%d��\n", e, pre);
                else if(flag == ERROR)
                    printf("Ԫ��%d�����Ա���û��ǰ����\n", e);
                else
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                getchar();getchar();
				break;
			case 9://���Һ��
				printf("��������Ҫ�����Ա��в������̵�Ԫ�أ�");     
				scanf("%d", &e);
                getchar();
                flag = NextElem(*L, e, next);
                if(flag == OK)
                    printf("Ԫ��%d�����Ա��еĺ��Ϊ%d��\n", e, next);
                else if(flag == ERROR)
                    printf("Ԫ��%d�����Ա���û�к�̣�\n", e);
                else
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                getchar();getchar();
				break;
			case 10://����Ԫ��
                printf("1.���뵥��Ԫ��\n2.�ڱ�β������Ԫ��\n��ѡ��Ҫ���еĲ�����");
                scanf("%d", &flag);
                getchar();
                switch (flag)
                {
                    case 1:
                        printf("�������Ԫ�أ�");
                        scanf("%d", &e);
                        getchar();
                        printf("��������Ҫ����Ϊ�ڼ���Ԫ�أ�");
                        scanf("%d", &i);
                        getchar();
                        flag = ListInsert(*L, i, e);
                        if(flag == OK)
                            printf("Ԫ���Ѳ������Ա��У�\n");
                        else if(flag == ERROR)
                            printf("λ�ò���Ƿ���\n");
                        else
                            printf("���ܶԲ����ڵ����Ա���в��룡\n");
                        break;
                    case 2:
                        printf("������Ԫ�ظ�����");
                        scanf("%d", &num);
                        getchar();
                        printf("��������ЩԪ�أ��Կո�����");
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
                        printf("Ԫ�������������Ա��У�\n");
                        break;
                }
                getchar();getchar();
				break;
			case 11://ɾ��Ԫ��
				printf("��������Ҫɾ����Ԫ����ţ�");
                scanf("%d", &i);
                getchar();
                flag = ListDelete(*L, i, e);
                if(flag == OK)
                    printf("���Ϊ %d ��Ԫ�� %d �Ѿ������Ա���ɾ����\n", i, e);
                else if(flag == ERROR)
                    printf("λ������Ƿ���\n");
                else
                    printf("���ܶԲ����ڵ����Ա����ɾ����\n");     
				getchar();getchar();
				break;
			case 12://����
				if(ListTraverse(*L, visit) == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա���б�����\n");
				getchar();getchar();
                break;
            case 13://��ת����
                flag = reverseList(*L);
                if(flag == OK)
                    printf("��ǰ�����ѷ�ת��\n");
                else
                    printf("���ܶԲ����ڵ����Ա���з�ת��\n");
                getchar();getchar();
                break;
            case 14://ɾ��������n�����
                int n;
                printf("������ʵ��ɾ����������n����㣬������n��");
                scanf("%d", &n);
                flag = RemoveNthFromEnd(*L, n);
                if(flag == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա����ɾ��������\n");
                else if(flag == ERROR)
                    printf("���ܶԿ����Ա����ɾ��������n���Ϸ���\n");
                else
                    printf("�������� %d ��Ԫ�� %d �ѱ�ɾ����\n", n, flag);
                getchar();getchar();
                break;
            case 15://����
                flag = sortList(*L);
                if(flag == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա��������\n");
                else
                    printf("���Ա��Ѵ�С��������\n");
                getchar();getchar();
                break;
            case 16://д���ļ�
				printf("�������ļ����ƣ�");
                scanf("%s", FileName);
                flag = SaveList(*L, FileName);
                if (flag == ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else if (flag == OK)
                    printf("���Ա�������Ѿ����Ƶ�����Ϊ %s ���ļ��У�\n", FileName);
                else if (flag == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա���н���д�ļ�������\n");
				getchar();getchar();
				break;
            case 17://��ȡ�ļ�
				printf("�������ļ����ƣ�");
                scanf("%s", FileName);
                flag = LoadList(*L, FileName);
                if (flag == ERROR)
                    printf("�ļ���ʧ�ܣ�\n");
                else if (flag == OK)
                    printf("����Ϊ %s ���ļ��е������Ѹ��Ƶ����Ա��У�\n", FileName);
                else if (flag == INFEASIBLE)
                    printf("���ܶ��Ѵ��ڵ����Ա���н��ж��ļ������������������Ա�\n");
                else if (flag == OVERFLOW)
                    printf("�����\n");
				getchar();getchar();
				break;
            case 18://�������Ա�
				printf("�������������Ա�����ƣ�");
                scanf("%s", ListName);
                flag = AddList(Lists, ListName);
                if (flag == OK)
                    printf("�ɹ���������Ϊ %s �����Ա�\n", ListName);
                else
                    printf("����ʧ�ܣ�\n");
				getchar();getchar();
				break;
            case 19://ɾ�����Ա�
				if(Lists.length)
                {
                    printf("\n---------------- all lists --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("���Ա�ļ���Ϊ�գ��޷����д˲�����\n");
                    getchar();getchar();
                    break;
                }
				printf("��������Ҫɾ�������Ա�����ƣ�");
                scanf("%s", ListName);
                flag = RemoveList(Lists, ListName);
                if (flag == OK)
                    printf("�ɹ�ɾ������Ϊ %s �����Ա�\n", ListName);
                else if (flag == ERROR)
                    printf("ɾ��ʧ�ܣ�\n");
                getchar();getchar();
				break;
            case 20://�������Ա�
				if(!Lists.length)
                {
                    printf("���Ա�ļ���Ϊ�գ��޷����д˲�����\n");
                    getchar();getchar();
                    break;
                }
				printf("��������Ҫ���ҵ����Ա�����ƣ�");
                scanf("%s", ListName);
                i = LocateList(Lists, ListName);
                if (i == 0)
                    printf("����������Ϊ %s �����Ա�\n", ListName);
                else printf("����Ϊ %s �����Ա�����Ϊ %d ��\n", ListName, i);
                getchar();getchar();
				break;
            case 21://�����ܱ�
                flag = ListsTraverse(Lists);
                if (flag == ERROR)
                    printf("���Ա�ļ���Ϊ�գ�\n");
                getchar();getchar();
                break;
            case 22://ѡ�����еı���е�������
                if(Lists.length)
                {
                    printf("\n---------------- all lists --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("���Ա�ļ���Ϊ�գ��޷����д˲�����\n");
                    getchar();getchar();
                    break;
                }
                printf("��������Ҫ���в��������Ա����ţ���1��ʼ����");
                scanf("%d", &i);
                getchar();
                L = ChooseList(L, Lists, i);
                if (L == NULL)
                    printf("�������Ų��Ϸ����������ÿգ�\n");
                else
                    printf("����ɶ����Ա��������Ϊ %d �����Ա���в�����\n", i);
                getchar();getchar();
                break;
			case 0:
				break;
		}
	}
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}
/*---------------------main����-----------------------*/





// ������
status Compare(ElemType e, ElemType elem)
{
    if(elem == e)
        return OK;
    return ERROR;
}

// ���ʺ���
void visit(ElemType elem)
{
    printf("%d ", elem);
}

// ����1 �������Ա�
// �����Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
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

// ����2 �������Ա�
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
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

// ����3 ������Ա�
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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

// ����4 ���Ա��п�
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
status ListEmpty(LinkList L)
{
    if(L == NULL)
        return INFEASIBLE;
    else if(L->next == NULL)
        return TRUE;
    return FALSE;
}

// ����5 ���Ա���
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
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

// ����6 ��ȡԪ��
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����7 ����Ԫ��
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����ERROR�������Ա�L������ʱ������INFEASIBLE��
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

// ����8 ��ȡǰ��Ԫ��
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����9 ��ȡ���Ԫ��
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����10 ����Ԫ��
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����11 ɾ��Ԫ��
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����12 �������Ա�
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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

// ���ӹ���13 ����ת
// ������Ա�L���ڣ���������Ϊ��L��ת
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

// ���ӹ���14 ɾ����������n�����
// ������Ա�L�����ҷǿգ���������Ǹ���������n�����
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

// ����15 ����
// �����Ա�L�Ѵ��ڣ���L��С��������
status sortList(LinkList &L)
{
    if(L == NULL)
        return INFEASIBLE;
    else
    {   //������⣨ð������
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

// ���ӹ���16 ���Ա�д�ļ�
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
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

// ���ӹ���17 ���Ա���ļ�
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
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

// ���ӹ���18 �����Ա�������������Ա�
// ��Lists������һ������ΪListName�����Ա�
status AddList(LISTS &Lists,char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))
        {
            printf("�������Ѵ�������Ϊ %s �����Ա�\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);
    Lists.elem[Lists.length].L = (LNode *)malloc(sizeof(LNode));
	Lists.elem[Lists.length].L->next = NULL;
    Lists.length++;
    return OK;
}

// ���ӹ���19 �����Ա����ɾ�����Ա�
// Lists��ɾ��һ������ΪListName�����Ա�
status RemoveList(LISTS &Lists,char ListName[])
{
    int i;
    for(i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //ƥ�����
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

// ���ӹ���20 �����Ա�����������Ա�
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
int LocateList(LISTS Lists, char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //ƥ�����
            return (i + 1);
    return ERROR;
}

// ���ӹ���21 �����Ա�������������Ա�
status ListsTraverse(LISTS Lists)
{
    if (Lists.length == 0)
        return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("����Ϊ %s ��Ԫ���У�", Lists.elem[n].name);
        ListTraverse(Lists.elem[n].L, visit);
        putchar('\n');
    }
    return OK;
}

// ���ӹ���22 �����Ա����ѡ��һ�����Ա���������ţ������ɶ�����в���
LinkList *ChooseList(LinkList *L, LISTS &Lists, int i) 
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        L = &(Lists.elem[i - 1].L);  //���ݵ�ַ��ͬʱ�Ķ����������еĴ˱�    
        return L;
    }
}