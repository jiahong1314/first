#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 10000
#define Max 20
typedef struct          //存放景点信息的结构体
   {
     int num;              //景点代号
     char name[20];        //景点名称
     char info[200];       //景点简介
   }VertexType;
   typedef struct               //校园景点图结构体
   {
      VertexType vex[Max];      //顶点信息域
      int edge[Max][Max];       //邻接矩阵存储图
      int vexNum,edgeNum;       //图中顶点数和边数
   }GraphType;
/*int menu();                                //主菜单
void Create_Map(mgraphtype *g);            //从文件读取信息建立图
void Print_Map();                          //显示校园景点地图
int Judge_Input(int num);                   //判断输入的编号是否合理
void Search_Location(mgraphtype *g);       //景点信息查询
void ShortPath(mgraphtype *g);             //求景点间最短路径
void Floyd_Print(mgraphtype *g, int sNum, int eNum);//递归打印两点间最短路径
void Shortpath_Print(mgraphtype *g);    //输出并打印两点间的最短路径
void Dfs_Print(mgraphtype *g, int sNum, int eNum);//深度优先遍历查询两景点间所有路径
void Allpath_Print(mgraphtype *g);    //查询两顶点间的所有路径并打印
void BestPath(mgraphtype *g);        //多顶点间求最佳路径
void System_Exit(int *q);            //退出系统
*/
int menu();   //主菜单
void Create_Map(GraphType *g);//读取信息建立图
void PrintMap();//显示校园景点信息
int JudgeInput(int num);//判断输入编号是否合理
void SearchLocation(GraphType *g);//景点信息查询
void ShortPath(GraphType *g);//求最短路径
void Floyd_print(GraphType *g,int sNum,int eNum);//递归打印最短路径
void ShortPath_print(GraphType *g);//输出并打印两点间的最短路径
void Dfs_print(GraphType *g,int sNum,int eNum);//深度优先遍历查询两景点间的所有路径
void AllPath_print(GraphType *g);//查询两点间的所有路径并打印
void BestPath(GraphType *g);//最佳路径
void System_exit(int *q);//退出系统
//邻接矩阵存储图
void Create_Map(GraphType *g)
{
   int i,j,k,e;
   FILE *rf;
   rf=fopen("map.txt","r");//打开文件,存储在项目路径，只读文件
   if(rf)
   {
       fscanf(rf,"%d%d",&g->vexNum,&g->edgeNum);//读取顶点数和边数
       //printf("%d %d",g->vexNum,g->edgeNum);
       for(i=0;i<g->vexNum;i++)
        {
            fscanf(rf,"%d%s%s",&g->vex[i].num,&g->vex[i].name,&g->vex[i].info);//读取顶点域信息

        }
       for(i=0;i<g->vexNum;i++)//初始化吧邻接矩阵
          for(j=0;j<g->vexNum;j++)
          {
           if(i==j) g->edge[i][j]=0;//对角线元素为0
           else g->edge[i][j]=INFINITY;
          }
       for(k=0;k<g->edgeNum;k++)//对边赋值代表路径长度
       {
           fscanf(rf,"%d%d%d",&i,&j,&e);
           g->edge[i][j]=e;
       }
       fclose(rf);//关闭文件
   }
   else g->edgeNum=0;

}
//校园图景展示
void Display_map()
{
    printf("\n                         河北大学南苑景点地图                       \n\n");
    printf("  ║================================（9）梅园宿舍=======================║\n");
    printf("  ║                                       ◎                            ║\n ");
    printf("  ║                                       ║                            ║\n  ");
    printf("  ║          （7）第九教学楼  =================  （8）综合教学楼=======║\n ");
    printf("  ║                   ◎                                  ◎            ║\n  ");
    printf("  ║===================╠════╩═════╩══╦═══╗===============║             ║\n");
    printf("                （6）敏秀园           ║                 ║             ║ \n ");
    printf("                      ◎=================================║             ║ \n ");
    printf("                                 ║                      ║             ║  \n ");
    printf("   （5）多功能管==========（3）主楼============（4）图书馆============║ \n");
    printf("           ◎                    ◎                    ◎               ║ \n ");
    printf("           ║                     ║                    ║               ║ \n");
    printf("           ║              （2）主楼广场               ║               ║ \n");
    printf("           ║                     ◎                    ║               ║ \n ");
    printf("           ║                     ║                    ║               ║ \n");
    printf("           ║==============（1）南苑大门===============║===============║ \n");
    printf("                                 ◎                                     \n ");
}
//景点信息查询
void SearchLocation(GraphType *g)
{
    int s;
    printf("\n请输入你要查找的景点编号：");
    scanf("%d",&s);

    printf("\n景点名称：%s\n\n",g->vex[s-1].name);
    printf("景点简介：%s\n\n",g->vex[s-1].info);
}
//Floyd算法求两景点间的一条最短路径
int dist[Max][Max];
int path[Max][Max];
void ShortPath(GraphType *g)
{
    int i,j,k;
    for(i=0;i<g->vexNum;i++)//初始化
    {
        for(j=0;j<g->vexNum;j++)
           {
              dist[i][j]=g->edge[i][j];
              if(i!=j&&dist[i][j]<INFINITY) path[i][j]=i;
              else path[i][j]=-1;
           }

    }
    for(k=0;k<g->vexNum;k++)//递推求解每两个景点的最短路径
    {
        for(i=0;i<g->vexNum;i++)
        {
            for(j=0;j<g->vexNum;j++)//更新dist[i][j]
            {
                if(dist[i][j]>(dist[i][k]+dist[k][j]))
                {
                    dist[i][j]=dist[i][k]+dist[k][j];
                    path[i][j]=k;
                }
            }
        }
    }
        for(i=0;i<g->vexNum;i++)
    {
        for(j=0;j<g->vexNum;j++)
        {
            printf("%-5d",path[i][j]);
        }
        printf("\n");
    }
}
//递归实现打印两点间的最短路径
void Floyd_print(GraphType *g,int sNum,int eNum)
{
    if(path[sNum][eNum]==-1||path[sNum][eNum]==eNum||path[sNum][eNum]==sNum) return;
    else
    {
        Floyd_print(g,sNum,path[sNum][eNum]);//将中间点作为终点继续打印路径
        printf("%s->",g->vex[path[sNum][eNum]].name);//打印中间点的名称
        Floyd_print(g,path[sNum][eNum],eNum);//将中间点作为起点继续打印
    }
}
//输出并打印两点之间的最短路径
void ShortPath_print(GraphType *g)
{
    int sNum,eNum;
    printf("\n请输入起点编号：");
    scanf("%d",&sNum);
    printf("\n请输入终点编号: ");
    scanf("%d",&eNum);
    printf("\n%s到%s的最短距离是：%dm\n", g->vex[--sNum].name, g->vex[--eNum].name, dist[sNum][eNum]);
	printf("\n这是最佳游览路线：");
	printf("%s->", g->vex[sNum].name);                                       /*输出路径上的起点*/
	Floyd_print(g, sNum, eNum);                                               /*输出路径上的中间点*/
	printf("%s\n\n", g->vex[eNum].name);
}
int main()
{
   GraphType g;
   Display_map();
   Create_Map(&g);
  //SearchLocation(&g);
  ShortPath(&g);
  ShortPath_print(&g);
   return 0;
}
