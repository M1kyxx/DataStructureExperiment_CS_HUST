/* Linear Table On Sequence Structure */
/*ͷ�ļ�*/
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

/*����Ԫ������*/
typedef int status; 
typedef int ElemType;

/*��ʼ���뵥λ��*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT  10

/*˳���*/
typedef struct
{
    char name[30];
	ElemType *elem;
	int length;
	int listsize;
}SqList;

/*���Ա�Ĺ����*/
typedef struct
{
    SqList L[10];
    int length;
    int listsize;
}LISTS;

/*�������*/
status Compare(ElemType e, ElemType elem);
void visit(ElemType elem);

/*�������ָ��*/
status (*CompareArr)(ElemType e, ElemType elem) = Compare;
void (*visitArr)(ElemType elem) = visit;

/*���������������*/
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

/*ѡ����������*/
int MaxSubArray(SqList L);
int SubArrayNum(SqList L, int k);
status sortList(SqList &L);

/*�ļ���д����*/
status SaveList(SqList L, char FileName[]);
status LoadList(SqList &L, char FileName[]);

/*����������*/
status AddList(LISTS &Lists, char ListName[]);
status RemoveList(LISTS &Lists, char ListName[]);
int LocateList(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
SqList* ChooseList(SqList *L, LISTS &Lists, int i);


/*--------------------------------------------*/
int main(void)
{
    //���嵥����ʼ��
    SqList L1;
    L1.elem = NULL, L1.length = 0, L1.listsize = 0;
    memset(L1.name, 0, sizeof(L1.name));
	SqList *L = &L1;

    //����������ʼ��
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
		printf("    	  1. ����         12. ����\n");
		printf("    	  2. ����         13. ����������������\n");
		printf("    	  3. ���         14. ���ΪK����������Ŀ\n");
		printf("    	  4. �п�         15. ����\n");
		printf("    	  5. ��         16. д���ļ�\n");
		printf("    	  6. ��ȡԪ��     17. ��ȡ�ļ�\n");
        printf("    	  7. ����Ԫ��     18. �������Ա�\n");
        printf("    	  8. ��ȡǰ��     19. ɾ�����Ա�\n");
        printf("    	  9. ��ȡ���     20. �������Ա�\n");
        printf("    	 10. ����Ԫ��     21. �����ܱ�\n");
        printf("    	 11. ɾ��Ԫ��     22. ѡ�񵥱���в���\n");
		printf("    	  0. �˳�\n");
		printf("-------------------------------------------------\n");
        printf("    ��ȷ���ఴ���λس���������ˢ�º���ѡ�����\n");
		printf("    ��ѡ����Ĳ���[0~22]:");
		scanf("%d", &op);
		switch(op)
		{
			case 1:
				if(InitList(*L) == OK)
					printf("���Ա����ɹ���\n����һ��������ڶ��ĵ�������Զ�������1~17������\n");
				else
					printf("���Ա���ʧ�ܣ�\n");
                getchar();getchar();
				break;
			case 2:
				if(DestroyList(*L) == OK)
                    printf("�ɹ��������Ա��ͷ�����Ԫ�صĿռ䣡\n");
                else
                    printf("���ܶԲ����ڵ����Ա�������ٲ�����\n");
                getchar();getchar();
				break;
			case 3:
				if(ClearList(*L) == OK)
                    printf("�ɹ�ɾ�����Ա������е�Ԫ�أ�\n");
                else
                    printf("���ܶԲ����ڵ����Ա������ղ�����\n");
                getchar();getchar();
				break;
			case 4:
				flag = ListEmpty(*L);
                if(flag == TRUE)
                    printf("���Ա�Ϊ�գ�\n");
                else if(flag == FALSE)
                    printf("���Ա�ǿգ�\n");
                else
                    printf("���ܶԲ����ڵ����Ա��пգ�\n");
                getchar();getchar();
				break;
			case 5:
				len = ListLength(*L);
                if(len >= 0)
                    printf("���Ա�ĳ���Ϊ %d ��\n", len);
                else
                    printf("���ܶԲ����ڵ����Ա��󳤣�\n");
                getchar();getchar();
				break;
			case 6:
				printf("��������Ҫ�����Ա��л�ȡ��Ԫ����ţ�");
                scanf("%d", &i);
                getchar();
                flag = GetElem(*L, i, e);
                if(flag == OK)
                    printf("���Ա��е� %d ��Ԫ��Ϊ %d ��\n", i, e);
                else if(flag == ERROR)
                    printf("�������Ų��Ϸ���\n");
                else
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                getchar();getchar();
				break;
			case 7:
				printf("��������Ҫ�����Ա��в��ҵ�Ԫ�أ�");
                scanf("%d", &e);
                getchar();
                flag = LocateElem(*L, e, Compare);
                if (flag == 0)
                    printf("���Ա��в����� %d ���Ԫ�أ�\n", e);
                else if (flag == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                else
                    printf("Ԫ�� %d �����Ա��е����Ϊ %d ��\n", e, flag);
                getchar();getchar();
				break;
			case 8:
				printf("��������Ҫ�����Ա��в�����ǰ����Ԫ�أ�");     
				scanf("%d", &e);
                getchar();
                flag = PriorElem(*L, e, pre);
                if(flag == OK)
                    printf("Ԫ�� %d �����Ա��е�ǰ��Ϊ %d ��\n", e, pre);
                else if(flag == ERROR)
                    printf("Ԫ�� %d �����Ա���û��ǰ����\n", e);
                else
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                getchar();getchar();
				break;
			case 9:
				printf("��������Ҫ�����Ա��в������̵�Ԫ�أ�");     
				scanf("%d", &e);
                getchar();
                flag = NextElem(*L, e, next);
                if(flag == OK)
                    printf("Ԫ�� %d �����Ա��еĺ��Ϊ %d ��\n", e, next);
                else if(flag == ERROR)
                    printf("Ԫ�� %d �����Ա���û�к�̣�\n", e);
                else
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                getchar();getchar();
				break;
			case 10:
                printf("1.���뵥��Ԫ��\n2.������Ԫ��\n��ѡ��Ҫ���еĲ�����");
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
                        for(int k = 0; k < num; k++)
                            scanf("%d", &L->elem[L->length++]);
                        getchar();
                        printf("Ԫ�������������Ա��У�\n");
                        break;
                }
                getchar();getchar();
				break;
			case 11:
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
			case 12:   
				if(ListTraverse(*L, visit) == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա���б�����\n");
				getchar();getchar();
                break;
            case 13:
                num = MaxSubArray(*L);
                if(num == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                else if(num == ERROR)
                    printf("���Ա�Ϊ�ձ��޷�������\n");
                else
                    printf("�����Ա���������������Ϊ %d ��\n", num);
                getchar();getchar();
                break;
            case 14:
                printf("����������������ĺͣ�");
                scanf("%d", &k);
                getchar();
                num = SubArrayNum(*L, k);
                if(num == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա���д˲�����\n");
                else if(num == ERROR)
                    printf("���Ա�Ϊ�ձ��޷�������\n");
                else
                    printf("�����Ա��к�Ϊ %d ��������ĸ���Ϊ %d ��\n", k, num);
                getchar();getchar();
                break;
            case 15:
                flag = sortList(*L);
                if(flag == INFEASIBLE)
                    printf("���ܶԲ����ڵ����Ա��������\n");
                else
                    printf("���Ա��Ѵ�С��������\n");
                getchar();getchar();
                break;
            case 16:
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
            case 17:
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
            case 18:
				printf("�������������Ա�����ƣ�");
                scanf("%s", ListName);
                flag = AddList(Lists, ListName);
                if (flag == OK)
                    printf("�ɹ���������Ϊ %s �����Ա�\n", ListName);
                else
                    printf("����ʧ�ܣ�\n");
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
            case 20:
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
            case 21:
                flag = ListsTraverse(Lists);
                if (flag == ERROR)
                    printf("���Ա�ļ���Ϊ�գ�\n");
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

// ����1 �������Ա�
// �����Ա�L�����ڣ�����һ���յ����Ա�����OK�����򷵻�INFEASIBLE��
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

// ����2 �������Ա�
// ������Ա�L���ڣ��������Ա�L���ͷ�����Ԫ�صĿռ䣬����OK�����򷵻�INFEASIBLE��
status DestroyList(SqList &L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        free(L.elem);
        L.elem = NULL;  //�����ÿգ�free��ָ����ָ��ԭ��
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
}

// ����3 ������Ա�
// ������Ա�L���ڣ�ɾ�����Ա�L�е�����Ԫ�أ�����OK�����򷵻�INFEASIBLE��
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

// ����4 ���Ա��п�
// ������Ա�L���ڣ��ж����Ա�L�Ƿ�Ϊ�գ��վͷ���TRUE�����򷵻�FALSE��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����5 ���Ա���
// ������Ա�L���ڣ��������Ա�L�ĳ��ȣ����򷵻�INFEASIBLE��
int ListLength(SqList L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
        return L.length;
}

// ����6 ��ȡԪ��
// ������Ա�L���ڣ���ȡ���Ա�L�ĵ�i��Ԫ�أ�������e�У�����OK�����i���Ϸ�������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����7 ����Ԫ��
// ������Ա�L���ڣ�����Ԫ��e�����Ա�L�е�λ����Ų����ظ���ţ����e�����ڣ�����0�������Ա�L������ʱ������INFEASIBLE��
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

// ����8 ��ȡǰ��Ԫ��
// ������Ա�L���ڣ���ȡ���Ա�L��Ԫ��e��ǰ����������pre�У�����OK�����û��ǰ��������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����9 ��ȡ���Ԫ��
// ������Ա�L���ڣ���ȡ���Ա�LԪ��e�ĺ�̣�������next�У�����OK�����û�к�̣�����ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����10 ����Ԫ��
// ������Ա�L���ڣ���Ԫ��e���뵽���Ա�L�ĵ�i��Ԫ��֮ǰ������OK��������λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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
            if(i == L.length + 1)   //��Ϊ���һ��Ԫ��ʱ��ֱ�Ӳ��뼴��
            {
                L.elem[L.length] = e;
                L.length++;
                return OK;
            }
            for(int j = L.length - 1; j >= i - 1; j--)  //������Ҫ����λԪ������ƶ�
                L.elem[j + 1] = L.elem[j];
            L.elem[i - 1] = e;
            L.length++;
            return OK;
        }
    }
}

// ����11 ɾ��Ԫ��
// ������Ա�L���ڣ�ɾ�����Ա�L�ĵ�i��Ԫ�أ���������e�У�����OK����ɾ��λ�ò���ȷʱ������ERROR��������Ա�L�����ڣ�����INFEASIBLE��
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

// ����12 �������Ա�
// ������Ա�L���ڣ�������ʾ���Ա��е�Ԫ�أ�ÿ��Ԫ�ؼ��һ�񣬷���OK��������Ա�L�����ڣ�����INFEASIBLE��
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
            printf("���Ա��ǿձ�");
        printf("\n------------------ end ------------------------\n");
        return OK;
    }
}

// ���ӹ���13 ����������������
// �����Ա�L�Ѵ����ҷǿգ��ҳ�һ���������͵����������飨���������ٰ���һ��Ԫ�أ�������������
int MaxSubArray(SqList L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else if(!L.length)
        return ERROR;
    else
    {   //�������
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

// ���ӹ���14 ���ΪK����������Ŀ
// �����Ա�L�Ѵ����ҷǿ�, ���ظ������к�Ϊk������������ĸ���
int SubArrayNum(SqList L, int k)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else if(!L.length)
        return ERROR;
    else
    {   //�������
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

// ���ӹ���15 ����
// �����Ա�L�Ѵ��ڣ���L��С��������
status sortList(SqList &L)
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {   //������⣨ð������
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

// ���ӹ���16 ���Ա�д�ļ�
// ������Ա�L���ڣ������Ա�L�ĵ�Ԫ��д��FileName�ļ��У�����OK�����򷵻�INFEASIBLE��
status  SaveList(SqList L, char FileName[])
{
    if(L.elem == NULL)
        return INFEASIBLE;
    else
    {
        FILE *fp = fopen(FileName, "w");    //дģʽ���ļ�
        for(int i = 0; i < L.length; i++)
            fprintf(fp, "%d ", L.elem[i]);  //����int�����ݣ�ʹ�ø�ʽ�����
        fclose(fp);     //����ر��ļ�
        return OK;
    }
}

// ���ӹ���17 ���Ա���ļ�
// ������Ա�L�����ڣ���FileName�ļ��е����ݶ��뵽���Ա�L�У�����OK�����򷵻�INFEASIBLE��
status  LoadList(SqList &L, char FileName[])
{
    if(L.elem != NULL)
        return INFEASIBLE;
    else
    {
        int i = 0;
        FILE *fp = fopen(FileName, "r");    //��ģʽ���ļ�
        L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);     //�����ǰ�����٣������½���
        L.listsize = LIST_INIT_SIZE;
        while(!feof(fp))    //�жϵ�ǰfp�Ƿ񵽴��ļ�β
            fscanf(fp, "%d", &L.elem[i++]);     //����int�����ݣ�ʹ�ø�ʽ������
        L.length = i - 1;
        fclose(fp);     //����ر��ļ�
        return OK;
    }
}

// ���ӹ���18 �����Ա�������������Ա�
// ��Lists������һ������ΪListName�����Ա�
status AddList(LISTS &Lists,char ListName[])
{
    for(int i=0;i<Lists.length;i++)
        if (strcmp(Lists.L[i].name, ListName) == 0)
        {
            printf("�������Ѵ�������Ϊ %s �����Ա�\n", ListName);
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

// ���ӹ���19 �����Ա����ɾ�����Ա�
// Lists��ɾ��һ������ΪListName�����Ա�
status RemoveList(LISTS &Lists,char ListName[])
{
    int i;
    for(i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.L[i].name, ListName))  //ƥ�����
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

// ���ӹ���20 �����Ա�����������Ա�
// ��Lists�в���һ������ΪListName�����Ա��ɹ������߼���ţ����򷵻�0
int LocateList(LISTS Lists, char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.L[i].name, ListName))  //ƥ�����
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
        printf("��ǰ������%s ", Lists.L[n].name);
        ListTraverse(Lists.L[n], visit);
        putchar('\n');
    }
    return OK;
}

// ���ӹ���22 �����Ա����ѡ��һ�����Ա���������ţ������ɶ�����в���
SqList *ChooseList(SqList *L, LISTS &Lists, int i) 
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        L = &(Lists.L[i - 1]);  //���ݵ�ַ��ͬʱ�Ķ����������еĴ˱�    
        L->length = Lists.L[i - 1].length;
        L->elem = Lists.L[i - 1].elem;
        return L;
    }
}