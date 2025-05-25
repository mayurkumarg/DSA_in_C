#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define MAX_FACES 4

typedef struct PITEntry {
    unsigned int fingerprint;
    unsigned int expiration;
    unsigned int faces;
    int occupied;
} PITEntry;

PITEntry hashTable[TABLE_SIZE];

unsigned int hashFunction(unsigned int fingerprint) {
    return fingerprint % TABLE_SIZE;
}

void insertPIT(unsigned int fingerprint, unsigned int expiration, unsigned int face) {
    unsigned int index = hashFunction(fingerprint);
    while (hashTable[index].occupied == 1) {
        index = (index + 1) % TABLE_SIZE;
    }
    hashTable[index].fingerprint = fingerprint;
    hashTable[index].expiration = expiration;
    hashTable[index].faces = (1 << face);
    hashTable[index].occupied = 1;
    printf("Inserted fingerprint %u at index %u with face %u\n", fingerprint, index, face);
}

void lazyDelete(unsigned int fingerprint) {
    unsigned int index = hashFunction(fingerprint);
    while (hashTable[index].occupied == 1) {
        if (hashTable[index].fingerprint == fingerprint) {
            hashTable[index].occupied = 0;
            printf("Lazy deleted fingerprint %u at index %u\n", fingerprint, index);
            return;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    printf("Fingerprint %u not found for deletion\n", fingerprint);
}

int searchPIT(unsigned int fingerprint) {
    unsigned int index = hashFunction(fingerprint);
    while (hashTable[index].occupied == 1) {
        if (hashTable[index].fingerprint == fingerprint) {
            return index;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    return -1;
}

void printPIT() {
    printf("\nPIT Content:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i].occupied == 1) {
            printf("Index %d: Fingerprint = %u, Expiration = %u, Faces = %u (bit vector)\n",
                   i, hashTable[i].fingerprint, hashTable[i].expiration, hashTable[i].faces);
        } else if (hashTable[i].occupied == 0) {
            printf("Index %d: Deleted entry\n", i);
        } else {
            printf("Index %d: Empty slot\n", i);
        }
    }
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].occupied = 0;
    }

    int choice;
    unsigned int fingerprint, expiration, face;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Insert PIT entry\n");
        printf("2. Delete PIT entry\n");
        printf("3. Search for fingerprint in PIT\n");
        printf("4. Print PIT\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter fingerprint: ");
                scanf("%u", &fingerprint);
                printf("Enter expiration time: ");
                scanf("%u", &expiration);
                printf("Enter face index (0 to 3): ");
                scanf("%u", &face);
                insertPIT(fingerprint, expiration, face);
                break;

            case 2:
                printf("Enter fingerprint to delete: ");
                scanf("%u", &fingerprint);
                lazyDelete(fingerprint);
                break;

            case 3:
                printf("Enter fingerprint to search: ");
                scanf("%u", &fingerprint);
                int index = searchPIT(fingerprint);
                if (index != -1) {
                    printf("Found fingerprint %u at index %d\n", fingerprint, index);
                } else {
                    printf("Fingerprint %u not found\n", fingerprint);
                }
                break;

            case 4:
                printPIT();
                break;

            case 5:
                printf("Exiting program.\n");
                exit(0);

            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
