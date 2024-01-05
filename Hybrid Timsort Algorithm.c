#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <time.h> // Include this header
#include <string.h>
#include <stdbool.h>


struct RunIndices {
    int indices;
    int length;
};
typedef struct RunIndices runIndices;

//
int runMaker(int array[], runIndices runs[], int sizeBig, int minSize, int maxSize);
int* binaryInsert(int firstArray[], int firstSize, int element);
void ascending(int *i, int sizeBig, int minSize, int array[]);
void descendingFunction(int *i, int sizeBig, int minSize, int array[],int *start_descending, bool *descending);

int main(){
    clock_t start, end; // Declare variables to hold the start and end times
    double cpu_time_used;
    start = clock(); // Get the start time
    int array[] = {29, 1065, 848, 818, 805, 795, 747, 734, 712, 710, 674, 664, 646, 627, 609, 586, 532, 506, 392, 343, 316, 285, 223, 149, 107, 73, 28, 9, 4411, 2356, 7150, 1916, 1703, 2901, 2350, 9304, 6563, 2547, 3622, 155, 1831, 3562, 6873, 8507, 7658, 7453, 5518, 4855, 3005, 1322, 7654, 4570, 744, 6119, 3685, 6598, 9117, 6477, 1593, 7621, 6522, 7884, 3025, 6185, 1163, 7858, 4549, 8451, 5863, 5432, 2561, 1042, 3202, 1450, 7431, 698, 4031, 1974, 4641, 3970, 5093, 5213, 9666, 2512, 3323, 8463, 1049, 8227, 8638, 7973, 5552, 1057, 7811, 2076, 4600, 3190, 3574, 71, 3799, 1438, 5799, 5699, 8898, 7863, 7485, 1576, 6399, 2851, 3847, 1023, 5013, 9102, 7735, 554, 156, 2672, 2599, 7283, 6353, 1113, 9855, 4028, 9553, 6730, 5, 9170, 964, 6550, 2108, 9856, 9074, 4889, 5597, 3747, 8196, 8376, 822, 8583, 7373, 2554, 6006, 7519, 1949, 6762, 6801, 2910, 4562, 5654, 6519, 6377, 6665, 6138, 7139, 2732, 4691, 9200, 6000, 6535, 5131, 4416, 5337, 6183, 2393, 3660, 8665, 463, 9150, 8223, 441, 1308, 471, 3645, 9782, 4035, 5527, 9136, 2354, 6266, 4846, 8589, 2264, 5697, 5782, 5951, 3114, 9480, 8370, 9385, 1018, 5442, 2150, 951, 3562, 884, 9, 6762, 6266, 7852, 439};
    int sizeBig=sizeof(array)/sizeof(array[0]);
    int k=sizeBig;
    runIndices runs[70];
    int y;
    for(y = 0; y < 70; y++) {
        runs[y].indices = 0;
        runs[y].length = 0;
    }
    int count=0;
    // Calculate the nearest power of 2 for the number of runs
    while(k != 1) {
        k = k/2;
        count++;
    }
    int numberOfRuns = pow(2, count - 1); // Adjusting count to get the closest lower power of 2
    float avgRunSize = (float)sizeBig / numberOfRuns;
    // Establishing minimum and maximum sizes for the runs
    int minRunSize = floor(avgRunSize);
    int maxRunSize = ceil(avgRunSize); // if there's a fraction, max size is just +1 of the min
    printf("Total elements: %d\n", sizeBig);
    printf("Number of Runs: %d\n", numberOfRuns);
    printf("Average Run Size: %.2f\n", avgRunSize);
    printf("Minimum Run Size: %d\n", minRunSize);
    printf("Maximum Run Size: %d\n", maxRunSize);
    for (int l=0;l<70;l++){
        printf("%d ",runs[l].indices);
        printf("%d ",runs[l].length);
        printf("\n");
    }
    printf("\n");
    int g=runMaker(array,runs,sizeBig,minRunSize,maxRunSize)-1;
    for (int l=0;l<70;l++){
        printf("%d ",runs[l].indices);
        printf("%d ",runs[l].length);
        printf("\n");
    }
    printf("\n");
    int i=0;
    for (int l=0;l<sizeBig;l++){
        if(l==runs[i].indices) {
            printf("    -->At %d\n",runs[i].indices);
            i++;
        }
        printf("%d ",array[l]);
    }
    printf("\n");
    printf("%d", g);
    printf("\n");
    end = clock(); // Get the end time

    // Calculate the time taken in seconds
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", cpu_time_used);
}



