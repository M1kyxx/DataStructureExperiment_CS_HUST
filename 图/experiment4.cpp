/* Undirected Graph On Adjacency List */
/* 头文件 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* status */
#define TRUE 1       //判定结果为正确
#define FALSE 0      //判定结果为错误
#define OK 1         //功能运行正常
#define ERROR 0      //功能出现错误无法运行
#define INFEASIBLE -1//操作对象不存在
#define OVERFLOW -2  //内存溢出

#define MAX_VERTEX_NUM 20

typedef int status;
typedef int KeyType; 
typedef enum {DG, DN, UDG, UDN} GraphKind; //图类型:有向图,有向网,无向图,无向网

/* 顶点类型 */
typedef struct {
    KeyType key;        //关键字
    char others[20];    //内容
} VertexType;

/* 表结点类型 */
typedef struct ArcNode {
    int adjvex;                //顶点位置编号 
    struct ArcNode *nextarc;   //下一个表结点指针
} ArcNode;

/* 头结点及其数组类型 */
typedef struct VNode {
    VertexType data;    //顶点信息
    ArcNode *firstarc;  //指向第一条弧
} VNode, AdjList[MAX_VERTEX_NUM];

/* 邻接表类型 */
typedef  struct {
    AdjList vertices;    //头结点数组
    int vexnum, arcnum;  //顶点数、弧数
    GraphKind kind;      //图的类型
} ALGraph;

/* 图的管理表 */
typedef struct{
    struct{ 
        char name[30];  //图名称
     	ALGraph G;
    }elem[10];
    int length;         //管理表长度（图数目）
    int listsize;       //管理表容量
}LISTS;

/* 循环队列元素类型 */
typedef int ElemType;

/* 循环队列容量 */
#define MAXLENGTH 100

/* 循环队列结构 */
typedef struct QUEUE {
    ElemType elem[MAXLENGTH];   //循环队列元素
    int front, length;          //循环队列定位用变量
} QUEUE;


int visited[MAX_VERTEX_NUM];    //遍历时记录顶点是否已访问
int PathLength[MAX_VERTEX_NUM]; //记录所有顶点到某一顶点的最短路径长度
VNode vn[MAX_VERTEX_NUM];       //存储顶点集合过程量

/* 零件函数 */
void visit(VertexType v);
void DFS(ALGraph G, int v, void (*visit)(VertexType));

/* 队列操作函数 */
void iniQueue(QUEUE &Q);
status enQueue(QUEUE &Q, ElemType e);
status deQueue(QUEUE &Q, ElemType &e);

/* 单图基础操作函数 */
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2]);
status DestroyGraph(ALGraph &G);
int LocateVex(ALGraph G, KeyType u);
status PutVex(ALGraph &G, KeyType u, VertexType value);
int FirstAdjVex(ALGraph G, KeyType u);
int NextAdjVex(ALGraph G, KeyType v, KeyType w);
status InsertVex(ALGraph &G, VertexType v);
status DeleteVex(ALGraph &G, KeyType v);
status InsertArc(ALGraph &G, KeyType v, KeyType w);
status DeleteArc(ALGraph &G, KeyType v, KeyType w);
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));

/*选做操作函数*/
VNode* VerticesSetLessThanK(ALGraph G, KeyType v, int k);
int ShortestPathLength(ALGraph G, KeyType v, KeyType w);
int ConnectedComponentsNums(ALGraph G);

/*文件读写函数*/
status SaveGraph(ALGraph G, char FileName[]);
status LoadGraph(ALGraph &G, char FileName[]);

/*多图操作函数*/
status AddGragh(LISTS &Lists, char ListName[]);
status RemoveGragh(LISTS &Lists, char ListName[]);
int LocateGragh(LISTS Lists, char ListName[]);
status ListsTraverse(LISTS Lists);
ALGraph* ChooseGragh(ALGraph *L, LISTS &Lists, int i);















