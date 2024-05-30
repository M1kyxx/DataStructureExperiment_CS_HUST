/* Binary Tree On BiLinked Structure */
/* ͷ�ļ� */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

/* status */
#define TRUE 1       //�ж����Ϊ��ȷ
#define FALSE 0      //�ж����Ϊ����
#define OK 1         //������������
#define ERROR 0      //���ܳ��ִ����޷�����
#define INFEASIBLE -1//�������󲻴���
#define OVERFLOW -2  //�ڴ����

/* ����Ԫ������ */
typedef int status;  //״̬
typedef int KeyType; //�ؼ�������

/* ������������� */
typedef struct{
        KeyType key;     //�ؼ���
        char others[20]; //����
}TElemType; 

/* ���������� */
typedef struct BiTNode{
        TElemType  data;                //������
        struct BiTNode *lchild,*rchild; //ָ����(�������Һ���)
}BiTNode, *BiTree;

/* ѭ������Ԫ������ */
typedef BiTNode* ElemType;

/* ѭ���������� */
#define MAXLENGTH 100

/* ѭ�����нṹ */
typedef struct QUEUE{
    ElemType elem[MAXLENGTH];   //ѭ������Ԫ��
    int front, length;          //ѭ�����ж�λ�ñ���
}QUEUE;

/* �������Ĺ���� */
typedef struct{
    struct{ 
        char name[30];  //����������
     	BiTree T;
    }elem[10];
    int length;         //�������(����������)
    int listsize;       //���������
}LISTS;


static int flag_create = 0, k = 0;      //flag_create, k���ڴ��������ı��
static BiTNode *p = NULL, *pt = NULL;   //p��pt���ڲ����ֵܺͽ�㸳ֵʱ��ʱ������
static int flag1 = 0, flag3 = 0;        //flag1��flag3����ɾ�����ͽ�㸳ֵʱ���б��

/* ������� */
status Compare(KeyType e, TElemType elem);  //�ȽϺ���
void visit(BiTree elem);                    //���ʺ���
int max(int x, int y);                      //��ϴ�ֵ����

/* �������ָ�� */
status (*CompareArr)(KeyType e, TElemType elem) = Compare;
void (*visitArr)(BiTree elem) = visit;

/* ���в������� */
void iniQueue(QUEUE &Q);
status enQueue(QUEUE &Q, ElemType e);
status deQueue(QUEUE &Q, ElemType &e);

/* ���������������� */
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

/*ѡ����������*/
int MaxPathSum(BiTree T);
BiTNode* LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);
status InvertTree(BiTree &T);

/*�ļ���д����*/
status SaveBiTree(BiTree T, char FileName[]);
status LoadBiTree(BiTree &T, char FileName[]);

