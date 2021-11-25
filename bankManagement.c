#include <stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

//structure giving: account_number, balance (in acccount), name(of customer).

struct bank_management
{
    char name[80];
    int acc_no;
    int bal;
};

void add_acc(struct bank_management arr[80], int s)
{
        FILE *fptr;
        fptr = fopen("egg.txt", "a");
        printf("\033[0m");
        printf("\033[0;33m");
        printf("\n\t\t\t\t\t--- Enter data for a NEW RECORD ---\n");
        printf("\033[0m");
        printf("\t\t\t\t\t\tEnter account_no : ");
        scanf("%d", &arr[s].acc_no);
        fflush(stdin);
        printf("\t\t\t\t\t\tEnter name : ");
        gets(arr[s].name);
        printf("\t\t\t\t\t\tEnter balance : ");
        scanf("%d", &arr[s].bal);
        fprintf(fptr, "%d %s %d\n", arr[s].acc_no,arr[s].name,arr[s].bal);
        fclose(fptr);
}

void display(struct bank_management arr[80])
{
    FILE *fptr;
    fptr = fopen("egg.txt", "a+");
    struct bank_management *p;
    p=arr;
    printf("\033[0m");
    printf("\033[1;33m");
    printf("\n\t\t\t\t\tA/c No\t\tName\t\tBalance\n");
    while(fscanf(fptr,"%d%s%d\n", &p->acc_no, p->name, &p->bal)!=EOF)
    {
        printf("\033[0m");
        printf("\033[0;33m");
        printf("\t\t\t\t\t%d\t\t%s\t\t%d\n", p->acc_no, p->name, p->bal);
        p=p+1;
    }
    fclose(fptr);
}

int search(struct bank_management arr[80], int number)
{
    FILE *fptr;
    fptr = fopen("egg.txt", "r");
    int c;
    struct bank_management *p;
    p=arr;
    c=0;
    while(fscanf(fptr,"%d%s%d\n", &p->acc_no, p->name, &p->bal)!=EOF)
    {
        if(p->acc_no == number)
        {
            fclose(fptr);
            return c;
        }
        c++;
        p=p+1;
    }
    fclose(fptr);
    return  -1;
}

void deposit(struct bank_management arr[], int number, int amt)
{
    FILE *neww,*old;
    struct bank_management *p;
    p=arr;
    int test=0;
    old = fopen("egg.txt", "r");
    neww = fopen("Temp.txt","w");
    while(fscanf(old,"%d%s%d\n", &p->acc_no, p->name, &p->bal)!=EOF)
    {
        if(p->acc_no==number)
        {
            test++;
            p->bal+=amt;
            fprintf(neww, "%d %s %d\n",p->acc_no, p->name, p->bal);
            printf("\033[0m");
            printf("\033[1;32m");
            printf("\n\t\t\t\t\t--> Amount DEPOSITED sucessfully!!!\n");
        }
        else
        {
            fprintf(neww, "%d %s %d\n",p->acc_no, p->name, p->bal);
        }
    }
    fclose(old);
    fclose(neww);
    remove("egg.txt");
    rename("Temp.txt","egg.txt");
    if(test==0)
    {
        printf("\033[0m");
        printf("\033[1;31m");
        printf("\n\t\t\t\t\t--> This Record is ** NOT FOUND **\n");
    }
}

void withdraw(struct bank_management arr[], int number, int amt)
{
    FILE *neww,*old;
    struct bank_management *p;
    p=arr;
    int test=0;
    old = fopen("egg.txt", "r");
    neww = fopen("Temp.txt","w");
    while(fscanf(old,"%d%s%d\n", &p->acc_no, p->name, &p->bal)!=EOF)
    {
        if(p->acc_no==number)
        {
            test++;
            if(p->bal>amt)
            {
                p->bal-=amt;
                fprintf(neww, "%d %s %d\n",p->acc_no, p->name, p->bal);
                printf("\033[0m");
                printf("\033[1;32m");
                printf("\n\t\t\t\t\t--> Amount DEDUCTED sucessfully!!!\n");
            }
        else
            {
                printf("\033[0m");
                printf("\033[0;31m");
                printf("\n\t\t\t\t\t--> NOT ENOUGH BALANCE in your account!!\n");
                fprintf(neww, "%d %s %d\n",p->acc_no, p->name, p->bal);
            }
        }
        else
            {
                fprintf(neww, "%d %s %d\n",p->acc_no, p->name, p->bal);
            }
    }
    fclose(old);
    fclose(neww);
    remove("egg.txt");
    rename("Temp.txt","egg.txt");
    if(test==0)
    {
        printf("\033[0m");
        printf("\033[1;31m");
        printf("\n\t\t\t\t\t--> This Record is ** NOT FOUND **\n");
    }
}

