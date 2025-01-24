#include <stdio.h>
#include "bits.h"

#define BUFFER_SIZE 15                  // 32 bit integer, newline, null terminator

int main(int argc, char* argv[])
{
    /* error checking */
    if(argc != 4)
    {
        printf("INCORRECT NUMBER OF VARIABLES");
        return(-1);
    }

    /* read input file */
    FILE* input = fopen(argv[1], "r");
    char line[BUFFER_SIZE];
    
    if(input == NULL)
    {
        printf("ERROR OPENING FILE");
        return(-1);
    }

    struct LinkedList* list = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    struct Node* newNode = NULL;
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;

    /* sort LL as inserting */
    while(fgets(line, sizeof(line), input) != NULL)
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->next = NULL;
        newNode->decimal = stod(line);
        newNode->big_endian = ConvertEndianness(newNode->decimal);
        EncryptXOR(&newNode, argv[3]);
        SortLinkedList(&list, &newNode);
    }
    fclose(input);

    newNode = list->head;

    /* print to output file */
    FILE* output = fopen(argv[2], "w");
    while(newNode != NULL)
    {
        fprintf(output, "%" PRIu32 "\t%08x\t%s\n\n", newNode->decimal, newNode->big_endian, newNode->ascii);
        newNode = newNode->next;
    }
    fclose(output);

    return 0;
}

/*  ./BitApp input.txt output.txt qemu */