/*������������*/
status AddTree(LISTS &Lists, char ListName[]);
status RemoveTree(LISTS &Lists, char ListName[]);
int LocateTree(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
BiTree* ChooseTree(BiTree *L, LISTS &Lists, int i);










/*---------------------main����-----------------------*/
int main(void)
{
    //���嵥������ʼ��
    BiTree T1 = NULL;
	BiTree *T = &T1;

    //����������ʼ��
    LISTS Lists;
    Lists.length = 0, Lists.listsize = 10;

	int op = 1, flag = 0, j = 0;     //op��¼����ѡ�������flag��¼�����������
    char FileName[30], ListName[30]; //�����ļ��������
    BiTNode *BTN = NULL;             //������ʱ������
    TElemType definition[100];       //����ǰ���������
    memset(definition, 0, 100 * sizeof(TElemType));
	while(op)
	{
		system("cls");
		printf("\n\n");
		printf("       Menu for Binary Tree On BiLinked Structure \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. ����         13. �������\n");
		printf("    	  2. ����         14. �������\n");
		printf("    	  3. ���         15. �����·����\n");
		printf("    	  4. �п�         16. �������������\n");
		printf("    	  5. ����         17. ��ת������\n");
		printf("    	  6. ���ҽ��     18. д���ļ�\n");
        printf("    	  7. ��㸳ֵ     19. ��ȡ�ļ�\n");
        printf("    	  8. ��ȡ�ֵ�     20. ���Ӷ�����\n");
        printf("    	  9. ������     21. ɾ��������\n");
        printf("    	 10. ɾ�����     22. ���Ҷ�����\n");
        printf("    	 11. ǰ�����     23. �����ܱ�\n");
        printf("    	 12. �������     24. ѡ�������в���\n");
		printf("    	  0. �˳�\n");
		printf("------------------------------------------------------\n");
        printf("    ��ȷ���ఴ���λس���������ˢ�º���ѡ�����\n");
		printf("    ��ѡ����Ĳ���[0~24]:");
		scanf("%d", &op);
		switch(op)
		{
			case 1://����
                if(*T != NULL)
                    printf("�������Ѵ��ڣ��޷��ٴ�����\n");
                else
                {
                    flag_create = 0, k = 0;//����static����
                    printf("������ǰ��������У�");
                    do
                    {
                        scanf("%d %s", &definition[j].key, definition[j].others);
                    } while (definition[j++].key != -1);
                    flag = CreateBiTree(*T, definition);
                    if(flag == OK)
                        printf("�����������ɹ���\n����һ��������ڶ����ĵ���������Զ�������1~19������\n");
                    else if(flag == ERROR)
                        printf("�ؼ��ʲ�Ψһ������������ʧ�ܣ�\n");
                }
                getchar();getchar();
				break;
			case 2://����
                flag = DestroyBiTree(*T);
                if(flag == OK)
                    printf("�ɹ����ٶ��������ͷ�����Ԫ�صĿռ䣡\n");
                else
                    printf("���ܶԲ����ڵĶ������������ٲ�����\n");
                getchar();getchar();
				break;
			case 3://���
                flag = ClearBiTree(*T);
                if(flag == OK)
                    printf("�ɹ���ն�������\n");
                else
                    printf("���ܶԲ����ڵĶ�����������ղ�����\n");
                getchar();getchar();
				break;
			case 4://�п�
                flag = BiTreeEmpty(*T);
                if(flag == TRUE)
                    printf("������Ϊ�գ�\n");
                else if(flag == FALSE)
                    printf("��������Ϊ�գ�\n");
                else
                    printf("���ܶԲ����ڵĶ����������пղ�����\n");
                getchar();getchar();
				break;
			case 5://����
                // if(*T == NULL)
                //     printf("���ܶԲ����ڵĶ������������������\n");
                // else
                {
                    flag = BiTreeDepth(*T);
                    printf("�����������Ϊ %d��\n", flag);
                }
                getchar();getchar();
				break;
			case 6://���ҽ��
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������в��ҽ�������\n");
                else
                {
                    int e = 0;//�洢�ؼ���
                    BTN = NULL;//�洢������
                    printf("��������Ҫ���ҵĽ��Ĺؼ��֣�");
                    scanf("%d", &e);
                    BTN = LocateNode(*T, e);
                    if(BTN == NULL)
                        printf("����ʧ�ܣ������ڹؼ���Ϊ %d �Ľ�㣡\n", e);
                    else
                        printf("���ҳɹ����ý��ؼ���Ϊ %d������Ϊ %s��\n", BTN->data.key, BTN->data.others);
                }
                getchar();getchar();
				break;
			case 7://��㸳ֵ
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������н�㸳ֵ������\n");
                else
                {
                    pt = NULL, flag3 = 0;//����static����
                    int e = 0;//�洢�ؼ���
                    TElemType value[5];//�洢�¹ؼ���������
                    memset(value, 0, 5 * sizeof(TElemType));//��ʼ��
                    printf("��������Ҫ��ֵ�Ľ��Ĺؼ��֣�");
                    scanf("%d", &e);
                    printf("�����뽫���Ĺؼ��������ݣ�");
                    scanf("%d %s", &value->key, value->others);
                    flag = Assign(*T, e, *value);
                    if(flag == OK)
                        printf("��ֵ�ɹ���\n");
                    else
                        printf("��ֵʧ�ܣ��ؼ����Ѵ��ڣ�\n");
                }
                getchar();getchar();
				break;
			case 8://��ȡ�ֵ�
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������л�ȡ�ֵܲ�����\n");
                else
                {
                    p = NULL;//����static����
                    int e = 0;//�洢�ؼ���
                    BTN = NULL;//�洢������
                    printf("��������Ҫ��ȡ���ֵܽ��Ľ��Ĺؼ��֣�");
                    scanf("%d", &e);
                    BTN = GetSibling(*T, e);
                    if(BTN == NULL)
                        printf("��ȡʧ�ܣ������ڹؼ���Ϊ %d �Ľ���ý��û���ֵܣ�\n", e);
                    else
                        printf("��ȡ�ɹ����ý����ֵܽ��Ĺؼ���Ϊ %d������Ϊ %s��\n", BTN->data.key, BTN->data.others);
                }
                getchar();getchar();
				break;
			case 9://������
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������в����������\n");
                else
                {
                    int e = 0, LR = 0;//�洢�ؼ�������뷽ʽ
                    printf("��������Ҫ����Ľ��ĸ����Ĺؼ��֣�");
                    scanf("%d", &e);
                    printf("LR = 0 ��Ϊ����\nLR = 1 ��Ϊ�Һ���\nLR = -1 ��Ϊ�����\n");
                    printf("��������뷽ʽ��");
                    scanf("%d", &LR);
                    if(LR == -1 || LR == 0 || LR == 1)
                    {
                        TElemType c[5];//�洢�¹ؼ���������
                        memset(c, 0, 5 * sizeof(TElemType));//��ʼ��
                        printf("�����뽫����Ĺؼ��������ݣ�");
                        scanf("%d %s", &c[0].key, c[0].others);
                        flag = InsertNode(*T, e, LR, c[0]);
                        if(flag == OK)
                            printf("����ɹ���\n");
                        else
                            printf("����ʧ�ܣ��ؼ����Ѵ��ڣ�\n");
                    }
                    else
                        printf("����ʧ�ܣ����뷽ʽ��������\n");
                }
                getchar();getchar();
				break;
			case 10://ɾ�����
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������в����������\n");
                else
                {
                    flag1 = 0;//����static����
                    int e = 0;//�洢�ؼ���
                    printf("��������ɾ���Ľ��Ĺؼ��֣�");
                    scanf("%d", &e);
                    flag = DeleteNode(*T, e);
                    if(flag == OK)
                        printf("ɾ���ɹ���\n");
                    else
                        printf("ɾ��ʧ�ܣ�\n");
                }
                getchar();getchar();
				break;
			case 11://ǰ�����
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ���������ǰ�����������\n");
                else
                {
                    printf("\n-------------- all elements -------------------\n");
                    PreOrderTraverse(*T, visit);
                    printf("\n------------------ end ------------------------\n");
                }
				getchar();getchar();
				break;
			case 12://�������
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ����������������������\n");
                else
                {
                    printf("\n-------------- all elements -------------------\n");
                    InOrderTraverse(*T, visit);
                    printf("\n------------------ end ------------------------\n");
                }
				getchar();getchar();
                break;
            case 13://�������
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������к������������\n");
                else
                {
                    printf("\n-------------- all elements -------------------\n");
                    PostOrderTraverse(*T, visit);
                    printf("\n------------------ end ------------------------\n");
                }
                getchar();getchar();
                break;
            case 14://�������
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������в������������\n");
                else
                {
                    printf("\n-------------- all elements -------------------\n");
                    LevelOrderTraverse(*T, visit);
                    printf("\n------------------ end ------------------------\n");
                }
                getchar();getchar();
                break;
            case 15://�����·����
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������иò�����\n");
                else
                {
                    flag = MaxPathSum(*T);
                    printf("�ö��������·����Ϊ %d��", flag);
                }
                getchar();getchar();
                break;
            case 16://�������������
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������иò�����\n");
                else
                {
                    int e1 = 0, e2 = 0;//�洢�ؼ���
                    BTN = NULL;//�洢������
                    printf("��������������������Ĺؼ��֣�\n");
                    scanf("%d %d", &e1, &e2);
                    BTN = LowestCommonAncestor(*T, e1, e2);
                    if(BTN == NULL)
                        printf("����ʧ�ܣ��ؼ�����������\n");
                    else
                        printf("�ؼ���Ϊ %d �� %d ���������������������Ϊ %d %s��\n", e1, e2, BTN->data.key, BTN->data.others);
                }
				getchar();getchar();
				break;
            case 17://��ת������
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������иò�����\n");
                else
                    if(InvertTree(*T) == OK)
                        printf("��������ת�ɹ���");
				getchar();getchar();
				break;
            case 18://д���ļ�
                if(*T == NULL)
                    printf("���ܶԲ����ڵĶ��������иò�����\n");
                else
                {
                    printf("�������ļ����ƣ�");
                    scanf("%s", FileName);
                    flag = SaveBiTree(*T, FileName);
                    if (flag == ERROR)
                        printf("�ļ���ʧ�ܣ�\n");
                    else if (flag == OK)
                        printf("�������������Ѿ����Ƶ�����Ϊ %s ���ļ��У�\n", FileName);
                }
				getchar();getchar();
				break;
            case 19://��ȡ�ļ�
                    printf("�������ļ����ƣ�");
                    scanf("%s", FileName);
                    flag = LoadBiTree(*T, FileName);
                    if (flag == ERROR)
                        printf("�ļ���ʧ�ܣ�\n");
                    else if (flag == OK)
                        printf("����Ϊ %s ���ļ��е������Ѹ��Ƶ��������У�\n", FileName);
                    else if (flag == INFEASIBLE)
                        printf("���ܶ��Ѵ��ڵĶ��������н��ж��ļ��������������ٶ�������\n");
                    else if (flag == OVERFLOW)
                        printf("�����\n");
                getchar();getchar();
				break;
            case 20://���Ӷ�����
                flag_create = 0, k = 0;
                printf("���������������������ƣ�");
                scanf("%s", ListName);
                flag = AddTree(Lists, ListName);
                if (flag == OK)
                    printf("�ɹ���������Ϊ %s �Ķ�������\n", ListName);
                else
                    printf("����ʧ�ܣ�\n");
                getchar();getchar();
				break;
            case 21://ɾ��������
                if(Lists.length)
                {
                    printf("\n---------------- all trees --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("�������ļ���Ϊ�գ��޷����д˲�����\n");
                    getchar();getchar();
                    break;
                }
				printf("��������Ҫɾ���Ķ����������ƣ�");
                scanf("%s", ListName);
                flag = RemoveTree(Lists, ListName);
                if (flag == OK)
                    printf("�ɹ�ɾ������Ϊ %s �Ķ�������\n", ListName);
                else if (flag == ERROR)
                    printf("ɾ��ʧ�ܣ�\n");
                getchar();getchar();
                break;
            case 22://���Ҷ�����
            {
                if(!Lists.length)
                {
                    printf("�������ļ���Ϊ�գ��޷����д˲�����\n");
                    getchar();getchar();
                    break;
                }
                int loc = 0;
				printf("��������Ҫ���ҵĶ����������ƣ�");
                scanf("%s", ListName);
                loc = LocateTree(Lists, ListName);
                if (loc == 0)
                    printf("����������Ϊ %s �Ķ�������\n", ListName);
                else
                    printf("����Ϊ %s �Ķ����������Ϊ %d ��\n", ListName, loc);
                getchar();getchar();
                break;
            }
            case 23://�����ܱ�
                flag = ListsTraverse(Lists);
                if (flag == ERROR)
                    printf("�������ļ���Ϊ�գ�\n");
                getchar();getchar();
                break;
            case 24://ѡ�������в���
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
                    printf("�������ļ���Ϊ�գ��޷����д˲�����\n");
                    getchar();getchar();
                    break;
                }
                int e = 0;
                printf("��������Ҫ���в����Ķ���������ţ���1��ʼ����");
                scanf("%d", &e);
                getchar();
                T = ChooseTree(T, Lists, e);
                if (T == NULL)
                    printf("�������Ų��Ϸ����������ÿգ�\n");
                else
                    printf("����ɶԶ��������������Ϊ %d �Ķ��������в�����\n", e);
                getchar();getchar();
                break;
            }
			case 0:
				break;
		}
	}
	printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
    return 0;
}
/*---------------------main����-----------------------*/












