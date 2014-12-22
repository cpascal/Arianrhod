// Ҫ���Ķ�������ļ��������룬��ɶ���д�ļ��Ĳ���
//��������ܶ����ش����ַ��ļ�����ʾ���ܽ��û��Ӽ���������ķ��Ŵ�д���ش����ļ�����

//�ļ�Ŀ¼�õ��������ӣ���β�����һ��Ŀ¼��Ϊ��Ŀ¼���ļ���Ϊ�գ���
//�򿪵��ļ�������Ӧ�Ļ�ļ�Ŀ¼���رյ��ļ�ɾ����Ӧ�Ļ�ļ�Ŀ¼��
#pragma comment(linker, "/ENTRY:main")

#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#define TRUE 1
#define FALSE 0

//�û��ļ�Ŀ¼�ṹ
struct dataEntry
{
    char filename[6];//�ļ���
    char pcode[3];//Ϊ3λ����,�ֱ��Ӧ������������д������ִ�У�ֵΪ'1'����������Ϊ'0'������������
    int length;//�ļ�����
    int addr;//�ļ��ռ��׵�ַ
    dataEntry* next;
};
dataEntry* entryPtr1;
dataEntry* entryPtr2;

//���ļ�Ŀ¼�ṹ
struct dataMain
{
    char username[6];//�û���
    dataEntry* link;//�û��ļ�Ŀ¼��������ָ��
};
dataMain* userPtr1;
dataMain* userPtr2;
dataMain* mainUser[5];//��Ӧ5���û�

//��ļ�Ŀ¼�ṹ
struct dataActive
{
    char filename[6];
    char pcode[3];//��ȡ���Ʊ�����
    int rpointer;//��ǰ��ָ��
    int wpointer;//��ǰдָ��
    int addr;//�ļ��ռ��׵�ַ
    dataActive* next;
};
dataActive* entryBeginPtr;//��ļ�Ŀ¼��������ָ��
dataActive* ActiveEntryPtr1;
dataActive* ActiveEntryPtr2;

static int openNumber=0;
char name[6];//��ǰ�������ļ���

void main();
void init();
void pcreate();
void popen();
void close1(int s);
void pclose();
void pdelete();
void pread();
void pwrite();
void pdirectory();


//---------------------------------------------------------------------------------------
void main()
{ 
    int i,flag;
    
    init();
    flag=TRUE;
    while(flag)
    {
        printf("\nѡ���ܣ�1-�����ļ�  2-���ļ�  3-�ر��ļ�  4-ɾ���ļ�  \n");
        printf("          5-���ļ�    6-д�ļ�    7-Ŀ¼      8-�˳�\n");
        scanf("%d",&i);
        switch (i)
        {
        case 1:
            {
                pcreate();
                break;
            }
        case 2:
            {
                popen();
                break;
            }
        case 3:
            {
                pclose();
                break;
            }
        case 4:
            {
                pdelete();
                break;
            }
        case 5:
            {
                pread();
                break;
            }
        case 6:
            {
                pwrite();
                break;
            }
        case 7:
            {
                pdirectory();
                break;
            }
        case 8:
            flag=FALSE;
        }//switch (i)
        
    }//while(flag)
}



//--------------------------------------------------------------------------
//Ϊÿ���û�����һ����Ŀ¼���յ��ļ�Ŀ¼������ϵͳһ���յĻ�ļ�Ŀ¼��
void init()
{
    int usernum,i,j;
    printf("�û�������<5��?");
    scanf("%d",&usernum);
    if (usernum>5)
        usernum=5;
    printf("��ʼ�û���ע�ᡣ\n");
    
    //Ϊÿ���û�������Ŀ¼
    for (i=0;i<usernum;i++)
    { //����һ����Ŀ¼
        mainUser[i]=new dataMain;
        for(j=0;j<6;j++)
            (mainUser[i]->username)[j]=0;
        printf("�û�%d�����֣�(<=5���ַ�)",i);
        scanf("%s",mainUser[i]->username);//ָ���û���
        
        entryPtr1=new dataEntry;
        entryPtr1->next=NULL;
        for(j=0;j<6;j++)
            (entryPtr1->filename)[j]=0;//�յ��ļ�Ŀ¼
        mainUser[i]->link=entryPtr1;//ָ������û���������ļ�Ŀ¼
        
    }
    //����5���û�ʱ��������Ŀ¼��Ϊ�ա�
    for (i=usernum;i<5;i++)
        mainUser[i]=NULL;
    //�����յĻ�ļ�Ŀ¼��entryBeginPtr
    entryBeginPtr=new dataActive;
    entryBeginPtr->next=NULL;
    for(j=0;j<6;j++)
        (entryBeginPtr->filename)[j]=0; 
}



