#include <stdio.h>
#include <stdlib.h>
#include <string.h>
                                   /*ان شاء الله العلامة الكاملة, تم بحمد الله*/

/* Heba mohamad Dababat
 * ID 1230151
 * Section 3
 */

typedef struct Task_Node* List;
typedef struct Task_Node* ptr;
typedef struct Task_Node* Stack;


//making a node for Tasks which consists of Task data and a next pointer to connect the nodes in a list
typedef struct Task_Node {
    int ID;        //task id
    char name[50];      //task name
    char date[50];       //task date
    float duration;               //task duration time
    ptr next;                // a pointer to the next node(task)
}Task_Node;

//functions prototype :___________________________________________________________________________________

// Linked List Creation methods :
List Create_a_List ();

//load a task file method
void Load_File(List L);

// to write in a file :
void Write_File(List L);

//General methods for lists ,Note : down bellow each method is Explained
int IsEmpty(List L);
int IsLast (List L, ptr p);
void Add_New_Task (List L,int ID,char name[],char date[],double duration);
ptr Find_Previous_node(List L,int ID);
void Delete_Task_byID(List L ,int ID);
int Is_ID_exist(List L,int ID);
List Search_by_ID (List L,int ID);
void Print_Tasks (List L);
int Is_Name_exist(List L,char name[]);
List Search_by_Name (List L,char name[]);


// Stack main methods :
void Push (Stack S,int ID,char name[],char date[],double durationTime);
Stack Top(Stack S);
Stack Pop(Stack S);