// ������
status Compare(KeyType e, TElemType elem)
{
    if(elem.key == e)
        return OK;
    return ERROR;
}

// ���ʺ���
void visit(BiTree elem)
{
    printf("| %d %s |", elem->data.key, elem->data.others);
}

// �����ֵ����
int max(int x, int y)
{
    return (x >= y) ? x : y;
}

// ��ʼ������Q
void iniQueue(QUEUE &Q)
{
    Q.front = 0;
    Q.length = 0;   //���г���Ϊ0
}

// Ԫ�����
status enQueue(QUEUE &Q, ElemType e)
{
    if(Q.length >= MAXLENGTH)   //�������
        return ERROR;
    Q.elem[(Q.front + Q.length++) % MAXLENGTH] = e;
    return OK;
}

// Ԫ�س���
// ��Q����Ԫ�س��ӣ���ֵ��e���ɹ����ӷ���1�����򷵻�0
status deQueue(QUEUE &Q, ElemType &e)
{
    if(Q.length == 0)   //����Ϊ��
        return ERROR;
    e = Q.elem[Q.front];
    Q.front = (Q.front + 1) % MAXLENGTH;
    Q.length--;
    return OK;
}

// ����1 ����
// ���ݴ���֦�Ķ������ȸ���������definition����һ�ö������������ڵ�ָ�븳ֵ��T������OK���������ͬ�Ĺؼ��֣�����ERROR��
status CreateBiTree(BiTree &T,TElemType definition[])
{
    if (flag_create == 0)
    {
        int i = 0, j = 0;   //�ؼ��ּ��ѭ���ñ���
        for (i = 0; definition[i].key != -1; i++)
        {
            if(definition[i].key == 0)
                continue;
            for (j = i + 1;definition[j].key != -1;j++)
                if (definition[j].key != 0)
                    if (definition[i].key == definition[j].key)
                        return ERROR;
        }
        flag_create = 1;    //����Ѿ����йؼ��ּ�飬�����ݹ������ٴμ��
    }
    if (flag_create == 1)
    {
        if (definition[k].key == 0) //�ؼ���Ϊ0ʱ��NULL
        {
            T = NULL;
            k++;    //definition��ǰ�ƽ�����һ���
        }
        else    //�ؼ��ֲ�Ϊ0ʱ���ɽ��
        {
            if (!(T = (BiTNode*)malloc(sizeof(BiTNode))))
                return OVERFLOW;
            T->data = definition[k];
            k++;    //definition��ǰ�ƽ�����һ���
            CreateBiTree(T->lchild, definition);//�ݹ�����������
            CreateBiTree(T->rchild, definition);//�ݹ�����������
        }
        return OK;
    }
}

