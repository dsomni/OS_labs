#include <stdio.h>
#include <stdlib.h>

struct node
{
    struct node *next;
    struct node *prev;
    int value;
};

struct DLL_int
{
    struct node head;
    struct node tail;
};

void print_DLL_int(struct node *head, struct node *tail){
    struct node *iterator = head->next;
    while (iterator != tail){
        printf("%d ", iterator->value);
        iterator = iterator->next;
    }
    printf("\n");
}

void append_node_DLL_int(struct node *head, struct node *tail, int value){
    struct node* new_node = malloc(sizeof(struct node));
    new_node->value = value;

    tail->prev->next = new_node;
    new_node->prev = tail->prev;
    tail->prev = new_node;
    new_node->next = tail;
}

void delete_node_DLL_int(struct node *head, struct node *tail, int value){
    struct node *iterator = head->next;
    while (iterator != tail){
        if (iterator->value == value){
            iterator->next->prev = iterator->prev;
            iterator->prev->next = iterator->next;
            free(iterator);
            return;
        }
        iterator = iterator->next;
    }
}

void insert_node_DLL_int(struct node *head, struct node *tail, int value, int existing_value){
    struct node *iterator = head->next;
    while (iterator != tail){
        if (iterator->value == existing_value){
            struct node * new_node = malloc(sizeof(struct node));
            new_node->value = value;
            new_node->prev = iterator;
            new_node->next = iterator->next;
            iterator->next->prev = new_node;
            iterator->next = new_node;
            return;
        }
        iterator = iterator->next;
    }
}

int main()
{

    struct DLL_int list;
    list.head.next = &list.tail;

    list.tail.prev = &list.head;

    printf("Commands:\n");
    printf("\tp\t|\tprint list\n");
    printf("\ta V\t|\tadd new node with value V to the tail\n");
    printf("\td V\t|\tdelete node with value V\n");
    printf("\ti V E\t|\tinsert node with value V after node with value E (if such node does not exist do nothing)\n");
    printf("\te\t|\texit\n");
    printf("\n");

    char instruction;
    int node_value, existing_node_value;
    while (1)
    {
        scanf("%c", &instruction);
        switch (instruction)
        {
        case 'p':
            printf("List:\n");
            print_DLL_int(&list.head, &list.tail);
            break;
        case 'a':
            scanf("%d", &node_value);
            append_node_DLL_int(&list.head, &list.tail, node_value);
            break;
        case 'd':
            scanf("%d", &node_value);
            delete_node_DLL_int(&list.head, &list.tail, node_value);
            break;
        case 'i':
            scanf("%d %d", &node_value, &existing_node_value);
            insert_node_DLL_int(&list.head, &list.tail, node_value, existing_node_value);
            break;
        case 'e':
            return 0;
        default:
            break;
        }
    }

    return 0;
}