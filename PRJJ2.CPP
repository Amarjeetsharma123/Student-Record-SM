#include<stdio.h>
#include<dos.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
typedef struct
{
	int roll;
	char name[30];
	char gen;
	char course[30];
	char contact[10];
}student;
student s;
FILE *fp;
void window();
void splash();
int pass();
void menu();
void add();
void display();
void edit();
void del();
void search();
int main()
{
 int ch;
 clrscr();
	window();
 textcolor(YELLOW);
 if(pass()==1)
 {

	gotoxy(10,6);
	textcolor(GREEN+BLINK);
	cprintf("correct Password");
	getch();
	splash();
	clrscr();
	while(1)
	{
	menu();
	scanf("%d",&ch);
	textbackground(BLUE);
	window(1,1,80,25);
	clrscr();
		switch(ch)
		{
		case 1:add();break;
		case 2:del();break;
		case 3:edit();break;
		case 4:search();break;
		case 5:display();break;
		case 7:exit(0);
		}
	 }
 }
 else
 {
 gotoxy(10,6);
 textcolor(RED+BLINK);
 cprintf("Incorrect Password");
 }


 getch();
 return 0;
}
void window()
{

 textbackground(YELLOW);
 clrscr();
 window(20,8,60,20);
 textbackground(BLACK);
 clrscr();
 gotoxy(18,1);
 textcolor(YELLOW);
 cprintf("LOGIN");
 gotoxy(16,2);
 cprintf("=========");
 gotoxy(6,4);
 cprintf("Enter the Password : ");
}
int pass()
{
	int i=0;
	char pass[30],ch,check[30]="amar";
	while(1)
	{
		ch=getch();
		if(ch==13)
		{
		pass[i]='\0' ;
		break;
		}
		pass[i++]=ch;
		textcolor(YELLOW);
		cprintf("*");
	}
	if(strcmp(pass,check)==0)
	return 1;
	else
	return 0;
}
void splash()
{
clrscr();
 textbackground(BLUE);
 window(1,1,80,25);
 clrscr();
 textcolor(YELLOW);
 gotoxy(23,2);
 cprintf("Student Record Management System");
 gotoxy(22,3);
 cprintf("==================================");
 gotoxy(26,6);
 cprintf("Developed By Mr. Amarjeet");
 gotoxy(30,8);
 cprintf("Version 1.0");
 gotoxy(10,15);
 cprintf("Loading");
 textcolor(YELLOW+BLINK);
 cprintf("....");
 gotoxy(10,16) ;
 for(int i=1;i<=30;i++)
 {
 delay(10);
 textcolor(YELLOW);
 cprintf("%c ",220);
 }
}
void menu()
{
 textbackground(YELLOW);
 window(1,1,80,25);
 clrscr();
 textbackground(BLACK);
 window(20,8,60,20);
 clrscr();
 textcolor(YELLOW);
 gotoxy(18,1);
 cprintf("Main Menu");
 gotoxy(8,2);
 cprintf("===========================");
 gotoxy(12,3);
 textcolor(11);
 cprintf("1. Add Student");
 gotoxy(12,4);
 cprintf("2. Delete Student");
 gotoxy(12,5);
 cprintf("3. Edit Student");
 gotoxy(12,6);
 cprintf("4. Search Student");
 gotoxy(12,7);
 cprintf("5. View All student");
 gotoxy(12,8);
 cprintf("6. Change Password");
 gotoxy(12,9);
 cprintf("7. Exit");
 gotoxy(8,10);
 textcolor(YELLOW) ;
 cprintf("===========================");
 gotoxy(8,11);
 cprintf("Enter your choice(1-7)? : ");
}
void add()
{
	char ch[30];
	fp=fopen("stu.txt","a");
	if(fp==NULL)
	printf("File not found");
	else
	gotoxy(25,2);
	printf("Enter Details to Add New Student");
	gotoxy(2,3);
	printf("===============================================================");
		gotoxy(5,4);
		printf("Enter Roll     : ");
		scanf("%d",&s.roll);
		fflush(stdin);

		gotoxy(5,6);
		printf("Enter Name     : ");
		gets(s.name);

		gotoxy(5,8);
		fflush(stdin);
		printf("Enter Gender   : ");
		scanf("%c",&s.gen);

		gotoxy(5,10);
		fflush(stdin);
		printf("Enter Course   : ");
		gets(s.course);

		gotoxy(5,12);
		printf("Enter Contact  : ");
		fflush(stdin);
		gets(s.contact);

		gotoxy(5,14);
		fflush(stdin);
		fwrite(&s,sizeof(s),1,fp);


	fclose(fp);
}

