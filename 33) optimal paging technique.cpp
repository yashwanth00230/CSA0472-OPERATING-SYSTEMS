#include <stdio.h>
#include <stdbool.h>
#define MAX_PAGES 10
#define MAX_FRAMES 3
void optimal(int pages[], int n, int futureAccess[], int m);
int main() {
    int n, m, i, j;
    int pages[MAX_PAGES];
    int futureAccess[MAX_PAGES];
    printf("Enter the number of pages: ");
    scanf("%d", &n);
    printf("Enter the sequence of pages: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }
    printf("Enter the number of future accesses: ");
    scanf("%d", &m);
    printf("Enter the future page accesses: ");
    for (i = 0; i < m; i++) {
        scanf("%d", &futureAccess[i]);
    }
    optimal(pages, n, futureAccess, m);
    return 0;
}
int findOptimalIndex(int pages[], int frames[], int start, int end) {
    int index = -1;
    int farthest = start;
    for (int i = 0; i < MAX_FRAMES; i++) {
        int j;
        for (j = start; j < end; j++) {
            if (frames[i] == pages[j]) {
                if (j > farthest) {
                    farthest = j;
                    index = i;
                }
                break;
            }
        }
        if (j == end) {
            return i;  
        }
    }
    return index;
}
void optimal(int pages[], int n, int futureAccess[], int m) {
    int frames[MAX_FRAMES] = {-1, -1, -1};  
    int pageFaults = 0;
    printf("\nPage\tFrames\n");
    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int isPageFault = true;
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                isPageFault = false; 
                break;
            }
        }
        if (isPageFault) {
            printf("%d\t", page);
            int index = findOptimalIndex(pages, frames, i + 1, n);
            if (index != -1) {
                if (frames[index] != -1) {
                    printf("%d replaced by %d\n", frames[index], page);
                } else {
                    printf("None\n");
                }
                frames[index] = page;
                pageFaults++;
            }
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