int runMaker(int array[], runIndices runs[], int sizeBig, int minSize, int maxSize) {
    int k = 0; // Index for indices array
    int i = 0; // Index for scanning through the main array
    int start_descending=0;
    bool descending=0;
    while (i < sizeBig - 1 || descending==1 ) {
        // Record the start of the current run
        if(i<sizeBig-1){
            runs[k].indices = i;
            if(k==0){
                runs[k].length=k;
            }
            else{
                runs[k].length = runs[k].indices-runs[k-1].indices;
            }
            k++;
        }
        // Determine the direction of the run (initially ascending or descending)
        if (array[i] < array[i+1]) {
            ascending(&i,sizeBig,minSize,array);
        }
        else {
            descendingFunction(&i,sizeBig,minSize,array,&start_descending, &descending);
        }


        // Move to the next potential start of a run
        if(descending==0) i++;
        descending = false; // Reset the flag
    }
    // Handle the last element as the start of a run if it hasn't been included yet
    if (i == sizeBig - 1 && k > 0 && runs[k-1].indices != i) {
        runs[k++].indices = i;
    }
    return k;
}































int* binaryInsert(int firstArray[], int firstSize, int element) {
    int left = 0;
    int right = firstSize - 1;
    int insertPos;
    // Binary search to find the correct insertion point
    while (left <= right) {
        int midPoint = left + (right - left) / 2;
        if (element == firstArray[midPoint]) {
            left = midPoint + 1; // Adjust based on your handling of duplicates
            break;
        } else if (element < firstArray[midPoint]) {
            right = midPoint - 1;
        } else {
            left = midPoint + 1;
        }
    }
    insertPos = left; // Insertion position is where left ends up
    // Shift elements to the right to make room for the new element
    for (int k = firstSize; k > insertPos; k--) {
        firstArray[k] = firstArray[k - 1];
    }
    // Insert the new element
    if(left==firstSize) firstArray[insertPos-1]=element;
    else firstArray[insertPos] = element;
    return firstArray;
}
void combineMerge(int firstArray[],int bigArray[],int firstArraySize, int secondArraySize){
    int i=0;//for first array
    int j=0;// for the bigger array
    int k=0;//for the new sorted array
    int sortedArray[firstArraySize+secondArraySize];
}
void ascending(int *i, int sizeBig, int minSize, int array[])
{
    int firstArrayStart = *i;
    int *arrayPointer = NULL;
    int count = 1;
    // Ascending run
    while (*i + 1 < sizeBig && array[*i] < array[*i + 1]) {
        (*i)++;
        count++;
    }
    int firstArrayEnd = *i;
    if (count < minSize && *i + 1 < sizeBig) {
        int firstArraySize = (firstArrayEnd - firstArrayStart) + 1;
        printf("Insertion sort started from %d to %d\n", firstArrayStart, firstArrayEnd);
        int remaining = minSize - count;
        int firstArray[firstArraySize + remaining] = {};
        int q = 0;
        for (int p = firstArrayStart; p <= firstArrayEnd; p++) {
            firstArray[q] = array[p];
            q++;
        }
        for (int j = 0; j < remaining; j++) {
            arrayPointer = binaryInsert(firstArray, firstArraySize + remaining, array[*i + 1]);
            (*i)++;
        }
        int e = 0;
        for (int temp = firstArrayStart; temp <= firstArrayEnd + remaining; temp++) {
            array[temp] = arrayPointer[e];
            e++;
            printf("%d\n", array[temp]);
        }
        for (int l = 0; l < sizeBig; l++) {
            printf("%d ", array[l]);
        }
        printf("\n");
    }
}
void descendingFunction(int *i, int sizeBig, int minSize, int array[],int *start_descending, bool *descending){
    *start_descending=*i;
    int firstArrayStart=*i;
    int *arrayPointer=NULL;
    int count=1;
    // Descending run or single element run
    while (*i + 1 < sizeBig && array[*i] >= array[*i+1]) {
        (*i)++;
        count++;
    }
    int firstArrayEnd=*i;
    *descending=1;
    (*i)++;
    // After identifying the end of a descending run
    if (*descending) {
        int o = *start_descending;
        int l = *i - 1; // i is now one past the end of the run
        while (o < l) {
            // Swap elements at indices o and l
            int temp = array[o];
            array[o] = array[l];
            array[l] = temp;
            o++;
            l--;
        }
    }
    if(count<minSize && *i+1<sizeBig){
        int firstArraySize=(firstArrayEnd-firstArrayStart)+1;

        printf("Insertion sort started from %d to %d\n",firstArrayStart,firstArrayEnd);
        int remaining=minSize-count;
        int firstArray[firstArraySize+remaining]={};
        int q=0;
        for (int p=firstArrayStart;p<=firstArrayEnd;p++){
            firstArray[q]=array[p];
            q++;
        }
        for (int j=0;j<remaining;j++){
            arrayPointer= binaryInsert(firstArray,firstArraySize+remaining,array[firstArrayEnd+1]);
            (*i)++;
        }
        int e=0;
        for (int temp=firstArrayStart;temp<=firstArrayEnd+remaining;temp++){
            array[temp]=arrayPointer[e];
            e++;
            printf("%d\n",array[temp]);
        }
        for (int l=0;l<sizeBig;l++){
            printf("%d ",array[l]);
        }
        printf("\n");

    }
}