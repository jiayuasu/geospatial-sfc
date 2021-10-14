#include <iostream>
#include "hilbert.h"
int main() {
    std::cout << "Hello, World!" << std::endl;
    unsigned i;
    unsigned c1[100], c2[100], pt[100];
    unsigned nDims, nBytes = 4;
    int stat, findPrev;
    printf("Enter nDims: " );
    scanf("%u", &nDims);

    printf("Enter 1st box corner: ");
    for (i = 0; i < nDims; ++i)
        scanf("%u", &c1[i]);
    printf("Enter 2nd box corner: ");
    for (i = 0; i < nDims; ++i)
        scanf("%u", &c2[i]);
    printf("Enter point: ");
    for (i = 0; i < nDims; ++i)
        scanf("%u", &pt[i]);
    printf("Find prev?: ");
    scanf("%d", &findPrev);

    stat =  hilbert_nextinbox(nDims, nBytes, 8*nBytes, findPrev, c1, c2, pt);

    if (stat)
        for (i = 0; i < nDims; ++i)
            printf("%u ", c1[i]);
    else
        printf("No such point");

    printf("\n");
    return 0;
}