/*---------------------main函数-----------------------*/
int main(void)
{
    //定义单图并初始化
    ALGraph G1;
    ALGraph *G = &G1;
    G->arcnum = 0;
    G->vexnum = 0;
    memset(G->vertices, 0, MAX_VERTEX_NUM * sizeof(VNode));

    //定义管理表并初始化
    LISTS Lists;
    Lists.length = 0, Lists.listsize = 10;

    //op记录功能选择情况,flag记录功能运行情况,i与k存储int型过程量,u与v存储关键字过程量
	int op = 1, flag = 0, i = 0, k = 0, u = 0, v = 0;
    char FileName[30], ListName[30]; //储存文件名与表名
    VertexType value;   //存储顶点过程量
    VertexType V[30];   //存储顶点序列
    KeyType VR[100][2]; //存储关系对序列
    VNode *VN = NULL;   //存储顶点集合过程量
    
	while(op)
	{
		system("cls");
		printf("\n\n");
		printf("      Menu for Undirected Graph On Adjacency List   \n");
		printf("------------------------------------------------------\n");
		printf("    	  1. 创建            12. 广搜遍历\n");
		printf("    	  2. 销毁            13. 求距离小于k的顶点集合\n");
		printf("    	  3. 查找顶点        14. 求顶点间最短路径长度\n");
		printf("    	  4. 顶点赋值        15. 求连通分量个数\n");
		printf("    	  5. 获得第一邻接点  16. 写入文件\n");
		printf("    	  6. 获得下一邻接点  17. 读取文件\n");
        printf("    	  7. 插入顶点        18. 增加图\n");
        printf("    	  8. 删除顶点        19. 删除图\n");
        printf("    	  9. 插入弧          20. 查找图\n");
        printf("    	 10. 删除弧          21. 遍历总表\n");
        printf("    	 11. 深搜遍历        22. 选择单图进行操作\n");
		printf("    	  0. 退出\n");
		printf("------------------------------------------------------\n");
        printf("    请确保多按几次回车键至窗口刷新后再选择操作\n");
		printf("    请选择你的操作[0~22]:");
		scanf("%d", &op);
		switch(op)
		{
			case 1://创建
                if(G->vexnum)
                    printf("创建失败!图已存在!\n");
                else
                {
                    i = 0;
                    printf("顶点格式示例: 1 线性表; 3 二叉树\n");
                    printf("以-1 nil作为结束标记\n");
                    printf("空图不予创建\n");
                    printf("请据此输入将建图中的顶点序列:");
                    do {
                        scanf("%d%s", &V[i].key, V[i].others);
                    } while(V[i++].key != -1);
                    i = 0;
                    printf("关系对格式示例: 1 3\n");
                    printf("以-1 -1作为结束标记\n");
                    printf("请据此输入将建图中的关系对序列:");
                    do {
                        scanf("%d%d", &VR[i][0], &VR[i][1]);
                    } while(VR[i++][0] != -1);
                    flag = CreateCraph(*G, V, VR);
                    if(flag == OK)
                        printf("无向图创建成功!\n这是一个与独立于多图的单图,你可以对它进行1~17操作!\n");
                    else
                        printf("创建失败!顶点序列或关系对序列输入有误!\n");
                }
                getchar();getchar();
				break;
			case 2://销毁
                flag = DestroyGraph(*G);
                if(flag == OK)
                    printf("成功销毁无向图并释放数据元素的空间!\n");
                else if(flag == INFEASIBLE)
                    printf("不能对不存在的无向图进行销毁操作!\n");
                getchar();getchar();
				break;
			case 3://查找顶点
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行查找操作!\n");
                else
                {
                    printf("请输入想要查找的关键字:");
                    scanf("%d", &u);
                    flag = LocateVex(*G, u);
                    if(flag == -1)
                        printf("含关键字 %d 的顶点不存在!\n", u);
                    else
                        printf("含关键字 %d 的顶点位序为 %d!", u, flag);
                }
                getchar();getchar();
				break;
			case 4://顶点赋值
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行赋值操作!\n");
                else
                {
                    printf("请输入想要赋值的顶点的关键字用于查找:");
                    scanf("%d", &u);
                    printf("请输入将赋的关键字与内容:");
                    scanf("%d%s", &value.key, value.others);
                    flag = PutVex(*G, u, value);
                    if(flag == OK)
                        printf("赋值成功!\n");
                    else
                        printf("赋值失败!关键字不存在或将赋关键字不唯一!\n");
                }
                getchar();getchar();
				break;
			case 5://获得第一邻接点
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请输入想要求第一邻接点的顶点的关键字:");
                    scanf("%d", &u);
                    flag = FirstAdjVex(*G, u);
                    if(flag == -1)
                        printf("操作失败!关键字不存在或该顶点不存在邻接点!\n");
                    else
                        printf("关键字为 %d 的顶点的第一邻接点是位序为 %d 的 %d %s!\n", u, flag, G->vertices[flag].data.key, G->vertices[flag].data.others);
                }
                getchar();getchar();
				break;
			case 6://获得下一邻接点
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请输入一个顶点和它的一个邻接点的关键字:");
                    scanf("%d%d", &u, &v);
                    flag = NextAdjVex(*G, u, v);
                    if(flag == -1)
                        printf("操作失败!关键字不存在或该邻接点已是最后一个!\n");
                    else
                        printf("顶点 %d 的邻接点 %d 的下一邻接点是位序为 %d 的 %d %s!\n", u, v, flag, G->vertices[flag].data.key, G->vertices[flag].data.others);
                }
                getchar();getchar();
				break;
			case 7://插入顶点
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请输入将插入的关键字与内容:");
                    scanf("%d%s", &value.key, value.others);
                    flag = InsertVex(*G, value);
                    if(flag == OK)
                        printf("插入成功!\n");
                    else
                        printf("插入失败!顶点数目已达最大值或关键字已存在!\n");
                }
                getchar();getchar();
				break;
			case 8://删除顶点
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请输入将删除的结点的关键字:");
                    scanf("%d", &u);
                    flag = DeleteVex(*G, u);
                    if(flag == OK)
                        printf("删除成功!与该顶点相关的弧已删除!\n");
                    else
                        printf("删除失败!关键字不存在或顶点数目为1!\n");
                }
                getchar();getchar();
				break;
			case 9://插入弧
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请分别输入将插入的弧的两个顶点的关键字:");
                    scanf("%d%d", &u, &v);
                    flag = InsertArc(*G, u, v);
                    if(flag == OK)
                        printf("插入成功!\n");
                    else
                        printf("插入失败!关键字不存在或弧已存在!\n");
                }
                getchar();getchar();
				break;
			case 10://删除弧
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请分别输入将删除的弧的两个顶点的关键字:");
                    scanf("%d%d", &u, &v);
                    flag = DeleteArc(*G, u, v);
                    if(flag == OK)
                        printf("删除成功!\n");
                    else
                        printf("删除失败!关键字不存在或弧不存在!\n");
                }
                getchar();getchar();
				break;
			case 11://深搜遍历
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行遍历操作!\n");
                else
                    DFSTraverse(*G, visit);
				getchar();getchar();
				break;
			case 12://广搜遍历
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行遍历操作!\n");
                else
                    BFSTraverse(*G, visit);
				getchar();getchar();
                break;
            case 13://求距离小于k的顶点集合
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请输入一个顶点的关键字:");
                    scanf("%d", &u);
                    printf("请输入距离k:");
                    scanf("%d", &k);
                    VN = VerticesSetLessThanK(*G, u, k);
                    if(VN == NULL)
                        printf("操作失败!关键字输入有误!\n");
                    else
                    {
                        if(VN[0].data.key == 0)
                            printf("集合为空!");
                        else
                        {
                            printf("与关键字为 %d 的顶点距离小于 %d 的顶点集合为:", u, k);
                            for(i = 0; VN[i].data.key != 0; i++)
                                printf("%d %s ", VN[i].data.key, VN[i].data.others);
                        }
                    }
                }
                getchar();getchar();
                break;
            case 14://求顶点间最短路径长度
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请输入两个顶点的关键字:");
                    scanf("%d%d", &u, &v);
                    flag = ShortestPathLength(*G, u, v);
                    if(flag == -1)
                        printf("操作失败!关键字不存在或两顶点间不存在路径!\n");
                    else
                        printf("关键字为 %d 和 %d 的顶点间最短路径长度为 %d!\n", u, v, flag);
                }
                getchar();getchar();
                break;
            case 15://求连通分量个数
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    flag = ConnectedComponentsNums(*G);
                    printf("\n该图的连通分量个数为 %d!\n", flag);
                }
                getchar();getchar();
                break;
            case 16://写入文件
                if(!G->vexnum)
                    printf("不能对不存在的无向图进行该操作!\n");
                else
                {
                    printf("请输入文件名称:");
                    scanf("%s", FileName);
                    flag = SaveGraph(*G, FileName);
                    if(flag == ERROR)
                        printf("文件打开失败!\n");
                    else
                        printf("无向图的内容已经复制到名称为 %s 的文件中!\n", FileName);
                }
				getchar();getchar();
				break;
            case 17://读取文件
                if(G->vexnum)
                    printf("不能对已存在的无向图进行读文件操作!请先销毁无向图!\n");
                else
                {
                    printf("请输入文件名称:");
                    scanf("%s", FileName);
                    flag = LoadGraph(*G, FileName);
                    if(flag == ERROR)
                        printf("文件打开失败!\n");
                    else
                        printf("名称为 %s 的文件中内容已复制到无向图中!\n", FileName);
                }
				getchar();getchar();
				break;
            case 18://增加图
                printf("请输入新增无向图的名称:");
                scanf("%s", ListName);
                flag = AddGragh(Lists, ListName);
                if(flag == OK)
                    printf("成功新增名称为 %s 的无向图!\n", ListName);
                else
                    printf("新增失败!\n");
				getchar();getchar();
				break;
            case 19://删除图
                if(Lists.length)
                {
                    printf("\n--------------- all graphs --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("无向图的集合为空!无法进行此操作!\n");
                    getchar();getchar();
                    break;
                }
                printf("请输入想要删除的无向图的名称:");
                scanf("%s", ListName);
                flag = RemoveGragh(Lists, ListName);
                if(flag == OK)
                    printf("成功删除名称为 %s 的无向图!\n", ListName);
                else
                    printf("删除失败!\n");
                getchar();getchar();
				break;
            case 20://查找图
                if(!Lists.length)
                {
                    printf("无向图的集合为空!无法进行此操作!\n");
                    getchar();getchar();
                    break;
                }
                printf("请输入想要查找的无向图的名称:");
                scanf("%s", ListName);
                flag = LocateGragh(Lists, ListName);
                if(!flag)
                    printf("不存在名称为 %s 的无向图!\n", ListName);
                else
                    printf("名称为 %s 的无向图的序号为 %d!\n", ListName, flag);
                getchar();getchar();
				break;
            case 21://遍历总表
                if(ListsTraverse(Lists) == ERROR)
                    printf("无向图的集合为空!\n");
                getchar();getchar();
                break;
            case 22://选择单图进行操作
                if(Lists.length)
                {
                    printf("\n--------------- all grapghs --------------------\n");
                    for(int i = 0; i < Lists.length; i++)
                        printf("%d %s\n", i + 1, Lists.elem[i].name);
                    printf("------------------ end ------------------------\n");
                }
                else
                {
                    printf("无向图的集合为空!无法进行此操作!\n");
                    getchar();getchar();
                    break;
                }
                printf("请输入想要操作的无向图的序号(从1开始):");
                scanf("%d", &flag);
                G = ChooseGragh(G, Lists, flag);
                if(G == NULL)
                    printf("输入序号不合法!单图已置空!\n");
                else
                    printf("下面可对无向图集合中序号为 %d 的无向图进行操作!\n", flag);
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










// 访问函数
void visit(VertexType v)
{
    printf(" %d %s", v.key, v.others);
}

// 深搜实现函数
void DFS(ALGraph G, int v, void (*visit)(VertexType))
{
    int w = -1;
    visited[v] = 1;
    visit(G.vertices[v].data);
    for(w = FirstAdjVex(G, G.vertices[v].data.key); w >= 0; w = NextAdjVex(G, G.vertices[v].data.key, G.vertices[w].data.key))
        if(!visited[w])
            DFS(G, w, visit);
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
// 根据V和VR构造图T并返回OK,如果V和VR不正确,返回ERROR,如果有相同的关键字,返回ERROR
status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
    if(V[0].key == -1)
        return ERROR;
    int a, i, j, flag1 = 0, flag2 = 0;
    KeyType keys[30];
    for(a = 0; a < 20; a++)
        keys[a] = 0;
    a = 0;
    for(i = 0; V[i].key != -1; i++)
    {
        if(i >= MAX_VERTEX_NUM)
            return ERROR;
        keys[a++] = V[i].key;
        for(j = i + 1; V[j].key != -1; j++)
            if(V[i].key == V[j].key)
                return ERROR;
    }
    for(i = 0; VR[i][0] != -1; i++)
    {
        flag1 = 0, flag2 = 0;
        for(a = 0; keys[a] != 0; a++)
        {
            if(VR[i][0] == keys[a])
                flag1 = 1;
            if(VR[i][1] == keys[a])
                flag2 = 1;
        }
        if(!flag1 || !flag2)
            return ERROR;
    }
    G.kind = UDG;
    G.vexnum = 0;
    G.arcnum = 0;
    for(i = 0; V[i].key != -1 && i < MAX_VERTEX_NUM; i++)
    {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
        G.vexnum++;
    }
    for(i = 0; VR[i][0] != -1; i++)
    {
        flag1 = 0, flag2 = 0;
        for(a = 0; keys[a] != 0; a++)
        {
            if(VR[i][0] == keys[a])
                flag1 = a;
            if(VR[i][1] == keys[a])
                flag2 = a;
        }
        ArcNode *a1 = (ArcNode *)malloc(sizeof(ArcNode));
        a1->adjvex = flag2;
        a1->nextarc = G.vertices[flag1].firstarc;
        G.vertices[flag1].firstarc = a1;
        ArcNode *a2 = (ArcNode *)malloc(sizeof(ArcNode));
        a2->adjvex = flag1;
        a2->nextarc = G.vertices[flag2].firstarc;
        G.vertices[flag2].firstarc = a2;
        G.arcnum++;
    }
    return OK;
}

// 功能2 销毁
// 销毁无向图G,删除G的全部顶点和边
status DestroyGraph(ALGraph &G)
{
    if(!G.vexnum)
        return INFEASIBLE;
    int i;
    ArcNode *a = NULL, *pre = NULL;
    for(i = 0; i < G.vexnum; i++)
    {
        a = G.vertices[i].firstarc;
        while(a)
        {
            pre = a;
            a = a->nextarc;
            free(pre);
        }
        G.vertices[i].firstarc = NULL;
    }
    memset(G.vertices, 0, G.vexnum);
    G.arcnum = 0;
    G.vexnum = 0;
    return OK;
}


// 功能3 查找顶点
// 根据u在图G中查找顶点,查找成功返回位序,否则返回-1
int LocateVex(ALGraph G, KeyType u)
{
    int i;
    for(i = 0; i < G.vexnum; i++)
        if(u == G.vertices[i].data.key)
            return i;
    return -1;
}

// 功能4 顶点赋值
// 根据u在图G中查找顶点,查找成功将该顶点值修改成value,返回OK
// 如果查找失败或关键字不唯一,返回ERROR
status PutVex(ALGraph &G, KeyType u, VertexType value)
{
    int i, j;
    for(i = 0; i < G.vexnum; i++)
        if(u == G.vertices[i].data.key)
            break;
    if(i == G.vexnum)
        return ERROR;
    for(j = 0; j < G.vexnum; j++)
        if(value.key == G.vertices[j].data.key && value.key != u)
            return ERROR;
    G.vertices[i].data = value;
    return OK;
}

// 功能5 获得第一邻接点
// 根据u在图G中查找顶点,查找成功返回顶点u的第一邻接顶点位序,否则返回-1
int FirstAdjVex(ALGraph G, KeyType u)
{
    int i;
    for(i = 0; i < G.vexnum; i++)
        if(u == G.vertices[i].data.key && G.vertices[i].firstarc != NULL)
            return G.vertices[i].firstarc->adjvex;
    return -1;
}

// 功能6 获得下一邻接点
// v对应G的一个顶点,w对应v的邻接顶点
// 操作结果是返回v的(相对于w)下一个邻接顶点的位序
// 如果w是最后一个邻接顶点,或v,w对应顶点不存在,则返回-1
int NextAdjVex(ALGraph G,KeyType v,KeyType w)
{
    int i, flag1 = -1, flag2 = -1;
    for(i = 0; i < G.vexnum; i++)
    {
        if(v == G.vertices[i].data.key)
            flag1 = i;
        if(w == G.vertices[i].data.key)
            flag2 = i;
    }
    if(flag1 == -1 || flag2 == -1)
        return -1;
    ArcNode *a = G.vertices[flag1].firstarc;
    while(a)
    {
        if(flag2 == a->adjvex && a->nextarc != NULL)
            return a->nextarc->adjvex;
        a = a->nextarc;
    }
    return -1;
}

// 功能7 插入顶点
// 在图G中插入顶点v,成功返回OK,否则返回ERROR
status InsertVex(ALGraph &G,VertexType v)
{
    if(G.vexnum == MAX_VERTEX_NUM)
        return ERROR;
    int i;
    for(i = 0; i < G.vexnum; i++)
        if(v.key == G.vertices[i].data.key)
            return ERROR;
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

// 功能8 删除顶点
// 在图G中删除关键字v对应的顶点以及相关的弧,成功返回OK,否则返回ERROR
status DeleteVex(ALGraph &G,KeyType v)
{
    if(G.vexnum == 1)
        return ERROR;
    int i, j = 0, k;
    for(i = 0; i < G.vexnum; i++)
        if(v == G.vertices[i].data.key)
            break;
    if(i == G.vexnum)
        return ERROR;
    ArcNode *a = G.vertices[i].firstarc, *pre = NULL;
    while(a)
    {
        pre = a;
        a = a->nextarc;
        ArcNode *b = G.vertices[pre->adjvex].firstarc, *preb = NULL;
        if(b->adjvex == i)
        {
            G.vertices[pre->adjvex].firstarc = b->nextarc;
            free(b);
        }
        else
            while(b)
            {
                preb = b;
                b = b->nextarc;
                if(b->adjvex == i)
                {
                    preb->nextarc = b->nextarc;
                    free(b);
                    break;
                }
            }
        free(pre);
        G.arcnum--;
    }
    G.vertices[i].firstarc = NULL;
    ArcNode *c = NULL;
    for(j = 0; j < G.vexnum; j++)
    {
        c = G.vertices[j].firstarc;
        while(c != NULL)
        {
            if(c->adjvex > i)
                c->adjvex--;
            c = c->nextarc;
        }
    }
    for(k = i + 1; k < G.vexnum; i++, k++)
    {
        G.vertices[i].data = G.vertices[k].data;
        G.vertices[i].firstarc = G.vertices[k].firstarc;
    }
    G.vexnum--;
    return OK;
}

// 功能9 插入弧
// 在图G中增加弧<v,w>,成功返回OK,否则返回ERROR
status InsertArc(ALGraph &G,KeyType v,KeyType w)
{
    int i, flag1 = -1, flag2 = -1;
    for(i = 0; i < G.vexnum; i++)
    {
        if(v == G.vertices[i].data.key)
            flag1 = i;
        if(w == G.vertices[i].data.key)
            flag2 = i;
    }
    if(flag1 == -1 || flag2 == -1)
        return ERROR;
    
    ArcNode *a = G.vertices[flag1].firstarc;
    while(a)
    {
        if(a->adjvex == flag2)
            return ERROR;
        a = a->nextarc;
    }

    ArcNode *a1 = (ArcNode *)malloc(sizeof(ArcNode));
    a1->adjvex = flag2;
    a1->nextarc = G.vertices[flag1].firstarc;
    G.vertices[flag1].firstarc = a1;
    ArcNode *a2 = (ArcNode *)malloc(sizeof(ArcNode));
    a2->adjvex = flag1;
    a2->nextarc = G.vertices[flag2].firstarc;
    G.vertices[flag2].firstarc = a2;
    G.arcnum++;
    return OK;
}

// 功能10 删除弧
// 在图G中删除弧<v,w>,成功返回OK,否则返回ERROR
status DeleteArc(ALGraph &G,KeyType v,KeyType w)
{
    int i, flag1 = -1, flag2 = -1, flag = 0;
    for(i = 0; i < G.vexnum; i++)
    {
        if(v == G.vertices[i].data.key)
            flag1 = i;
        if(w == G.vertices[i].data.key)
            flag2 = i;
    }
    if(flag1 == -1 || flag2 == -1)
        return ERROR;
    
    ArcNode *a = G.vertices[flag1].firstarc;
    while(a)
    {
        if(a->adjvex == flag2)
            flag = 1;
        a = a->nextarc;
    }
    if(!flag)
        return ERROR;

    ArcNode *a1 = G.vertices[flag1].firstarc, *pre1 = NULL;
    if(a1->adjvex == flag2)
    {
        G.vertices[flag1].firstarc = a1->nextarc;
        free(a1);
    }
    else
        while(a1)
        {
            pre1 = a1;
            a1 = a1->nextarc;
            if(a1->adjvex == flag2)
            {
                pre1->nextarc = a1->nextarc;
                free(a1);
                break;
            }
        }
    
    ArcNode *a2 = G.vertices[flag2].firstarc, *pre2 = NULL;
    if(a2->adjvex == flag1)
    {
        G.vertices[flag2].firstarc = a2->nextarc;
        free(a2);
    }
    else
        while(a2)
        {
            pre2 = a2;
            a2 = a2->nextarc;
            if(a2->adjvex == flag1)
            {
                pre2->nextarc = a2->nextarc;
                free(a2);
                break;
            }
        }
    G.arcnum--;
    return OK;
}

// 功能11 深搜遍历
// 对图G进行深度优先搜索遍历,依次对图中的每一个顶点使用函数visit访问一次,且仅访问一次
status DFSTraverse(ALGraph &G,void (*visit)(VertexType))
{
    int v;
    for(v = 0; v < G.vexnum; v++)
        visited[v] = 0;
    for(v = 0; v < G.vexnum; v++)
        if(!visited[v])
            DFS(G, v, visit);
    return OK;
}

// 功能12 广搜遍历
// 对图G进行广度优先搜索遍历,依次对图中的每一个顶点使用函数visit访问一次,且仅访问一次
status BFSTraverse(ALGraph &G,void (*visit)(VertexType))
{
    int v, u, w = -1;
    QUEUE Q;
    for(v = 0; v < G.vexnum; v++)
        visited[v] = 0;
    iniQueue(Q);
    for(v = 0; v < G.vexnum; v++)
        if(!visited[v])
        {
            visited[v] = 1;
            visit(G.vertices[v].data);
            enQueue(Q, v);
            while(Q.length)
            {
                deQueue(Q, u);
                for(w = FirstAdjVex(G, G.vertices[u].data.key); w >= 0; w = NextAdjVex(G, G.vertices[u].data.key, G.vertices[w].data.key))
                    if(!visited[w])
                    {
                        visited[w] = 1;
                        visit(G.vertices[w].data);
                        enQueue(Q, w);
                    }
            }
        }
    return OK;
}

// 附加功能13 求距离小于k的顶点集合
// 初始条件是图G存在;操作结果是返回与顶点v距离小于k的顶点集合
VNode* VerticesSetLessThanK(ALGraph G, KeyType v, int k)
{
    int i, j, u, x = -1, len = 0, times = 0;
    int flag1 = -1, flag2 = -1;
    for(i = 0; i < MAX_VERTEX_NUM; i++)
        vn[i].data.key = 0;
    for(i = 0; i < G.vexnum; i++)
        if(v == G.vertices[i].data.key)
            flag1 = i;
    if(flag1 == -1)
        return NULL;
    int length[MAX_VERTEX_NUM];
    for(i = 0; i < MAX_VERTEX_NUM; i++)
        length[i] = 0;
    QUEUE Q;
    for(i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    iniQueue(Q);
    for(i = flag1; times < G.vexnum; i++, times++)
    {
        if(!visited[i])
        {
            visited[i] = 1;
            length[i] = len;
            enQueue(Q, i);
            while(Q.length)
            {
                len++;
                deQueue(Q, u);
                for(x = FirstAdjVex(G, G.vertices[u].data.key); x >= 0; x = NextAdjVex(G, G.vertices[u].data.key, G.vertices[x].data.key))
                {
                    if(!visited[x])
                    {
                        visited[x] = 1;
                        length[x] = len;
                        enQueue(Q, x);
                    }
                }
            }
        }
        if(i + 1 == G.vexnum)
            i = -1;
        break;
    }
    for(i = 0, j = 0; i < G.vexnum; i++)
        if(length[i] > 0 && length[i] < k)
            vn[j++] = G.vertices[i];
    return vn;
}

// 附加功能14 求顶点间最短路径长度
// 初始条件是图G存在;操作结果是返回顶点v与顶点w的最短路径的长度
int ShortestPathLength(ALGraph G, KeyType v, KeyType w)
{
    int i, u, x = -1, len = 0, times = 0;
    int flag1 = -1, flag2 = -1;
    for(i = 0; i < G.vexnum; i++)
    {
        if(v == G.vertices[i].data.key)
            flag1 = i;
        if(w == G.vertices[i].data.key)
            flag2 = i;
    }
    if(flag1 == -1 || flag2 == -1)
        return -1;
    int length[MAX_VERTEX_NUM];
    for(i = 0; i < MAX_VERTEX_NUM; i++)
        length[i] = -1;
    QUEUE Q;
    for(i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    iniQueue(Q);
    for(i = flag1; times < G.vexnum; i++, times++)
    {
        if(!visited[i])
        {
            visited[i] = 1;
            length[i] = len;
            enQueue(Q, i);
            while(Q.length)
            {
                len++;
                deQueue(Q, u);
                for(x = FirstAdjVex(G, G.vertices[u].data.key); x >= 0; x = NextAdjVex(G, G.vertices[u].data.key, G.vertices[x].data.key))
                {
                    if(!visited[x])
                    {
                        visited[x] = 1;
                        length[x] = len;
                        enQueue(Q, x);
                    }
                }
            }
        }
        if(i + 1 == G.vexnum)
            i = -1;
        break;
    }
    return length[flag2];
}

// 附加功能15 求图连通分量个数
// 初始条件是图G存在;操作结果是返回图G的所有连通分量的个数
int ConnectedComponentsNums(ALGraph G)
{
    int i, nums = 0;
    for(i = 0; i < G.vexnum; i++)
        visited[i] = 0;
    for(i = 0; i < G.vexnum; i++)
        if(!visited[i])
        {
            nums++;
            DFS(G, i, visit);
        }
    return nums;
}

// 附加功能16 写入文件
// 将图的数据写入到文件FileName中
status SaveGraph(ALGraph G, char FileName[])
{
    FILE *fp = fopen(FileName, "w");
    
    for(int i = 0; i < G.vexnum; i++)
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    fprintf(fp, "%d %s ", -1, "nil");
    int a1[30], a2[30];
    for(int i = 0; i < 30; i++)
        a1[i] = 0, a2[i] = 0;
    for(int i = 0; i < G.vexnum; i++)
    {
        KeyType k1 = G.vertices[i].data.key, k2 = -1;
        ArcNode *a = G.vertices[i].firstarc;
        int j = 0, flag = 0;
        while(a)
        {
            flag = 0;
            k2 = G.vertices[a->adjvex].data.key;
            a = a->nextarc;
            for(j = 0; a1[j] != 0; j++)
                if(k1 == a2[j] && k2 == a1[j])
                    flag = 1;
            if(flag)
                continue;
            else
            {
                a1[j] = k1;
                a2[j] = k2;
            }
        }
    }
    for(int i = 0; a1[i] != 0; i++)
        if(a2[i] < a1[i])
        {
            int tmp = a2[i];
            a2[i] = a1[i];
            a1[i] = tmp;
        }
    for(int i = 0; a1[i] != 0; i++)
    {
        for(int j = i + 1; a1[j] != 0; j++)
        {
            if((a1[i] > a1[j]) || (a1[i] == a1[j] && a2[i] > a2[j]))
            {
                int tmp1 = a1[i];
                a1[i] = a1[j];
                a1[j] = tmp1;
                int tmp2 = a2[i];
                a2[i] = a2[j];
                a2[j] = tmp2;
            }
        }
    }
    for(int i = 0; a1[i] != 0; i++)
        fprintf(fp, "%d %d ", a1[i], a2[i]);
    fprintf(fp, "%d %d ", -1, -1);
    fclose(fp);
    return OK;
}

// 功能17 读取文件
// 读入文件FileName的图数据，创建图的邻接表
status LoadGraph(ALGraph &G, char FileName[])
{
    FILE *fp = fopen(FileName, "r");
    G.kind = UDG;
    G.vexnum = 0;
    G.arcnum = 0;
    VertexType V[21];
    KeyType VR[100][2], keys[30];
    for(int k = 0; k < 30; k++)
        keys[k] = 0;
    int i = 0, flag1 = -1, flag2 = -1;
    do{
        fscanf(fp, "%d %s ", &V[i].key, V[i].others);
        keys[i] = V[i].key;
    }while(V[i++].key != -1);
    i = 0;
    do{
        fscanf(fp, "%d %d ", &VR[i][0], &VR[i][1]);
    }while(VR[i++][0] != -1);

    for(i = 0; V[i].key != -1 && i < MAX_VERTEX_NUM; i++)
    {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
        G.vexnum++;
    }
    for(i = 0; VR[i][0] != -1; i++)
    {
        flag1 = 0, flag2 = 0;
        for(int a = 0; keys[a] != 0; a++)
        {
            if(VR[i][0] == keys[a])
                flag1 = a;
            if(VR[i][1] == keys[a])
                flag2 = a;
        }
        ArcNode *a1 = (ArcNode *)malloc(sizeof(ArcNode));
        a1->adjvex = flag2;
        a1->nextarc = G.vertices[flag1].firstarc;
        G.vertices[flag1].firstarc = a1;
        ArcNode *a2 = (ArcNode *)malloc(sizeof(ArcNode));
        a2->adjvex = flag1;
        a2->nextarc = G.vertices[flag2].firstarc;
        G.vertices[flag2].firstarc = a2;
        G.arcnum++;
        G.arcnum++;
    }
    fclose(fp);
    return OK;
}

// 附加功能18 多无向图管理:增加新图
// 在Lists中增加一个名称为GraphName的无向图
status AddGragh(LISTS &Lists, char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))
        {
            printf("集合中已存在名称为 %s 的无向图!\n", ListName);
            return ERROR;
        }
    strcpy(Lists.elem[Lists.length].name, ListName);
    VertexType V1[30];
    KeyType VR1[100][2];
    int m = 0, flag1 = 0;
    printf("顶点格式示例: 1 线性表; 3 二叉树\n");
    printf("以-1 nil作为结束标记\n");
    printf("空图不予创建\n");
    printf("请据此输入将建图中的顶点序列:");
    do {
        scanf("%d%s", &V1[m].key, V1[m].others);
    } while(V1[m++].key != -1);
    m = 0;
    printf("关系对格式示例: 1 3\n");
    printf("以-1 -1作为结束标记\n");
    printf("请据此输入将建图中的关系对序列:");
    do {
        scanf("%d%d", &VR1[m][0], &VR1[m][1]);
    } while(VR1[m++][0] != -1);
    flag1 = CreateCraph(Lists.elem[Lists.length].G, V1, VR1);
    if(flag1 == OK)
        printf("名称为 %s 的无向图创建成功!\n", Lists.elem[Lists.length++].name);
    else
        printf("创建失败!顶点序列或关系对序列输入有误!\n");
    return OK;
}

// 附加功能19 多无向图管理:删除图
status RemoveGragh(LISTS &Lists, char ListName[])
{
    int i;
    for(i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //匹配表名
            break;
    if(i == Lists.length)
        return ERROR;
    else
    {
        DestroyGraph(Lists.elem[i].G);
        memset(Lists.elem[i].name, 0, strlen(Lists.elem[i].name));
        Lists.length--;
        for(int j = i; j < Lists.length; j++)
            Lists.elem[j] = Lists.elem[j + 1];
        return OK;
    }
}

// 附加功能20 多无向图管理:查找图
int LocateGragh(LISTS Lists, char ListName[])
{
    for(int i = 0; i < Lists.length; i++)
        if(!strcmp(Lists.elem[i].name, ListName))  //匹配表名
            return (i + 1);
    return ERROR;
}

// 附加功能21 多无向图管理:遍历总表
status ListsTraverse(LISTS Lists)
{
    if (Lists.length == 0)
        return ERROR;
    for (int n = 0; n < Lists.length; n++)
    {
        printf("表名为 %s 的无向图的邻接表按深搜遍历得:\n", Lists.elem[n].name);
        DFSTraverse(Lists.elem[n].G, visit);
        printf("\n---------------------------------------\n");
    }
    return OK;
}

// 附加功能22 多无向图管理:选择单图进行操作
ALGraph* ChooseGragh(ALGraph *G, LISTS &Lists, int i)
{
    if (i > Lists.length || i < 1)
        return NULL;
    else
    {
        G = &(Lists.elem[i - 1].G);  //传递地址以同时改动单图与多图中的此图    
        return G;
    }
}