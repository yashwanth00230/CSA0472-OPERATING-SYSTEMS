#include <stdio.h>
#include <stdlib.h>
#define MAX_BLOCKS 100
#define BLOCK_SIZE 512
struct IndexBlock {
    int blockPointers[MAX_BLOCKS];
};
void writeToIndexFile(struct IndexBlock indexBlock, const char *filename);
void readFromIndexFile(const char *filename);
int main() {
    int numBlocks, i;
    struct IndexBlock indexBlock;
    printf("Enter the number of blocks: ");
    scanf("%d", &numBlocks);
    for (i = 0; i < numBlocks; i++) {
        printf("Enter the block pointer for block %d: ", i + 1);
        scanf("%d", &indexBlock.blockPointers[i]);
    }
    writeToIndexFile(indexBlock, "index_file.dat");
    readFromIndexFile("index_file.dat");
    return 0;
}
void writeToIndexFile(struct IndexBlock indexBlock, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fwrite(&indexBlock, sizeof(struct IndexBlock), 1, file);
    fclose(file);
}
void readFromIndexFile(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file for reading");
        exit(EXIT_FAILURE);
    }
    struct IndexBlock indexBlock;
    fread(&indexBlock, sizeof(struct IndexBlock), 1, file);
    printf("Block Pointers:\n");
    for (int i = 0; i < MAX_BLOCKS; i++) {
        printf("Block %d: %d\n", i + 1, indexBlock.blockPointers[i]);
    }
    fclose(file);
}
