#ifndef BITS_H
#define BITS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include <stdarg.h>
#include <ctype.h>
#include <limits.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/types.h>
#include <inttypes.h>
#include <stdbool.h>

/* reads an input file containing a list of unsigned little-endian 
 * decimal integers (one integer per line) and prints three columns
 * to an output file. The first column shouuld be the original decimal
 * integer. The second colun shouuld have a hexadecimal value,
 * corresponding to the number in the input file, but this time converted
 * into big-endian format (consider byte-endianness, not bit-endianness).
 * The third columns should show the ASCII representation (4 letters, each
 * letter is 8-bits long) of each big-endian number, encrypted using XOR
 * encryption with a user-provided 4-letter key.
*/

struct Node
{
    uint32_t decimal;
    uint32_t big_endian;
    char* ascii;
    struct Node* next;
} Node;

struct LinkedList
{
    struct Node* head;
    struct Node* tail;
    int size;
} LinkedList;

/* converts a little-endian number into big-endian, byte-endianness */
uint32_t ConvertEndianness(uint32_t little_endian);

/* performs XOR encription */
void EncryptXOR(struct Node** newNode, char key[5]);

/* self defined function, converts line to uint32_t */
uint32_t stod(char* line);

/* self defined function, sorts linked list in ASCII alphabetical order*/
void SortLinkedList(struct LinkedList** list, struct Node** node);

#endif