// ����2 ����
// ��ʼ�����Ƕ�����T�Ѵ��ڣ�������������ٶ�����T��
status DestroyBiTree(BiTree &T)
{
   if (T)
   {
        DestroyBiTree(T->lchild);//�ݹ�����������
        DestroyBiTree(T->rchild);//�ݹ�����������
        free(T);    //���ٷ���Ŀռ�
        T = NULL;   //�����ÿգ�free��ָ����ָ��ԭ��
        return OK;
   }
   return ERROR;
}

// ����3 ���
// ��ʼ�����Ƕ�����T���ڣ���������ǽ�������T��ա�
status ClearBiTree(BiTree &T)
{
    if(T)
    {
        ClearBiTree(T->lchild);//�ݹ����������
        ClearBiTree(T->rchild);//�ݹ����������
        memset(T, 0, sizeof(BiTNode));//��ղ�����
        return OK;
    }
    return ERROR;
}

// ����4 �п�
// ��ʼ�����Ƕ�����T���ڣ������������TΪ�ն������򷵻�TRUE�����򷵻�FALSE��
status BiTreeEmpty(BiTree T)
{
    if(T == NULL)   //������������
        return INFEASIBLE;
    else if(T->data.key == 0)
        return TRUE;
    return FALSE;
}

// ����5 ����
// ��ʼ�����Ƕ�����T���ڣ���������Ƿ���T����ȡ�
int BiTreeDepth(BiTree T)
{
    int depthL = 0, depthR = 0;
    if(T == NULL)
        return 0;
    depthL = BiTreeDepth(T->lchild);//�ݹ������������
    depthR = BiTreeDepth(T->rchild);//�ݹ������������
    if(depthL > depthR)
        return (depthL + 1);
    else
        return (depthR + 1);
}

