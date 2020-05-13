#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include <unistd.h>

//Global variables

//structs
struct loggedIn
{
    char username[20];
    int authuser;
};

struct faculty
{
    char facultyName[30];
    char department[30];
};

struct course
{
    char courseName[40];
    int courseSem;
};

struct result
{
    
};


struct new_record
{
    char fname[15];
    char *lname[20];
    struct faculty fac;
    struct course crs;
    char studentId[10];
    char address[70];
    long phone;
    char email[40];
};

//functions
void clear()
{
    printf("\e[1;1H\e[2J");
}
void topbar()
{
    printf("\t\t<!-----------------------------------------------------------------------!>\n\n\n");
}
void header(){
    topbar();
    printf("\t\t\t\t\tWelcome to the University\n\t\t\t\t\t\tNew Delhi\n\n\n");
}
void display(struct new_record new)
{
    topbar();
    printf("Student's Name : %s %s\n",new.fname,new.lname);
    printf("Student's Email : %s \n",new.email);
    printf("Student's Phone : %ld \n",new.phone);
    printf("Student's Address : %s\n ",new.address);
    printf("Student's Address : %s\n ",new.address);
    printf("Student's Faculty : %s\n ",new.fac.facultyName);
    printf("Student's Department : %s\n ",new.fac.department);
    printf("Student's Course : %s\n ",new.crs.courseName);
    printf("Student's semester : %d\n ",new.crs.courseSem);

}

int options(int n)
{
    int choice;
    switch (n)
    {
    case 1:
        printf("\n1. Add new student record\n2. View student details\n3. update record\n4. search record\n5. delete a record\n99. Exit\n");
        break;
    
    default:
        break;
    }
    printf("choose : ");
    scanf("%d",&choice);
    return choice;
}

int signin(struct loggedIn *temp){
    printf("SIGNIN:\nuser : ");
    char username[20];
    scanf("%s",&username[0]);
    char *password = getpass("Password: ");
    if(strcmp(username,"admin")==0 && strcmp(password,"admin")==0)
    {
        temp->authuser=1;
        strcpy(temp->username,username);
        return 1;
    }
    else
    {
        return 0;
    }
}

void addNew()
{
    clear();
    struct new_record new;
    FILE *fptr;
    fptr = fopen("details.dat","a+");
    if(fptr == NULL)
    {
        printf("Error occurred at opening file\n");
    }
    else
    {char c;
        printf("Student's first Name : "); c=getchar();
        scanf("%[^\n]s",&new.fname[0]);c=getchar(); 
        printf("Student's last Name : "); 
        scanf("%[^\n]s",&new.lname[0]);c=getchar();  
        printf("Student's Email : ");   
        scanf("%[^\n]s",&new.email[0]);c=getchar();
        printf("Student's phone : ");   
        scanf("%ld",&new.phone);c=getchar(); 
        printf("Student's permanent Address : ");   
        scanf("%[^\n]s",&new.address[0]);c=getchar();
        printf("Student's faculty : "); 
        scanf("%[^\n]s",&new.fac.facultyName[0]);c=getchar();  
        printf("Student's Department : ");   
        scanf("%[^\n]s",&new.fac.department[0]);c=getchar();
        printf("Student's course : ");  
        scanf("%[^\n]s",&new.crs.courseName[0]);c=getchar();
        printf("Student's sem : ");   
        scanf("%d",&new.crs.courseSem);c=getchar(); 
        printf("Student's id : ");
        scanf("%[^\n]s",&new.studentId[0]);c=getchar();  
        fwrite(&new,sizeof(struct new_record),1,fptr);
        fclose(fptr);
        printf("Successfully Added !\nPress Enter to continue(ctrl + c to quit)\n");
        getc(stdin);
    }
}

void viewRecord()
{
    clear();
    topbar();
    FILE *fptr;
	fptr=fopen("details.dat","r");
	if(fptr == NULL){
		printf("file can not open\n");
	}
	struct new_record b;
	while(fread(&b,sizeof(struct new_record),1,fptr)>0){
		printf("%s %s | %s | %ld | %s | %s | %s | %s | %d | %s \n",b.fname,b.lname,b.email,b.phone,b.address,b.fac.facultyName,b.fac.department,b.crs.courseName,b.crs.courseSem,b.studentId);
	}
	fclose(fptr);
    printf("\n\nPress 99 to continue (ctrl + c to quit)\n");
    int i;
    do
    {
        scanf("%i",&i);
    } while (i!=99);
    
}
void updateRecord()
{

}
void searchRecord()
{
    FILE *fptr;
    fptr = fopen("details.dat","r");
    if(fptr==NULL)
    {
        printf("\nFile not found.\n");
    }
    else
    {
        char st[10];
        struct new_record b;
        printf("\nEnter student ID : ");
        scanf("%s",&st[0]);
	    while(fread(&b,sizeof(struct new_record),1,fptr)>0){
            if(strcmp(b.studentId,st)==0)
            {
                display(b);
            }
            else
            {
                printf("No match found\n");
            }
        }
        char c;
        c=getchar();
    }
}
void deleteRecord()
{

}

//Main body
int main()
{
    clear();
    int choice;
    struct loggedIn *user=(struct loggedIn *)malloc(sizeof(struct loggedIn));
    header();
    for(int i=0;i<3;i++)
    {
        int a=signin(user);
        if(a==1)
        {
            break;
        }   
        else
        {
            if(i==2)
            {
                break;
            }
            printf("\nwrong credentials. you have %d attempts left\n",2-i);
            continue;
        }
    }
    if(user->authuser)
    {
    do{
        clear();  //clears screen
        header();
        printf("Hi %s :)",user->username);  
        choice=options(1);     //for home options
        switch (choice)
        {
        case 1:
            addNew();
            break;
        case 2:
            viewRecord();
            break;
        case 3:
            updateRecord();break;
        case 4:
            searchRecord();break;
        case 5:
            deleteRecord();break;
        default:
            break;
        }
        }while(choice != 99);
    }
    getc(stdin);
    return 0;
}