FILE *output;
//___________________________________________________________________________________________________________
//main method :
int main()
{
    //task data:
    int ID;
    char name[50];
    char date[50];
    float duration;

    //creating the lists and the stacks that i used :
    List TaskS_List = Create_a_List();
    Stack performed_Tasks=Create_a_List();
    List undone_Tasks=Create_a_List();
    Stack performed_CopyList=Create_a_List();

    Stack Popednode;
    ptr p;

    int option=0;   //for the menu
    int option2=0;

    do{
        //the menu :
        printf("\nchoose an option :\n");
        printf("1- Load Tasks File \n");
        printf("2- Add a New Task \n");
        printf("3- Delete a Task \n");
        printf("4- Search for a Task \n");
        printf("5- View Unperformed Tasks \n");
        printf("6- Perform a Task \n");
        printf("7- Undo Last Performed Task \n");
        printf("8- View Performed Tasks \n");
        printf("9- Generate Summary Report \n");
        printf("10- Exit \n");
        scanf("%d",&option);

        switch(option)
        {
        case 1: //load tasks from File
            Load_File(TaskS_List);
            printf("all tasks are loaded : \n");
            break;

        case 2 : // adding a new task to the list
            printf("Enter Task ID :\n");
            scanf("%d",&ID);
            if(Is_ID_exist(TaskS_List,ID)){
                printf("Id is already exist \n");
                break;
            }
            printf("Enter Task name : \n");
            gets(name);
            gets(name);
            printf("Enter Task Date : \n");
            gets(date);
            printf("Enter Task Duration Time : \n");
            scanf("%f",&duration);
            Add_New_Task(TaskS_List,ID,name,date,duration);
            break;

        case 3 : //delete a task based on its ID
            printf("enter the ID for the task you want to delete : ");
            scanf("%d",&ID);
            int check = Is_ID_exist(TaskS_List,ID);
            if(check)
               Delete_Task_byID(TaskS_List,ID);
            else
               printf("ID does not exist \n");
            break;

        case 4 : // Search for a task
            printf("Choose an option 1 or 2 based on what you want to search :\n");
            printf("1- Task ID\n");
            printf("2- Task name \n");
            scanf("%d",&option2);
            if(option2 == 1)
            {
                printf("Enter the Task ID you want to Search for :");
                scanf("%d",&ID);
                if(Is_ID_exist(TaskS_List,ID) ){
                    List l=  Search_by_ID(TaskS_List,ID);
                    printf("Task information your searching for : ID = %d\t.Task Name = %s\t.Task Date = %s\t.Task duration time inn hours = %f\t\n",l->ID,l->name,l->date,l->duration);
                }
                else
                printf("ID does not exist \n");
            }
            else if(option2 == 2){
                printf("Enter Task name you want to Search for : ");
                gets(name);
                gets(name);
                int flag=Is_Name_exist(TaskS_List,name);
                if(flag==1){
                    List l=Search_by_Name(TaskS_List,name);
                    printf("Task information your searching for : ID = %d\t.Task Name = %s\t.Task Date = %s\t.Task duration time inn hours = %f\t\n",l->ID,name,l->date,l->duration);
                }
                else
                printf("there is no such name \n");
            }else
            printf("there is no such option : \n");
            break;

        case 5 : // display unperformed tasks
            printf("Unperformed Tasks : \n");
            Print_Tasks(TaskS_List);
            break;

        case 6 : // mark and remove performed tasks
            printf("enter the ID for the Task you want to perform : \n");
            scanf("%d",&ID);
            if( Is_ID_exist(TaskS_List,ID)){
                List l= Search_by_ID(TaskS_List,ID);
                Push(performed_Tasks,ID,l->name,l->date,l->duration);
                Delete_Task_byID(TaskS_List,ID);
                Delete_Task_byID(undone_Tasks,ID);
            }else{
                printf("such ID does not exist\n");
            }
            break;

        case 7 : //Restore the most undo task (top from the stack)
            if(IsEmpty(performed_Tasks)){
                 printf("empty stack ");
                 break;
            }
            Popednode = Pop(performed_Tasks);
            Add_New_Task(undone_Tasks,Popednode->ID,Popednode->name,Popednode->date,Popednode->duration);
            Add_New_Task(TaskS_List,Popednode->ID,Popednode->name,Popednode->date,Popednode->duration);
            break;

        case 8 : //View Performed Tasks (stack)
            p=Top(performed_Tasks);
            if(IsEmpty(performed_Tasks))
                printf("empty stack");
            while(p!=NULL){
                Popednode =Pop(performed_Tasks);
                printf("ID = %d\t.Task Name = %s\t.Task Date = %s\t.Task duration time inn hours = %f\n",Popednode->ID,Popednode->name,Popednode->date,Popednode->duration);
                Push(performed_CopyList,Popednode->ID,Popednode->name,Popednode->date,Popednode->duration);
                p=Top(performed_Tasks);
            }
            //adding the tasks again to the stack to dont lose any data after poping them
            p=Top(performed_CopyList);
            while(p!=NULL){
                Popednode=Pop(performed_CopyList);
                Push(performed_Tasks,Popednode->ID,Popednode->name,Popednode->date,Popednode->duration); //copying tasks from the copy stack to performed stack
                p=Top(performed_CopyList);
            }
            break;

        case 9: // write in a file :
             //1-  write  unperformed tasks
            output=fopen("Report.txt","w");
            fprintf(output,"unperformed tasks : \n");
            Write_File(TaskS_List);
            //2- write the performed tasks
            fprintf(output,"performed Tasks :\n");
            Write_File(performed_Tasks);
            //3- un done tasks
            fprintf(output,"Undone tasks : \n");
            Write_File(undone_Tasks);

            fclose(output);
            break;

        case 10 :
            return 0;
            break;

        default : printf("No such choice \n");
        }
    }while(option!=10);
}
// a function to check if the list is empty (boolean) return 1 if true
int IsEmpty(List L){
    return L->next==NULL;
}

// a function to check if a node is the last one in the list(return 1 if true)
int IsLast (List L, ptr p){
    return p->next==NULL;
}

// a function to create a linked list
List Create_a_List (){

    List L =(List)malloc(sizeof(struct Task_Node));
    if(L==NULL){
        printf("out of memory ");
        return NULL;
    }
    L->next=NULL;
}

//a function to add elements to the stack
void Push (Stack S,int ID,char name[],char date[],double durationTime){
    ptr p;
    p=(Stack )malloc(sizeof(struct Task_Node));
    if(p==NULL)
        printf("out of space");
    else{
        p->ID=ID;
        strcpy(p->name,name);
        strcpy(p->date,date);
        p->duration=durationTime;
        p->next=S->next;
        S->next=p;

    }
}