//--------------------------------------------------------------------------
//���ͬʱ��5���ļ���
void pcreate()
{
    char code[3];//������
    int i,j,useri;
    
    for (i=0;i<6;i++)
        name[i]=0;
    printf("�û�����?");
    scanf("%s",name);
    //����Ƿ�Ϸ��û�
    for (useri=0;useri<5;useri++)
    {
        j=0;
        while (j<6 && ((mainUser[useri]->username)[j]==name[j]) ) 
            j++;
        if (j==6)
            break;
    }
    if (useri==5)
    {
        printf("�㲻��ע���û���\n");
        return;
    }
    //�û�Ϊ��useri�û�
    for (i=0;i<6;i++)
        name[i]=0;
    printf("�½����ļ�����");
    scanf("%s",name);
    //Ѱ�Ҹ��û������һ���ļ�Ŀ¼
    entryPtr1=mainUser[useri]->link;//ȡ���û��ļ�Ŀ¼��������ָ��
    while ((entryPtr1->next)!=NULL)
        entryPtr1=entryPtr1->next;
    //Ϊ��Ŀ¼����ڵ�ռ�
    entryPtr2=new dataEntry;
    //��entryPtr2������β.��entryPtr1����һ���ڵ���entryPtr2,entryPtr2�ǿ�Ŀ¼��
    entryPtr2->next=NULL;
    for (i=0;i<6;i++)
        (entryPtr2->filename)[i]=' ';
    entryPtr1->next=entryPtr2;
    for (i=0;i<6;i++)
        (entryPtr1->filename)[i]=name[i];
    printf("�������ļ��ı�����(��111����Ӧ˳�򣺶�д��ִ�У���1������0��������)��");
    scanf("%s",code);
    for (i=0;i<3;i++)
        entryPtr1->pcode[i]=code[i];
    entryPtr1->length=0;//��ʼ�ļ�����Ϊ0
    printf("�ļ������ɹ�!\n");
}


//--------------------------------------------------------------------------
//���ļ���Ѱ�Ҹ��ļ�����Ѱ�ҵ���������Ӧ�Ļ�ļ�Ŀ¼��
void popen()
{
    int i,j,k,useri;
    bool flag;//�Ƿ��ҵ��ļ�
    
    for (i=0;i<6;i++)
        name[i]=0;
    printf("�򿪵��ļ�����?");
    scanf("%s",name);
    //�������ļ��в��Ҹ��ļ�
    flag=false;
    for (useri=0;useri<5;useri++)
    {  //�ڵ�useri���û���Ѱ��
        entryPtr1=mainUser[useri]->link;
        while (entryPtr1!=NULL)
        {
            for (j=0;j<6;j++)
            {
                if ((entryPtr1->filename)[j]!=name[j])
                    break;
            }
            if (j==6)
            {
                flag=true;
                break;//�ҵ����ļ�,�ǵ�useri�û���entryPtr1Ŀ¼	
            }
            else
                entryPtr1=entryPtr1->next;//�����һ���ļ�Ŀ¼
        } //while ((entryPtr1->next)!=NULL)
        if (flag)
            break;
    }//for (useri=0;useri<5;useri++)
    if (!flag)
    {
        printf("���ļ���δ������\n");
        return;
    }
    //�Ѿ��ҵ��ļ����ǵ�useri�û���entryPtr1Ŀ¼.Ϊ���ļ�����һ����ļ�Ŀ¼��
    if (openNumber>5)
    {
        printf("�򿪵��ļ����Ѿ���������޶�(5��)�����ܴ򿪸��ļ�.\n");
        return;
    }
    //���ļ�
    openNumber++;
    //�ҵ���ļ�Ŀ¼����β��
    ActiveEntryPtr2=entryBeginPtr;//ȡ��ļ�Ŀ¼����
    while ((ActiveEntryPtr2->next)!=NULL)
        ActiveEntryPtr2=ActiveEntryPtr2->next;
    ActiveEntryPtr1=new dataActive;//�����µĻĿ¼�ռ�
    //ActiveEntryPtr1��Ϊ��β���롣ActiveEntryPtr2����һ���ڵ���ActiveEntryPtr1��
    ActiveEntryPtr1->next=NULL;
    ActiveEntryPtr2->next=ActiveEntryPtr1;
    for (k=0;k<6;k++)
        (ActiveEntryPtr2->filename)[k]=name[k];
    for (k=0;k<3;k++)
        (ActiveEntryPtr2->pcode)[k]=(entryPtr1->pcode)[k];
    ActiveEntryPtr2->rpointer=0;
    ActiveEntryPtr2->wpointer=0;
    ActiveEntryPtr2->addr = 0;
    printf("�ļ��򿪳ɹ���\n");
}

