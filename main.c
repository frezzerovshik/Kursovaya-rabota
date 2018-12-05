#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LEN 100
#define MAXLEN 1000
#define YES 1
#define NO 0
#define CATEGORIES 8
typedef struct sNode
{
    int id;
    char name[LEN];
    char category[LEN];
    int  cost;
    struct sNode *next;
}Node;
int showMenu()
{
    int choice;
    printf("    1 - Add product\n");
    printf("    2 - Editing record \n");
    printf("    3 - Delete record\n");
    printf("    4 - Display the database on the screen in alphabetical order by product category or product name\n");
    printf("    5 - Selection of the 'minimum basket' for a given list of products\n");
    printf("\n              Press 0 and Enter if you want to quit.\n");
    scanf("%d", &choice);
    return choice;
}
Node* init(int a)
{
    Node *lst;
    lst = (Node*)malloc(sizeof(Node));
    lst->id = a;
    lst->next = NULL;
    return(lst);
}
Node * deleteHead(Node *head)
{
    Node *temp;
    temp = head->next;
    free(head);
    return(temp);
}
void deleteNode(Node *lst, Node *head)
{
    Node *temp;
    temp = head;
    while (temp->next != lst)
    {
        temp = temp->next;
    }
    temp->next = lst->next;
    free(lst);
}
void freeStruct(Node ** head)
{
    Node * current = *head;
    Node * next = NULL;
    do
    {
        next = current->next;
        free(current);
        current = next;
    } while (current != NULL);
    free(current);
}
Node* Appendlist(Node** headRef)
{
    Node* current = *headRef;
    Node* lst;
    lst = (Node*)malloc(sizeof(Node));
    lst->next = NULL;
    if (current == NULL) {
        *headRef = lst;
    }
    else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = lst;
    }
    return(lst);
}
void structFor(Node** headRef, int structType, int count)
{
    Node* current;
    Node* next;
    int noSwap;
    int iBuf;
    char cBuf[MAXLEN];
    switch (structType)
    {
        case 1:
            for (int i = count - 1; i >= 0; i--)
            {
                current = *headRef;
                next = current->next;
                noSwap = 1;
                for (int j = 0; j < i; j++)
                {
                    if (strcmp(current->name, next->name) > 0)
                    {
                        iBuf = current->id;
                        current->id = next->id;
                        next->id = iBuf;
                        strcpy(cBuf, current->name);
                        strcpy(current->name, next->name);
                        strcpy(next->name, cBuf);
                        strcpy(cBuf, current->category);
                        strcpy(current->category, next->category);
                        strcpy(next->category, cBuf);
                        iBuf = current->cost;
                        current->cost = next->cost;
                        next->cost = iBuf;
                        noSwap = 0;
                    }
                    current = current->next;
                    next = current->next;
                }
                if (noSwap == 1)
                    break;
            }
            break;
        case 2:
            for (int i = count - 1; i >= 0; i--)
            {
                current = *headRef;
                next = current->next;
                noSwap = 1;
                for (int j = 0; j < i; j++)
                {
                    if (strcmp(current->category, next->category) > 0)
                    {
                        iBuf = current->id;
                        current->id = next->id;
                        next->id = iBuf;
                        strcpy(cBuf, current->name);
                        strcpy(current->name, next->name);
                        strcpy(next->name, cBuf);
                        strcpy(cBuf, current->category);
                        strcpy(current->category, next->category);
                        strcpy(next->category, cBuf);
                        iBuf = current->cost;
                        current->cost = next->cost;
                        next->cost = iBuf;
                        noSwap = 0;
                    }
                    current = current->next;
                    next = current->next;
                }
                if (noSwap == 1)
                    break;
            }
            break;
        default:
            break;
    }
}
void inputData(Node** headRef, int *countItemsRet, int *itemNumRet)
{
    FILE *fpin;
    FILE *finit;
    int dataNum;
    int itemNum = 0;
    int inItem = NO;
    int countItems = 0;
    int i = 0;
    char line[MAXLEN];
    Node* item_ptr = NULL;
    fpin = fopen("base.txt", "r");
    if (fpin == NULL)
    {
        finit = fopen("base.txt", "w");
        fclose(finit);
        fpin = fopen("base.txt", "r");
    }
    fscanf(fpin, "%d\n", &countItems);
    while (!feof(fpin))
    {
        fscanf(fpin, "%s\n", line);
        if (line == NULL)
            break;
        if (*line == '(')
        {
            inItem = YES;
            itemNum++;
            if (itemNum == 1)
            {
                item_ptr = *headRef;
            }
            else
            {
                item_ptr = Appendlist(&(*headRef));
            }
            dataNum = 0;
            continue;
        }
        if (*line == ')')
        {
            inItem = NO;
            continue;
        }
        if (inItem)
        {
            i = -1;
            ++dataNum;
            switch (dataNum)
            {
                case 1:
                    item_ptr->id = atoi(line);
                    break;
                case 2:
                    do
                    {
                        i++;
                        item_ptr->category[i] = line[i];
                    } while (line[i] != '\0');
                    break;
                case 3:
                    do
                    {
                        i++;
                        item_ptr->name[i] = line[i];
                    } while (line[i] != '\0');
                    break;
                case 4:
                    item_ptr->cost = atoi(line);
                    break;
            }
        }
    }
    fclose(fpin);
    *itemNumRet = itemNum;
    *countItemsRet = countItems;
}
void recordData(Node** headRef, int itemNum)
{
    FILE *fpin;
    Node* current = *headRef;
    fpin = fopen("base.txt", "w");
    fprintf(fpin, "%d\n", itemNum);
    while (current != NULL)
    {
        fprintf(fpin, "(\n");
        fprintf(fpin, "%d\n", current->id);
        fprintf(fpin, "%s\n", current->category);
        fprintf(fpin, "%s\n", current->name);
        fprintf(fpin, "%d\n", current->cost);
        fprintf(fpin, ")\n");
        current = current->next;
    }
    fclose(fpin);
}
int main()
{
    Node* HeadPointer = init(0);
    Node* ItemPointer = NULL;
    char WantedName[LEN];
    int itemNum;
    int countItems;
    int i = 0;
    int need_menu;
    int need_cost;
    int need_item;
    int need_category;
    int need_showCategory;
    char categories[CATEGORIES][100] = { "Fruits","Meat", "Milk", "Drinks", "Candy", "Vegetables", "Bread", "Bakery" };
    int need_basketCategories[CATEGORIES + 1];
    inputData(&HeadPointer, &countItems, &itemNum);
    
    do
    {
        need_menu = showMenu();
        switch (need_menu)
        {
            case 1:
                printf("1 - Fruits\n");
                printf("2 - Meat\n");
                printf("3 - Milk\n");
                printf("4 - Drinks\n");
                printf("5 - Candy\n");
                printf("6 - Vegetables\n");
                printf("7 - Bread\n");
                printf("8 - Bakery\n");
                printf("Select product category : ");
                scanf("%d", &need_category);
                printf("Enter the item name : ");
                getchar();
                fgets(WantedName, LEN, stdin);
                getchar();
                printf("Enter the price of the item : ");
                scanf("%d", &need_cost);
                countItems++;
                if (itemNum == 0)
                {
                    ItemPointer = HeadPointer;
                }
                else
                {
                    ItemPointer = Appendlist(&HeadPointer);
                }
                ItemPointer->id = countItems;
                ItemPointer->cost = need_cost;
                i = -1;
                do
                {
                    i++;
                    ItemPointer->name[i] = WantedName[i];
                } while (WantedName[i] != '\0');
                i = -1;
                do
                {
                    i++;
                    ItemPointer->category[i] = categories[need_category - 1][i];
                } while (categories[need_category - 1][i] != '\0');
                itemNum++;
                break;
            case 2:
               
                if (!itemNum)
                {
                    printf("There is no items here\n");
                    
                    break;
                }
                printf("Select the item you want to change : \n");
                ItemPointer = HeadPointer;
                i = 1;
                while (ItemPointer != NULL)
                {
                    printf("%d - %s\n", i, ItemPointer->name);
                    i++;
                    ItemPointer = ItemPointer->next;
                }
                ItemPointer = HeadPointer;
                scanf("%d", &need_item);
                for (i = 0; i < need_item - 1; i++)
                {
                    ItemPointer = ItemPointer->next;
                }
                printf("Old item type : %s\n||||||||||\n", ItemPointer->category);
                for (i = 0; i < CATEGORIES; i++)
                {
                    printf("%d %s\n", i + 1, &categories[i]);
                }
                printf("Enter a new category of product : ");
                scanf("%d", &need_category);
                printf("Old product name : %s\nEnter new product name : ", ItemPointer->name);
                getchar();
                fgets(WantedName, LEN, stdin);
                getchar();
                printf("Old cost: %d\nEnter new cost : ", ItemPointer->cost);
                scanf("%d", &need_cost);
                ItemPointer->cost = need_cost;
                i = -1;
                do
                {
                    i++;
                    ItemPointer->name[i] = WantedName[i];
                } while (WantedName[i] != '\0');
                i = -1;
                i = -1;
                do
                {
                    i++;
                    ItemPointer->category[i] = categories[need_category - 1][i];
                } while (categories[need_category - 1][i] != '\0');
                
                break;
            case 3:
                if (!itemNum)
                {
                    printf("There is no items here\n");
                   
                    break;
                }
                printf("Select the item you want to remove : \n");
                ItemPointer = HeadPointer;
                i = 1;
                while (ItemPointer != NULL)
                {
                    printf("%d %s\n", i, ItemPointer->name);
                    i++;
                    ItemPointer = ItemPointer->next;
                }
                scanf("%d", &need_item);
                ItemPointer = HeadPointer;
                for (i = 0; i < need_item - 1; i++)
                {
                    ItemPointer = ItemPointer->next;
                }
                if (need_item == 1)
                {
                    HeadPointer = deleteHead(ItemPointer);
                }
                else
                {
                    deleteNode(ItemPointer, HeadPointer);
                }
                itemNum--;
                if (!itemNum)
                {
                    HeadPointer = init(0);
                }
                break;
            case 4:
               
                if (!itemNum)
                {
                    printf("There is no items here\n");
                    break;
                }
                printf("Choose sorting method: \n");
                printf("1 - Name\n2 - Category\n");
                scanf("%d", &need_showCategory);
                
                structFor(&HeadPointer, need_showCategory, itemNum);
                ItemPointer = HeadPointer;
                i = 1;
                while (ItemPointer != NULL)
                {
                    printf("      <%d>      \n", i);
                    printf("ID: %d\n", ItemPointer->id);
                    printf("Category: %s\n", ItemPointer->category);
                    printf("Name: %s\n", ItemPointer->name);
                    printf("Cost: %d\n", ItemPointer->cost);
                    i++;
                    ItemPointer = ItemPointer->next;
                }
                break;
            case 5:
                if (!itemNum)
                {
                    printf("There is no items here\n");
                    break;
                }
                for (i = 0; i < CATEGORIES; i++)
                {
                    printf("%d %s\n", i + 1, categories[i]);
                }
                printf("Select the types of goods for the minimum basket.\nEnter by one type.When finished, enter 0\n");
                i = 0;
                do
                {
                    scanf("%d", &need_basketCategories[i]);
                    if (i)
                    {
                        for (int j = 0; j < i; j++)
                            if (need_basketCategories[j] == need_basketCategories[i])
                            {
                                printf("This type of product is already in the basket. Choose a different one or finish the selection.\n");
                                i--;
                            }
                    }
                    i++;
                } while (need_basketCategories[i - 1]);
                i = 0;
                while (need_basketCategories[i])
                {
                    int max = 100000;
                    Node*max_ptr = NULL;
                    ItemPointer = HeadPointer;
                    while (ItemPointer != NULL)
                    {
                        if (!strcmp(ItemPointer->category, categories[need_basketCategories[i] - 1]))
                        {
                            if (ItemPointer->cost < max)
                            {
                                max = ItemPointer->cost;
                                max_ptr = ItemPointer;
                            }
                        }
                        ItemPointer = ItemPointer->next;
                    }
                    i++;
                    if (!(max_ptr == NULL))
                    {
                        printf("      <%d>      \n", i);
                        printf("ID: %d\n", max_ptr->id);
                        printf("Category: %s\n", max_ptr->category);
                        printf("Name: %s\n", max_ptr->name);
                        printf("Cost: %d\n", max_ptr->cost);
                    }
                }
                break;
            default:
                break;
        };
    } while (need_menu);
    if (itemNum)
    {
        recordData(&HeadPointer, countItems);
    }
    freeStruct(&HeadPointer);
    return 0;
}