// ����6 ���ҽ��
// ��ʼ�����Ƕ�����T�Ѵ��ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
// ��������Ƿ��ز��ҵ��Ľ��ָ�룬���޹ؼ���Ϊe�Ľ�㣬����NULL��
BiTNode* LocateNode(BiTree T,KeyType e)
{
    BiTNode *p = NULL, *q = NULL;//�������������������в��ҵ��Ľ��
    if(T == NULL)
        return NULL;
    if(T->data.key == e)
        return T;
    p = LocateNode(T->lchild, e);//�ݹ����������
    q = LocateNode(T->rchild, e);//�ݹ����������
    if(p != NULL)//����������������
        return p;
    if(q != NULL)//����������������
        return q;
    return NULL;
}

// ����7 ��㸳ֵ
// ��ʼ�����Ƕ�����T�Ѵ��ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
// ��������ǹؼ���Ϊe�Ľ�㸳ֵΪvalue��
status Assign(BiTree &T,KeyType e,TElemType value)
{
    if(T == NULL)
        return OK;
    if(T->data.key == value.key && T->data.key != e)//�ؼ��ʳ�ͻ
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
    Assign(T->lchild, e, value);//�ݹ����������
    Assign(T->rchild, e, value);//�ݹ����������
    if(pt != NULL)
    {
        pt->data.key = value.key;
        strcpy(pt->data.others, value.others);
        return OK;
    }
    else
        return ERROR;
}

