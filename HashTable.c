#include <stdio.h>
#include <stdlib.h>
#define TABLE_SIZE 10
#define MAX_FACES 4

typedef struct PITEntry
{
    unsigned int fingerprint;
    unsigned int expiration;
    unsigned int faces;
    int occupied;
} PITEntry;

PITEntry hashTable[TABLE_SIZE];

unsigned int hashFunction(unsigned int fingerprint) 
{
    return fingerprint % TABLE_SIZE;
}

void insertPIT(unsigned int fingerprint, unsigned int expiration, unsigned int face)
{
    unsigned int index = hashFunction(fingerprint);

    while (hashTable[index].occupied == 1) 
    {
        if (hashTable[index].fingerprint == fingerprint) 
        {
            hashTable[index].faces |= (1 << face);
            if (hashTable[index].expiration < expiration) {
                hashTable[index].expiration = expiration;
            }
            printf("Updated fingerprint %u at index %u\n", fingerprint, index);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }

    hashTable[index].fingerprint = fingerprint;
    hashTable[index].expiration = expiration;
    hashTable[index].faces = (1 << face);
    hashTable[index].occupied = 1;
    printf("Inserted fingerprint %u at index %u\n", fingerprint, index);
}

int searchPIT(unsigned int fingerprint)
{
    unsigned int index = hashFunction(fingerprint);
    while (hashTable[index].occupied == 1)
    {
        if (hashTable[index].fingerprint == fingerprint)
        {
            return index;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    return -1;
}

void printPIT()
{
    printf("\nPIT Content:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hashTable[i].occupied)
        {
            printf("Index %d: Fingerprint = %u, Expiration = %u, Faces = %u\n",
                   i, hashTable[i].fingerprint, hashTable[i].expiration, hashTable[i].faces);
        }
    }
}

int main()
{
    int numEntries;
    unsigned int fingerprint, expiration, face;

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hashTable[i].occupied = 0;
    }

    printf("Enter the number of entries to insert into PIT: ");
    scanf("%d", &numEntries);

    for (int i = 0; i < numEntries; i++)
    {
        printf("\nEnter fingerprint for entry %d: ", i + 1);
        scanf("%u", &fingerprint);

        printf("Enter expiration time for fingerprint %u: ", fingerprint);
        scanf("%u", &expiration);

        printf("Enter face number (0 to 3) for fingerprint %u: ", fingerprint);
        scanf("%u", &face);

        if (face < MAX_FACES) 
        {
            insertPIT(fingerprint, expiration, face);
        }
        else
        {
            printf("Invalid face number! Face must be between 0 and 3.\n");
        }
    }

    printf("\nEnter a fingerprint to search: ");
    scanf("%u", &fingerprint);
    int index = searchPIT(fingerprint);
    if (index != -1)
    {
        printf("\nFound fingerprint %u at index %d\n", fingerprint, index);
    }
    else
    {
        printf("\nFingerprint %u not found\n", fingerprint);
    }

    printPIT(); 
    return 0;
}
