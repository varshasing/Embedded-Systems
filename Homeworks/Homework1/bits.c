#include "bits.h"

uint32_t ConvertEndianness(uint32_t little_endian)
{
    /* 8 bits in a byte, bitshift byte to LSB, bitmask, bitwise OR and shifts */
    uint32_t big_endian = 0;
    uint32_t bitmask = 255;
    uint32_t temp = 0;
    int i;

    for(i = 0; i < 4; i++)
    {
        big_endian <<= 8;
        temp = little_endian >> (i*8);  // shift
        temp = temp&bitmask;            // bitmask
        big_endian = temp | big_endian; // bitwise OR
    }
    return big_endian;    
}

void EncryptXOR(struct Node** node, char key[5])
{
    /* convert to ascii, XOR with masking to assign characters */
    uint32_t encrypted = 0;
    uint32_t temp = 0;      // also mask
    int i;

    /* allocate space to node value */
    (*node)->ascii = (char*)malloc(5);

    /* typecasting and bitshifts to key */
    for(i = 0; i < 4; i++)
    {
        temp <<= 8;
        temp = temp | (uint32_t)key[i];
    }

    /* XOR logic: (Xx~Y) + (~XxY) */
    encrypted = (*node)->big_endian ^ temp;
    
    temp = 255;                         // mask for 8 bits
    for(i = 0; i < 4; i++)
    {
        (*node)->ascii[3-i] = (char) (encrypted & temp);
        encrypted >>= 8;
    }
    (*node)->ascii[4] = '\0';
    return;
}

uint32_t stod(char* line)
{
    uint32_t decimal = 0;
    int i;

    /* convert ascii number to unsigned 32 bit integer */
    for(i = 0; i < strlen(line); i++)
    {
        if(line[i] == '\n' || line[i] == '\0' || (int) line[i] == 13)
        {
            break;
        }
        else if((int) line[i] - 48 >= 0 && (int) line[i] - 48 <= 9)
        {
            decimal = decimal * 10 + (int) line[i] - 48;
        }
        else
        {
            printf("ERROR: INVALID CHARACTER IN FILE: %d\n", (int) line[i]);
            return 911;
        }
    }
    return decimal;
}

void SortLinkedList(struct LinkedList** list, struct Node** node)
{
    /* no nodes in list, first entry */
    if((*list)->head == NULL)
    {
        (*list)->head = *node;
        (*list)->tail = *node;
        (*list)->size = 1;
        return;
    }
    
    struct Node* current = (*list)->head;
    struct Node* previous = NULL;

    /* go through list */
    while(current != NULL)
    {
        /* compare ASCII values */
        if(strcmp((*node)->ascii, current->ascii) < 0)
        {
            /* inserting at head */
            if(previous == NULL)
            {
                (*node)->next = current;
                (*list)->head = *node;
                (*list)->size++;
            }
            else
            {
                previous->next = *node;
                (*node)->next = current;
                (*list)->size++;
            }
            return;
        }
        previous = current;
        current = current->next;
    }
    /* inserting at end */
    if(current == NULL)
    {
        previous->next = *node;
        (*list)->tail = *node;
        (*list)->size++;
    }
    return;
}