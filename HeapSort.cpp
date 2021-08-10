#include <iostream>
#include <random>
#include "stdbool.h"


#define INT_MAX_SORT 2147483647
#define INT_MIN_SORT -2147483648


void InsertionSort(int *array, int size){

    std::cout << "Insertion Sort\n";


    for(int i = 0; i < size; i++){
        int currNum = array[i];
        for(int j = 0; j < i; j++){
            if(array[j] > currNum){
                for(int k = i; k > j; k--){
                    array[k] = array[k-1];
                }
                array[j] = currNum;
                break;
            }
        }
    }
}

void SwapIndices(int *array, int i, int j){
    int temp = array[i];
    array[i] = array[j];
    array[j] = temp;
}

void SelectionSort(int *array, int size){

    std::cout << "Selection Sort\n";

    for(int i = 0; i < size; i++){
        int min = INT_MAX_SORT;
        int index = -1;
        for(int j = i; j < size; j++){
            if(array[j] < min){
                min = array[j];
                index = j;
            }
        }
        SwapIndices(array, i, index);
    }


}

void CountingSort(int *array, int size){
    std::cout << "Radix Sort\n";
    int *newArray = new int[INT_MAX_SORT];
    for(int j = 0; j < INT_MAX_SORT; j++){
        newArray[j] = 0;
    }
    for(int i = 0; i < size; i++){
        int incrIndex = array[i];
        newArray[incrIndex] = newArray[incrIndex] + 1;
    } 

    int pointer = 0;
    int check = 0;
    while(pointer < size){
        if(newArray[check] > 0){
            for(int z = 0; z < newArray[check]; z++){
                array[pointer+z] = check;
            }
            pointer += newArray[check];
        }
        check++;
    }


}

void Merge(int *array, int start, int end){

    int mid = start + (end - start)/2;
    int firstPointer = start;
    int secondPointer = mid + 1;
    
    int sizeOfNewArr = end - start + 1;
    int *tempArray = new int[sizeOfNewArr];
    int mainPointer = 0;
    while((firstPointer < (mid + 1)) || (secondPointer < (end + 1))){
        if(firstPointer == (mid + 1)){
            tempArray[mainPointer] = array[secondPointer];
            secondPointer++;
            mainPointer++;
            continue;
        }

        if(secondPointer == (end + 1)){
            tempArray[mainPointer] = array[firstPointer];
            firstPointer++;
            mainPointer++;
            continue;
        }


        if(array[firstPointer] < array[secondPointer]){
            tempArray[mainPointer] = array[firstPointer];
            firstPointer++;
        }else{
            tempArray[mainPointer] = array[secondPointer];
            secondPointer++;
        }
        mainPointer++;
    }
    for(int z = 0; z < sizeOfNewArr; z++){
        array[start+z] = tempArray[z];
    }

    delete[] tempArray;

    

}

void MergeSortHelper(int *array, int start, int end){
    if(start != end){
        int mid = start + (end - start)/2;
        MergeSortHelper(array, start, mid);
        MergeSortHelper(array, mid + 1, end);
        Merge(array, start, end);
    }

}

void MergeSort(int *array, int size){

    std::cout << "Merge Sort\n";

    MergeSortHelper(array, 0, size - 1);
}

void Heapify(int *array, int size, int i){

    
    int parentIndex = i + 1;
    int leftChildIndex = 2*parentIndex;
    int rightChildIndex = 2*parentIndex + 1;

    int parentValue = array[parentIndex - 1];
    int leftChildValue = INT_MIN_SORT;
    if(leftChildIndex < (size + 1)){
        leftChildValue = array[leftChildIndex - 1];
    }


    int rightChildValue = INT_MIN_SORT;
    if(rightChildIndex < (size + 1)){
        rightChildValue = array[rightChildIndex - 1];
    }


    int largest = i;

    if(leftChildValue > parentValue){
        if(rightChildValue > leftChildValue){
            largest = rightChildIndex - 1;
            SwapIndices(array, parentIndex - 1, rightChildIndex - 1);
        }else{
            largest = leftChildIndex - 1;
            SwapIndices(array, parentIndex - 1, leftChildIndex - 1);
        }
    }else if(rightChildValue > parentValue){
        largest = rightChildIndex - 1;
        SwapIndices(array, parentIndex - 1, rightChildIndex - 1);
    }



    if(largest != i){
        Heapify(array, size, largest);
    }


}


void HeapSort(int *array, int size){

    std::cout << "Heap Sort \n";

    for(int j = size/2 - 1; j >= 0; j--){
        Heapify(array, size, j);
    }

    int end = size - 1;

    for(int i = 0; i < end; i++){
        SwapIndices(array, 0, size - 1);
        Heapify(array, size - 1, 0);
        size--;
    }


}

bool IsSorted(int *array, int size){
    for(int i = 0; i < size - 1; i++){
        if(array[i] > array[i+1]){
            return false;
        }
    }

    return true;
}


void BubbleSort(int *array, int size){
    while(!IsSorted(array, size)){
        for(int i = 0; i < size - 1; i++){
            if(array[i] > array[i+1]){
                SwapIndices(array, i, i + 1);
            }
        }
    }
}


bool baseCase(int *arr, int sizeOfArray, int startIndex, int endIndex){
    
    if(startIndex < 0){
        return true;
    }

    if(endIndex >= sizeOfArray){
        return true;
    }

    if((endIndex - startIndex) < 2){
        if(arr[startIndex] > arr[endIndex]){
            SwapIndices(arr, startIndex, endIndex);
        }
        return true;
    }


    return false;
}

void inPlacePivot(int *arr, int sizeOfArray, int startIndex, int endIndex){

    if(baseCase(arr, sizeOfArray, startIndex, endIndex)){
        return;
    }

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(startIndex, endIndex);
    int index = dist(mt);

    int value = arr[index];
    int currIndex = startIndex;
    //std::cout << "\n" << value << "\n";
    
    for(int z = startIndex; z <= endIndex; z++){
        if(arr[z] < value){
            SwapIndices(arr, currIndex, z);
            currIndex++;

        
        }
        //std::cout << arr[z] << " ";
        
    }
    

    int switchAble = -1;
    for(int k = currIndex; k <= endIndex; k++){
        if(arr[k] == value){
            switchAble = k;
            break;
        }

    }

    SwapIndices(arr, currIndex, switchAble);

    inPlacePivot(arr, sizeOfArray, startIndex, currIndex);
    inPlacePivot(arr, sizeOfArray, currIndex + 1, endIndex);
}

void QuickSort(int *array, int sizeOfArray){
    inPlacePivot(array, sizeOfArray, 0, sizeOfArray - 1);

}


int main()
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<double> dist(1, 7500);
    int sizeOfArray = 900000;

    int *arr = new int[sizeOfArray];

    for(int i = 0; i < sizeOfArray; i++){
        arr[i] = dist(mt);
        std::cout << arr[i] << " ";
    }

    std::cout << "\n";

    QuickSort(arr, sizeOfArray);

    std::cout << "\n";

    for(int z = 0; z < sizeOfArray; z++){
        std::cout << arr[z] << " ";
    }

    if(IsSorted(arr, sizeOfArray)){
        std::cout << "\nSorted Pased!\n";
    }

    return 0;

}