// ����8 ��ȡ�ֵ�
// ��ʼ�����Ƕ�����T���ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
// ��������Ƿ��عؼ���Ϊe�Ľ��ģ�����ң��ֵܽ��ָ�롣���ؼ���Ϊe�Ľ�����ֵܣ��򷵻�NULL��
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

// ����9 ������
// ��ʼ�����Ƕ�����T���ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��LRΪ0��1��c�Ǵ������㡣
// ��������Ǹ���LRΪ0����1��������c��T�У���Ϊ�ؼ���Ϊe�Ľ�������Һ��ӽ�㣬���e��ԭ������������������Ϊ���c����������
// LRΪ-1ʱ����Ϊ�������룬ԭ�������Ϊc����������
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
{
    static BiTNode *p = NULL;
    if(LR == -1)//��Ϊ��������
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
        if(!LR)//��Ϊ����������
        {
            p->rchild = T->lchild;
            T->lchild = p;
            p->lchild = NULL;
        }
        else//��Ϊ����������
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

// ����10 ɾ�����
// ��ʼ�����Ƕ�����T���ڣ�e�Ǻ�T�н��ؼ���������ͬ�ĸ���ֵ��
// ���������ɾ��T�йؼ���Ϊe�Ľ�㣻ͬʱ������ؼ���Ϊe�Ľ���Ϊ0��ɾ�����ɡ�
// ��ؼ���Ϊe�Ľ���Ϊ1���ùؼ���Ϊe�Ľ�㺢�Ӵ��汻ɾ����eλ�á�
// ��ؼ���Ϊe�Ľ���Ϊ2����e�����Ӵ��汻ɾ����eλ�ã�e����������Ϊe�������������ҽ�����������
status DeleteNode(BiTree &T,KeyType e)
{
    if(T == NULL)
        return OK;
    if(T->data.key == e)
    {
        flag1 = 1;
        if(T->lchild == NULL && T->rchild == NULL)//��Ϊ0��ֱ��ɾ��
        {
            free(T);
            T = NULL;
            return OK;
        }
        else if(T->lchild != NULL && T->rchild == NULL)//��Ϊ1���ú��Ӵ���e
        {
            BiTNode *p = T->lchild;
            free(T);
            T = p;
            return OK;
        }
        else if(T->lchild == NULL && T->rchild != NULL)//��Ϊ1���ú��Ӵ���e
        {
            BiTNode *p = T->rchild;
            free(T);
            T = p;
            return OK;
        }
        else//��Ϊ2�������Ӵ���e����������Ϊ�����������ҽ���������
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

// ����11 ǰ�����
// ��ʼ�����Ƕ�����T���ڣ�Visit��һ������ָ����βΣ���ʹ�øú����Խ���������
// ��������������������ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
status PreOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T)
    {
        visit(T);//���ʵ�ǰ���
        PreOrderTraverse(T->lchild, visit);//�ݹ����������
        PreOrderTraverse(T->rchild, visit);//�ݹ����������
    }
        return OK;
}

// ����12 �������
// ��ʼ�����Ƕ�����T���ڣ�Visit��һ������ָ����βΣ���ʹ�øú����Խ���������
// ����������������t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
status InOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T)
    {
        InOrderTraverse(T->lchild, visit);//�ݹ����������
        visit(T);//���ʵ�ǰ���
        InOrderTraverse(T->rchild, visit);//�ݹ����������
        return OK;
    }
    else
        return OK;
}

