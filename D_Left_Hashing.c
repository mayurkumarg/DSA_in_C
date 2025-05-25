#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define SUBTABLES 4
#define MAX_FACES 4
typedef struct PITEntry {
    unsigned int fingerprint; 
    unsigned int expiration;  
    unsigned int faces;       
    int occupied;            
} PITEntry;

PITEntry dLeftTable[SUBTABLES][TABLE_SIZE];
unsigned int hashFunction(unsigned int fingerprint, int subtableIndex) {
    return (fingerprint + subtableIndex) % TABLE_SIZE;
}
void dLeftInsert(unsigned int fingerprint, unsigned int expiration, unsigned int face) {
    if (face >= MAX_FACES) {
        printf("Error: Face index %u exceeds the maximum allowed faces (%d).\n", face, MAX_FACES - 1);
        return;
    }

    int bestSubtable = -1;
    unsigned int bestIndex = 0;
    for (int subtable = 0; subtable < SUBTABLES; subtable++) {
        unsigned int index = hashFunction(fingerprint, subtable);
        if (dLeftTable[subtable][index].occupied == 0) {
            bestSubtable = subtable;
            bestIndex = index;
            break;
        }
    }

    if (bestSubtable == -1) {
        printf("Error: No available slot for fingerprint %u.\n", fingerprint);
        return;
    }
    dLeftTable[bestSubtable][bestIndex].fingerprint = fingerprint;
    dLeftTable[bestSubtable][bestIndex].expiration = expiration;
    dLeftTable[bestSubtable][bestIndex].faces |= (1 << face);
    dLeftTable[bestSubtable][bestIndex].occupied = 1;

    printf("Inserted fingerprint %u at subtable %d, index %u with face %u\n",
           fingerprint, bestSubtable, bestIndex, face);
}
int dLeftSearch(unsigned int fingerprint) {
    for (int subtable = 0; subtable < SUBTABLES; subtable++) {
        unsigned int index = hashFunction(fingerprint, subtable);
        if (dLeftTable[subtable][index].occupied == 1 &&
            dLeftTable[subtable][index].fingerprint == fingerprint) {
            return subtable; 
        }
    }
    return -1; 
}
void printDLeftTable() {
    printf("\nD-Left Hash Table Content:\n");
    for (int subtable = 0; subtable < SUBTABLES; subtable++) {
        printf("Subtable %d:\n", subtable);
        for (unsigned int index = 0; index < TABLE_SIZE; index++) {
            if (dLeftTable[subtable][index].occupied) {
                printf(" Index %u: Fingerprint = %u, Expiration = %u, Faces = %u (bit vector)\n",
                       index, dLeftTable[subtable][index].fingerprint,
                       dLeftTable[subtable][index].expiration,
                       dLeftTable[subtable][index].faces);
            }
        }
    }
}

int main() {
    for (int subtable = 0; subtable < SUBTABLES; subtable++) {
        for (int i = 0; i < TABLE_SIZE; i++) {
            dLeftTable[subtable][i].occupied = 0;
        }
    }

    unsigned int fingerprint, expiration, face;
    int numEntries;
    printf("Enter number of PIT entries to insert: ");
    scanf("%d", &numEntries);
    for (int i = 0; i < numEntries; i++) {
        printf("Enter fingerprint (number) for entry %d: ", i + 1);
        scanf("%u", &fingerprint);
        printf("Enter expiration time (in seconds) for entry %d: ", i + 1);
        scanf("%u", &expiration);
        printf("Enter face index (0 to 3) for entry %d: ", i + 1);
        scanf("%u", &face);
        dLeftInsert(fingerprint, expiration, face);
    }
    unsigned int checkFingerprint;
    printf("Enter fingerprint to search for: ");
    scanf("%u", &checkFingerprint);
    int subtableIndex = dLeftSearch(checkFingerprint);
    if (subtableIndex != -1) {
        printf("\nFound fingerprint %u in subtable %d\n", checkFingerprint, subtableIndex);
    } else {
        printf("\nFingerprint %u not found\n", checkFingerprint);
    }
    printDLeftTable();

    return 0;
}