void display()
{
	fp=fopen("stu.txt","r");
	gotoxy(30,1);
	printf("List of All Students");
	gotoxy(1,2);
	printf("==============================================================");
	gotoxy(1,3);
	printf("Roll");
	gotoxy(8,3);
	printf("Name");
	gotoxy(25,3);
	printf("Gender");
	gotoxy(33,3);
	printf("Course");
	gotoxy(48,3);
	printf("Contact");
	gotoxy(1,4);
	printf("==============================================================");
	int r=5;
	while(fread(&s,sizeof(s),1,fp)!=NULL)
	{
	gotoxy(1,r);
	printf("%d",s.roll);
	gotoxy(8,r);
	printf("%s",s.name);
	gotoxy(25,r);
	printf("%c",s.gen);
	gotoxy(33,r);
	printf("%s",s.course);
	gotoxy(48,r);
	printf("%s",s.contact);
	r=r+1;
	}
	fclose(fp);
	getch();
}
void del()
{
	int r;
	student s;
	FILE *fp=fopen("stu.txt","r");
	if(fp==NULL)
	{
		printf("File not found");
		//return;
	}
	int ch=0;
	printf("Delete Student\n");
	printf("==============================================================\n");
	printf("Enter Roll number to be deleted \n");
	fflush(stdin);
	scanf("%d",&r);
	while(fread(&s,sizeof(s),1,fp)!=NULL) //checking roll numbers exist or not
	{
		if(s.roll==r)
		{
		printf("Name    : %s\n",s.name);
		printf("Gender  : %c\n",s.gen);
		printf("Course  : %s\n",s.course);
		printf("Contact : %s\n",s.contact);
		ch++;
		}
	}
	if(ch==0)
	{
		printf("Record not found");
		return;
	}
	else
	{
		rewind(fp);
		FILE *nfp=fopen("temp.txt","w");
		while(fread(&s,sizeof(s),1,fp)!=NULL)
		{
			if(s.roll!=r)
			{
			fwrite(&s,sizeof(s),1,nfp);
			}
		}
		fclose(fp);
		fclose(nfp);
		remove("stu.txt");
		rename("temp.txt","stu.txt");
		printf("successfully deleted");
	}
	getch();
}
void edit()
{
	int r;
	student s;
	FILE *fp=fopen("stu.txt","r+");
	if(fp==NULL)
	{
		printf("File not found");
		//return;
	}
	int ch=0;
	printf("Edit Student details\n");
	printf("==============================================================\n");
	printf("Enter Roll number to be edited \n");
	fflush(stdin);
	scanf("%d",&r);
	while(fread(&s,sizeof(s),1,fp)!=NULL) //checking roll numbers exist or not
	{
		if(s.roll==r)
		{
		printf("Name    : %s\n",s.name);
		printf("Gender  : %c\n",s.gen);
		printf("Course  : %s\n",s.course);
		printf("Contact : %s\n",s.contact);
		ch++;
		}
	}
	if(ch==0)
	{
		printf("Record not found");
		return;
	}
	else
	{
		int pos=ftell(fp);
		fseek(fp,pos-sizeof(s),SEEK_SET);
		printf("Enter New Details of Student\n");
		printf("===============================================================\n");
		printf("Enter Roll     : ");
		scanf("%d",&s.roll);
		fflush(stdin);

		printf("Enter Name     : ");
		gets(s.name);

		fflush(stdin);
		printf("Enter Gender   : ");
		scanf("%c",&s.gen);

		fflush(stdin);
		printf("Enter Course   : ");
		gets(s.course);

		printf("Enter Contact  : ");
		fflush(stdin);
		gets(s.contact);

		fflush(stdin);
		printf("\n");
		fwrite(&s,sizeof(s),1,fp);
		printf("successfully updated");
	}
	fclose(fp);
	getch();
}
void search()
{
	textbackground(BLUE);
	clrscr();
	textcolor(YELLOW);
	char n[30];
	student s;
	FILE *fp=fopen("stu.txt","r+");
	if(fp==NULL)
	{
		printf("File not found");
	}
	int ch=0;
	printf("Search Student Here\n");
	printf("==============================================================\n");
	printf("Enter Name of student to be searched : \n");
	fflush(stdin);
	gets(n);
	//system("cls");
	printf("==============================================================\n");
	
	printf("Roll\t");
	
	printf("Name\t\t");
	
	printf("Gender\t");
	
	printf("Course\t");
	
	printf("Contact\n");
	printf("==============================================================\n");
	while(fread(&s,sizeof(s),1,fp)!=NULL) //checking roll numbers exist or not
	{
		if(strcmpi(s.name,n)==0)
		{
		printf("%d\t",s.roll);
		printf("%s\t\t",s.name);
		printf("%c\t",s.gen);
		printf("%s\t",s.course);
		printf("%s\n",s.contact);
		ch++;
		}
	}
	if(ch==0)
	{
		printf("Record not found");
		return;
	}
	fclose(fp);
	getch();
}