// ����13 �������
// ��ʼ�����Ƕ�����T���ڣ�Visit��һ������ָ����βΣ���ʹ�øú����Խ���������
// ��������Ǻ������t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ��
status PostOrderTraverse(BiTree T,void (*visit)(BiTree))
{
    if(T)
    {
        PostOrderTraverse(T->lchild, visit);//�ݹ����������
        PostOrderTraverse(T->rchild, visit);//�ݹ����������
        visit(T);//���ʵ�ǰ���
        return OK;
    }
    else
        return OK;
}

// ����14 �������
// ��ʼ�����Ƕ�����T���ڣ�Visit�ǶԽ�������Ӧ�ú�����
// ��������ǲ������t����ÿ�������ú���Visitһ����һ�Σ�һ������ʧ�ܣ������ʧ�ܡ�
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
            enQueue(qu, p->lchild);//���ӽ���
        if(p->rchild != NULL)
            enQueue(qu, p->rchild);//�Һ��ӽ���
    }
    return OK;
}

// ���ӹ���15 �����·����
// ��ʼ�����Ƕ�����T���ڣ���������Ƿ��ظ��ڵ㵽Ҷ�ӽ������·���͡�
int MaxPathSum(BiTree T)
{
    if(T == NULL)
        return 0;
    else
        return max(T->data.key + MaxPathSum(T->lchild), T->data.key + MaxPathSum(T->rchild));
}

// ���ӹ���16 �������������
// ��ʼ�����Ƕ�����T���ڣ���������Ǹö�������e1�ڵ��e2�ڵ������������ȡ�
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