void del(struct bank_management arr[80], int number)
{
    FILE *neww,*old;
    struct bank_management *pt;
    pt=arr;
    int test=0;
    old = fopen("egg.txt", "r");
    neww = fopen("Temp.txt","w");
    while(fscanf(old,"%d%s%d\n", &pt->acc_no, pt->name, &pt->bal)!=EOF)
    {
        if(pt->acc_no!=number)
        {
            fprintf(neww, "%d %s %d\n",pt->acc_no, pt->name, pt->bal);
        }
        else
            {
                test++;
                printf("\033[0m");
                printf("\033[1;32m");
                printf("\n\t\t\t\t\t--> Deleted successfully!!\n");
            }
    }
    fclose(old);
    fclose(neww);
    remove("egg.txt");
    rename("Temp.txt","egg.txt");
    if(test==0)
    {
        printf("\033[0m");
        printf("\033[1;31m");
        printf("\n\t\t\t\t\t--> This Record is ** NOT FOUND **");
    }
}


int main()
{
    struct bank_management obj[80];
    struct bank_management *ptr;
    ptr=obj;
    int n=0, ch, account_no, amount, pos;
    system("color 0");
    system("color 0F");
    printf("\033[0;34m");
    printf("\n\t\t\t\t\t**************************************************");
    printf("\033[0m");
    printf("\033[1;36m");
    printf("\n\t\t\t\t <---------------- Advanced C Programming project ---------------->");
    printf("\033[0m");
    printf("\033[0;34m");
    printf("\n\t\t\t\t\t**************************************************\n");
    printf("\033[0m");
    printf("\033[0;34m");
    printf("\033[0m");
    printf("\033[1;36m");
    printf("\033[0m");
    printf("\033[1;32m");
    printf("\n\t\t\t\t ********** Welcome to the BANKING MANAGEMENT SYSTEM **********\n\n");
    printf("\033[0m");

    do
    {
        printf("\033[0;32m");
        printf("\n\t\t\t-------------------------");
        printf("\033[0m");
        printf("\033[1;32m");
        printf("\n\t\t\t  Banking System Menu :\n");
        printf("\033[0m");
        printf("\033[0;32m");
        printf("\t\t\t-------------------------");

        printf("\033[0m");
        printf("\033[1;34m");
        printf("\n\t\t\t## Press '1' to ADD accounts.\n");
        printf("\t\t\t## Press '2' to DISPLAY records.\n");
        printf("\t\t\t## Press '3' to DEPOSIT amount.\n");
        printf("\t\t\t## Press '4' to WITHDRAW amount.\n");
        printf("\t\t\t## Press '5' to SEARCH a record.\n");
        printf("\t\t\t## Press '6' to DELETE a new account.\n");
        printf("\t\t\t## Press '0' to EXIT from application\n");
        printf("\033[0m");
        printf("\033[1;35m");
        printf("\n\t\t\tENTER YOUR CHOICE from --> (0-6) :   ");
        scanf("\t\t%d", &ch);
        switch (ch)
        {
            case 1:
                add_acc(obj, n);
                n++;
                break;

            case 2:
                display(obj);
                break;

            case 3:
                printf("\033[0m");
                printf("\n\t\t\t\t\tEnter account number : ");
                scanf("%d", &account_no);
                printf("\t\t\t\t\tEnter amount to deposit : ");
                scanf("%d", &amount);
                deposit(obj, account_no, amount);
                break;

            case 4:
                printf("\033[0m");
                printf("\n\t\t\t\t\tEnter account number : ");
                scanf("%d", &account_no);
                printf("\t\t\t\t\tEnter amount to withdraw : ");
                scanf("%d", &amount);
                withdraw(obj, account_no, amount);
                break;

            case 5:
                ptr=obj;
                printf("\033[0m");
                printf("\n\t\t\t\t\tEnter account number to search : ");
                scanf("%d", &account_no);
                pos = search(obj, account_no);
                if (pos ==  - 1)
                {
                    printf("\033[0m");
                    printf("\033[1;31m");
                    printf("\n\t\t\t\t\t--> This Record is ** NOT FOUND **");
                }
                else
                {
                    ptr=ptr+pos;
                    printf("\033[0m");
                    printf("\033[0;33m");
                    printf("\n\t\t\t\t\tA/c Number: %d\n\t\t\t\t\tName: %s\n\t\t\t\t\tBalance: %d\n",ptr->acc_no, ptr->name, ptr->bal);
                }
                break;

            case 6:
                printf("\033[0m");
                printf("\n\t\t\t\t\tEnter account number to be deleted : ");
                scanf("%d", &account_no);
                del(obj, account_no);

                break;

        }
    }

    while (ch != 0);
    return 0;
}