//--------------------------------------------------------------------------
//�ر��ļ����ڻĿ¼��Ѱ���ļ�����ɾ����Ӧ�ڵ㡣
//statusΪ1������ʾ�ر���Ϣ������ɾ���ļ�֮ǰ���ļ��رա�statusΪ0����ʾ�ر���Ϣ�������ļ��رղ�����
void close1(int status)
{
    int i,j;
    bool flag;
    
    for (i=0;i<6;i++)
        name[i]=0;
    printf("�ļ����֣�");
    scanf("%s",name);
    //�ڻ�ļ�Ŀ¼����Ѱ�Ҹ��ļ�
    flag=false;
    ActiveEntryPtr1=NULL;//ǰһ���ڵ�
    ActiveEntryPtr2=entryBeginPtr;
    while (ActiveEntryPtr2!=NULL)
    {
        for (j=0;j<6;j++)
        {
            if ((ActiveEntryPtr2->filename)[j]!=name[j])
                break;
        }
        if (j==6)
        {
            flag=true;
            break;//�ҵ����ļ�ActiveEntryPtr2	
        }
        else
        {
            ActiveEntryPtr1=ActiveEntryPtr2;//����ǰһ���ڵ�
            ActiveEntryPtr2=ActiveEntryPtr2->next;//�����һ���ļ�Ŀ¼
        }
    }//while (ActiveEntryPtr2!=NULL)
    if (!flag)
    {
        if (status==0)
            printf("���ļ���δ�򿪡�\n");
        return;
    }
    //�ر��ļ���ɾ���ڵ�ActiveEntryPtr2, ActiveEntryPtr2��ǰһ�ڵ���ActiveEntryPtr1.
    if (ActiveEntryPtr2==entryBeginPtr)   //����
        entryBeginPtr=ActiveEntryPtr2->next;
    else
        ActiveEntryPtr1->next=ActiveEntryPtr2->next;
    openNumber--;
    delete ActiveEntryPtr2;//�ͷŽڵ�ռ�
    if (status==0)
        printf("�ļ��ɹ��رա�\n");
}

//-------------------------------------------------------------------
void pclose()
{
    close1(0);//�ر��ļ�
}