// ���ӹ���17 ��ת������
// ��ʼ���������Ա�L�Ѵ��ڣ���������ǽ�T��ת��ʹ�����нڵ�����ҽڵ㻥����
status InvertTree(BiTree &T)
{
    if(T == NULL)
        return OK;
    InvertTree(T->lchild);//�ݹ鷭ת������
    InvertTree(T->rchild);//�ݹ鷭ת������
    BiTree tmp = NULL;//�������ҽ��ʱ����ʱ�洢���
    tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    return OK;
}

// ���ӹ���18 д���ļ�
// ���������T���ڣ���������T�ĵ�Ԫ��д��FileName�ļ��У�����OK��
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

// ���ӹ���19 ��ȡ�ļ�
// ���������T�����ڣ���FileName�ļ��е����ݶ��뵽������T�У�����OK��
status LoadBiTree(BiTree &T,  char FileName[])
{
    static FILE *fp2 = fopen(FileName, "r");
    int t = 0;  //�洢�ؼ���
    char s[20]; //�洢����
    memset(s, 0, 20);
    if(feof(fp2))
        return OK;
    fscanf(fp2, "%d%s", &t, s);
    if(t == 0)
        T = NULL;
    else
    {
        T = (BiTNode *)malloc(sizeof(BiTNode));//��������
        T->data.key = t;
        strcpy(T->data.others, s);
        LoadBiTree(T->lchild, FileName);//�ݹ齨��������
        LoadBiTree(T->rchild, FileName);//�ݹ齨��������
    }
    if(feof(fp2))
        fclose(fp2);
    return OK;
}

// ���ӹ���20 ����������������¶�����
// ��Lists������һ������ΪTreeName�Ķ�������
status AddTree(LISTS &Lists,char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if (!strcmp(Lists.elem[i].name, ListName))
        {
            printf("�������Ѵ�������Ϊ %s �Ķ�������\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);
    TElemType defi[100];
    memset(defi, 0, 100 * sizeof(TElemType));
    int j = 0, flag3 = 0;
    printf("������ǰ��������У�");
    do
    {
        scanf("%d %s", &defi[j].key, defi[j].others);
    } while (defi[j++].key != -1);
    flag3 = CreateBiTree(Lists.elem[Lists.length].T, defi);
    if(flag3 == OK)
    {
        printf("����Ϊ %s �Ķ����������ɹ���\n", Lists.elem[Lists.length].name);
        Lists.length++;
    }
    else if(flag3 == ERROR)
        printf("�ؼ��ʲ�Ψһ������������ʧ�ܣ�\n");
    return OK;
}

// ���ӹ���21 �����������:ɾ��������
// ��Lists��ɾ��һ������ΪTreeName�Ķ�������
status RemoveTree(LISTS &Lists,char ListName[])
{
    int i;
    for(i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //ƥ�����
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

// ���ӹ���22 �����������:���Ҷ�����
// ��Lists�в���һ������ΪTreeName�Ķ��������ɹ������߼���ţ����򷵻�0
int LocateTree(LISTS Lists, char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //ƥ�����
            return (i + 1);
    return ERROR;
}

// ���ӹ���23 �����������:�����������
// ��Lists��ɾ��һ������ΪTreeName�Ķ�������
status ListsTraverse(LISTS Lists)
{
    if (Lists.length == 0)
        return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("����Ϊ %s ��Ԫ���У�", Lists.elem[n].name);
        PreOrderTraverse(Lists.elem[n].T, visit);
        putchar('\n');
    }
    return OK;
}

// ���ӹ���24 �����������:ѡ��һ������������������ţ������ɶ�����в���
BiTree *ChooseTree(BiTree *T, LISTS &Lists, int i) 
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        T = &(Lists.elem[i - 1].T);  //���ݵ�ַ��ͬʱ�Ķ�����������еĴ���    
        return T;
    }
}