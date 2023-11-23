#include <stdio.h>
#define MAX_PAGES 10
#define MAX_FRAMES 3
void lru(int pages[], int n);
int main() {
    int n, i;
    int pages[MAX_PAGES];
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the sequence of pages: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    lru(pages, n);
    return 0;
}
void lru(int pages[], int n) {
    int frames[MAX_FRAMES] = {-1, -1, -1};  
    int pageFaults = 0;
    int usedOrder[MAX_FRAMES] = {0};
    int time = 0;
    printf("\nPage\tFrames\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int isPageFault = 1; 
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                isPageFault = 0; 
                usedOrder[j] = time++;
                break;
            }
        }
        if (isPageFault) {
            printf("%d\t", page);
            int lruIndex = 0;
            for (int j = 1; j < MAX_FRAMES; j++) {
                if (usedOrder[j] < usedOrder[lruIndex]) {
                    lruIndex = j;
                }
            }
            if (frames[lruIndex] != -1) {
                printf("%d replaced by %d\n", frames[lruIndex], page);
            } else {
                printf("None\n");
            }
            frames[lruIndex] = page;
            usedOrder[lruIndex] = time++;
            pageFaults++;
        } else {
            printf("%d\tNone\n", page);
        }
        printf("Frames:\t");
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == -1) {
                printf("Empty ");
            } else {
                printf("%d ", frames[j]);
            }
        }
        printf("\n\n");
    }
    printf("Total Page Faults: %d\n", pageFaults);
}
