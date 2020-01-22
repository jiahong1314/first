#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INFINITY 10000
#define Max 20
typedef struct          //��ž�����Ϣ�Ľṹ��
   {
     int num;              //�������
     char name[20];        //��������
     char info[200];       //������
   }VertexType;
   typedef struct               //У԰����ͼ�ṹ��
   {
      VertexType vex[Max];      //������Ϣ��
      int edge[Max][Max];       //�ڽӾ���洢ͼ
      int vexNum,edgeNum;       //ͼ�ж������ͱ���
   }GraphType;
/*int menu();                                //���˵�
void Create_Map(mgraphtype *g);            //���ļ���ȡ��Ϣ����ͼ
void Print_Map();                          //��ʾУ԰�����ͼ
int Judge_Input(int num);                   //�ж�����ı���Ƿ����
void Search_Location(mgraphtype *g);       //������Ϣ��ѯ
void ShortPath(mgraphtype *g);             //�󾰵�����·��
void Floyd_Print(mgraphtype *g, int sNum, int eNum);//�ݹ��ӡ��������·��
void Shortpath_Print(mgraphtype *g);    //�������ӡ���������·��
void Dfs_Print(mgraphtype *g, int sNum, int eNum);//������ȱ�����ѯ�����������·��
void Allpath_Print(mgraphtype *g);    //��ѯ������������·������ӡ
void BestPath(mgraphtype *g);        //�ඥ��������·��
void System_Exit(int *q);            //�˳�ϵͳ
*/
int menu();   //���˵�
void Create_Map(GraphType *g);//��ȡ��Ϣ����ͼ
void PrintMap();//��ʾУ԰������Ϣ
int JudgeInput(int num);//�ж��������Ƿ����
void SearchLocation(GraphType *g);//������Ϣ��ѯ
void ShortPath(GraphType *g);//�����·��
void Floyd_print(GraphType *g,int sNum,int eNum);//�ݹ��ӡ���·��
void ShortPath_print(GraphType *g);//�������ӡ���������·��
void Dfs_print(GraphType *g,int sNum,int eNum);//������ȱ�����ѯ������������·��
void AllPath_print(GraphType *g);//��ѯ����������·������ӡ
void BestPath(GraphType *g);//���·��
void System_exit(int *q);//�˳�ϵͳ
//�ڽӾ���洢ͼ
void Create_Map(GraphType *g)
{
   int i,j,k,e;
   FILE *rf;
   rf=fopen("map.txt","r");//���ļ�,�洢����Ŀ·����ֻ���ļ�
   if(rf)
   {
       fscanf(rf,"%d%d",&g->vexNum,&g->edgeNum);//��ȡ�������ͱ���
       //printf("%d %d",g->vexNum,g->edgeNum);
       for(i=0;i<g->vexNum;i++)
        {
            fscanf(rf,"%d%s%s",&g->vex[i].num,&g->vex[i].name,&g->vex[i].info);//��ȡ��������Ϣ

        }
       for(i=0;i<g->vexNum;i++)//��ʼ�����ڽӾ���
          for(j=0;j<g->vexNum;j++)
          {
           if(i==j) g->edge[i][j]=0;//�Խ���Ԫ��Ϊ0
           else g->edge[i][j]=INFINITY;
          }
       for(k=0;k<g->edgeNum;k++)//�Ա߸�ֵ����·������
       {
           fscanf(rf,"%d%d%d",&i,&j,&e);
           g->edge[i][j]=e;
       }
       fclose(rf);//�ر��ļ�
   }
   else g->edgeNum=0;

}
//У԰ͼ��չʾ
void Display_map()
{
    printf("\n                         �ӱ���ѧ��Է�����ͼ                       \n\n");
    printf("  �U================================��9��÷԰����=======================�U\n");
    printf("  �U                                       ��                            �U\n ");
    printf("  �U                                       �U                            �U\n  ");
    printf("  �U          ��7���ھŽ�ѧ¥  =================  ��8���ۺϽ�ѧ¥=======�U\n ");
    printf("  �U                   ��                                  ��            �U\n  ");
    printf("  �U===================�d�T�T�T�T�m�T�T�T�T�T�m�T�T�j�T�T�T�[===============�U             �U\n");
    printf("                ��6������԰           �U                 �U             �U \n ");
    printf("                      ��=================================�U             �U \n ");
    printf("                                 �U                      �U             �U  \n ");
    printf("   ��5���๦�ܹ�==========��3����¥============��4��ͼ���============�U \n");
    printf("           ��                    ��                    ��               �U \n ");
    printf("           �U                     �U                    �U               �U \n");
    printf("           �U              ��2����¥�㳡               �U               �U \n");
    printf("           �U                     ��                    �U               �U \n ");
    printf("           �U                     �U                    �U               �U \n");
    printf("           �U==============��1����Է����===============�U===============�U \n");
    printf("                                 ��                                     \n ");
}
//������Ϣ��ѯ
void SearchLocation(GraphType *g)
{
    int s;
    printf("\n��������Ҫ���ҵľ����ţ�");
    scanf("%d",&s);

    printf("\n�������ƣ�%s\n\n",g->vex[s-1].name);
    printf("�����飺%s\n\n",g->vex[s-1].info);
}
//Floyd�㷨����������һ�����·��
int dist[Max][Max];
int path[Max][Max];
void ShortPath(GraphType *g)
{
    int i,j,k;
    for(i=0;i<g->vexNum;i++)//��ʼ��
    {
        for(j=0;j<g->vexNum;j++)
           {
              dist[i][j]=g->edge[i][j];
              if(i!=j&&dist[i][j]<INFINITY) path[i][j]=i;
              else path[i][j]=-1;
           }

    }
    for(k=0;k<g->vexNum;k++)//�������ÿ������������·��
    {
        for(i=0;i<g->vexNum;i++)
        {
            for(j=0;j<g->vexNum;j++)//����dist[i][j]
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
//�ݹ�ʵ�ִ�ӡ���������·��
void Floyd_print(GraphType *g,int sNum,int eNum)
{
    if(path[sNum][eNum]==-1||path[sNum][eNum]==eNum||path[sNum][eNum]==sNum) return;
    else
    {
        Floyd_print(g,sNum,path[sNum][eNum]);//���м����Ϊ�յ������ӡ·��
        printf("%s->",g->vex[path[sNum][eNum]].name);//��ӡ�м�������
        Floyd_print(g,path[sNum][eNum],eNum);//���м����Ϊ��������ӡ
    }
}
//�������ӡ����֮������·��
void ShortPath_print(GraphType *g)
{
    int sNum,eNum;
    printf("\n����������ţ�");
    scanf("%d",&sNum);
    printf("\n�������յ���: ");
    scanf("%d",&eNum);
    printf("\n%s��%s����̾����ǣ�%dm\n", g->vex[--sNum].name, g->vex[--eNum].name, dist[sNum][eNum]);
	printf("\n�����������·�ߣ�");
	printf("%s->", g->vex[sNum].name);                                       /*���·���ϵ����*/
	Floyd_print(g, sNum, eNum);                                               /*���·���ϵ��м��*/
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
