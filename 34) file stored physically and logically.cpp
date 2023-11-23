#include <stdio.h>
#include <stdlib.h>
#define MAX_RECORDS 100
struct Record {
    int recordNumber;
};
void writeToSequentialFile(struct Record records[], int numRecords, const char *filename);
void readFromSequentialFile(const char *filename);
int main() {
    int numRecords, i;
    struct Record records[MAX_RECORDS];
    printf("Enter the number of records: ");
    scanf("%d", &numRecords);
    for (i = 0; i < numRecords; i++) {
        records[i].recordNumber = i + 1;
    }
    writeToSequentialFile(records, numRecords, "sequential_file.dat");
    readFromSequentialFile("sequential_file.dat");
    return 0;
}
void writeToSequentialFile(struct Record records[], int numRecords, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fwrite(records, sizeof(struct Record), numRecords, file);
    fclose(file);
}
void readFromSequentialFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    struct Record record;
    while (fread(&record, sizeof(struct Record), 1, file) == 1) {
        printf("Record Number: %d\n", record.recordNumber);
    }
    fclose(file);
}