//--------------------------------------------------------------------------
//ɾ���ļ������ȹر��ļ���Ȼ����ȫ���û��ļ�Ŀ¼��Ѱ�Ҳ�ɾ����Ӧ�ļ�Ŀ¼��
void pdelete()
{
    int j,useri;
    bool flag;
    
    //�رմ򿪵��ļ�name
    close1(1);
    //��ȫ�����û���Ѱ���ļ�name��ɾ����ӦĿ¼
    for (useri=0;useri<5;useri++)
    { //�û�i
        flag=false;
        entryPtr2=NULL;//ǰһ���ڵ�
        entryPtr1=mainUser[useri]->link;//ȡ�ļ�Ŀ¼�����׽ڵ�
        while (entryPtr1!=NULL)
        {
            for (j=0;j<6;j++)
            {
                if ((entryPtr1->filename)[j]!=name[j])
                    break;
            }
            if (j==6)
            {
                flag=true;
                break;//�ҵ����ļ�entryPtr1,���ڵ�useri���û���	
            }
            else
            {
                entryPtr2=entryPtr1;//����ǰһ���ڵ�
                entryPtr1=entryPtr1->next;//�����һ���ļ�Ŀ¼
            }
        }//while (entryPtr1!=NULL)
        if (flag)       
            break;
    }//for (useri=0;useri<5;useri++)
    if (!flag)
    {
        printf("�ļ�û�д�����\n");
        return;
    }
    //ɾ��entryPtr1Ŀ¼����ǰһ��Ŀ¼��entryPtr2.
    if (entryPtr1==mainUser[useri]->link)   //entryPtr1������
        mainUser[useri]->link=entryPtr1->next;
    else
        entryPtr2->next=entryPtr1->next;
    delete entryPtr1;
    printf("�ļ�%s���ɹ�ɾ����\n",name);
}


//--------------------------------------------------------------------------
void pread()
{
    FILE *fp;
    dataActive *p;

    printf("ȷʵҪ��test.txt���뵽�ĸ��ļ�: ");
    fgets(name, sizeof(name), stdin);
    
    p = entryBeginPtr;
    while (p->next)
    {
        if (strncmp(p->filename, name, sizeof(name)) == 0)
            break;
    }
    if (p->next == NULL)
    {
        printf("�Ҳ��� %s.\n", name);
        return;
    }

    fp = fopen("test.txt", "rb");
    p->
}


//--------------------------------------------------------------------------
void pwrite()
{
    printf("current opened file: %s\n", name);
}


//--------------------------------------------------------------------------
//��ѯ��Ŀ¼�����û�Ŀ¼��
void pdirectory()
{  
    char sel,ppcode[4];
    int i,j,fileNumber,totalNumber,useri;
    
    printf("��ѯ��Ŀ¼��1�������û�Ŀ¼��2����");
    scanf("%d",&sel);
    totalNumber=0;//ͳ���ܵ��ļ���
    if (sel==1)
    {//��ѯ��Ŀ¼
        printf("��Ŀ¼��\n");
        printf("�û���                �ļ�����\n");
        for(useri=0;useri<5;useri++)
        {
            if (mainUser[useri]!=NULL)
            {
                fileNumber=0;//����ͳ�Ƹ��û����ļ���
                entryPtr1=mainUser[useri]->link;
                while (entryPtr1!=NULL)
                {
                    fileNumber++;//ͳ�Ƹ��û����ļ���
                    entryPtr1=entryPtr1->next;
                }
                fileNumber--;//���һ��Ϊ��Ŀ¼
                printf("%s                %d\n",mainUser[useri]->username,fileNumber);
                totalNumber+=fileNumber;//ͳ���ܵ��ļ���
            }
        }//for(useri=0;useri<5;useri++)
        printf("�ܵ��ļ���=%d\n",totalNumber);
    }
    else
    {
        //��ѯ�û�Ŀ¼
        for (i=0;i<6;i++)
            name[i]=0;
        printf("�û����֣�");
        scanf("%s",name);
        for (useri=0;useri<5;useri++)
        {
            for (j=0;j<6;j++)
            {
                if ((mainUser[useri]->username)[j]!=name[j])
                    break;
            }
            if (j==6)
                break;//�鵽���û����ǵ�useri���û�
        } //for (useri=0;useri<5;useri++)
        if (useri==5)
        {
            printf("�û�Ŀ¼�����ڡ�\n");
            return;
        }
        //��ʾ��useri���û���Ŀ¼�ļ�
        printf("�û�%s��Ŀ¼��\n",name);
        printf("�ļ���      ������      ����\n");
        entryPtr1=mainUser[useri]->link;
        while (entryPtr1!=NULL)
        {
            for (i=0;i<3;i++)
                ppcode[i]=entryPtr1->pcode[i];
            ppcode[3]=0;
            if (entryPtr1->next!=NULL)//���һ��Ϊ�սڵ�
                printf("%s          %s         %d\n",entryPtr1->filename,ppcode,entryPtr1->length);
            entryPtr1=entryPtr1->next;
        }
    }
}