// a function returns the top of the stack
Stack Top(Stack S){
    if(!IsEmpty(S))
        return S;
    return 0;
}

// a function to delete and return the top node of the stack
Stack Pop(Stack S){
    ptr firstCell;
    if(IsEmpty(S)){
        printf("empty stack");
    }
    else{
        firstCell=S->next;
        S->next=S->next->next;
        firstCell->next=NULL;
        return firstCell;
    }
}

// a function to add a new task to the list
void Add_New_Task  (List L,int ID,char name[],char date[],double duration){

    ptr node=(struct node*)malloc(sizeof(struct Task_Node));
    node->ID=ID;
    strcpy(node->name,name);
    strcpy(node->date,date);
    node->duration=duration;

    ptr p=L;
    while(p->next !=NULL)
        p=p->next;
    p->next=node;
    node->next=NULL;

}

//a function that loads the data from a file names tasks
void Load_File(List L){

    FILE *input =fopen("tasks.txt","r");
    if(input == NULL)                     //check if the file exist
        printf("cant open file ");
    char Line[100];

    while(fgets(Line,sizeof(Line),input) !=NULL){ //reading from the file line by line and store it in the array

        char *token;
        token=strtok(Line,"#");
        L->ID=atoi(token);
        token=strtok(NULL,"#");
        strcpy(L->name,token);
        token=strtok(NULL,"#");
        strcpy(L->date,token);
        token=strtok(NULL,"#");
        L->duration=atof(token);
        Add_New_Task(L,L->ID,L->name,L->date,L->duration);
    }
    fclose(input);
}

// a function to find the previous node based on id ,to use it in delete
ptr Find_Previous_node(List L,int ID){
    ptr p;
    p=L;
    while(p->next!=NULL && p->next->ID != ID)
        p=p->next;
    return p;
}

//a function to delete a task based in its id
void Delete_Task_byID(List L ,int ID){
    ptr p;
    ptr temp;
    p=Find_Previous_node(L,ID);
    if(!IsLast(L,p)){
        temp=p->next;
        p->next=temp->next;
        free(temp);
    }
}

// a function to check if the id exist
int Is_ID_exist(List L,int ID){
    ptr p;
    p=L->next;
    while(p !=NULL){
        if(p->ID == ID)
            return 1;
        p=p->next;
    }
    return 0;
}

// a function to search on a task based on its ID
List Search_by_ID (List L,int ID){
    ptr p;
    p=L->next;
    while(p!=NULL && p->ID !=ID)
        p=p->next;
    return p;
}

// a function to print the tasks information of the List
void Print_Tasks (List L){
    ptr p;
    p=L;
    if(IsEmpty(L))
        printf("empty list ");
    else{
        do{
        p=p->next;
        printf("ID = %d\t.Task Name = %s\t.Task Date = %s\t.Task duration time inn hours = %f\n",p->ID,p->name,p->date,p->duration);
    }while(!IsLast(L,p));
    printf("\n");
    }
}

//a function to check if the name exist(boolean)
int Is_Name_exist(List L,char name[]){
    ptr p;
    p=L->next;
    int flag=0;
    while(p !=NULL ){
         if( strcmp(p->name,name)==0){
          flag=1;
         }
         p=p->next;
    }
    return flag;
}

// a function to  search for a task based on its name
List Search_by_Name (List L,char name[]){
    ptr p;
    p=L->next;
    while(p!=NULL && strcmp(p->name,name))
        p=p->next;
    return p;
}

// a function to write in a file as a summary of the taskes
void Write_File(List L){
    ptr p =(ptr)L->next;
    while(p !=NULL){
        fprintf(output,"ID = %d\tName = %s\tDate = %s\tDuration time = %f\n",p->ID,p->name,p->date,p->duration);
        p=p->next;
        }
}

                                                      /*ان شاء الله العلامة الكاملة, تم بحمد الله*/
