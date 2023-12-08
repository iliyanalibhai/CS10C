#include <cmath>
#include <iostream>
#include <ctime>

using namespace std;

const int NUMBERS_SIZE = 50000;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; //clock per milliseconds



int genRandInt(int low, int high) {
   return low + rand() % (high - low + 1);
}
void fillArrays(int arr1[], int arr2[],int arr3[]){
    for(int i = 0; i < NUMBERS_SIZE; ++i){
        arr1[i] = genRandInt(0,NUMBERS_SIZE);
        arr2[i] = arr1[i];
        arr3[i] = arr1[i];
    }
}

// zybooks version of quicksort and partioning
// i represents the low and k represents high 
void Quicksort_midpoint(int numbers[], int i, int k) {
	if (i >= k) { //base case : if partition size is 1 or 0 aka nothing left to sort.
		return;
	}
	
	int pivot = numbers[i + (k - i) / 2];
	int left = i;
	int right = k;
	
	while(true) {
		while (numbers[left] < pivot) { //increment left 
			left += 1;
		}
		while (numbers[right] > pivot) { //decrements right
			right -= 1;
		}
		if (left >= right) { //nothing left to sort aka if zero or one elements remain, break 
			break;
		}
		else { // other wise we swap
			int temp = numbers[left];
			numbers[left] = numbers[right];
			numbers[right] = temp;
			left += 1;
			right -= 1;
		}
	}
	
	Quicksort_midpoint(numbers, i, right);
	Quicksort_midpoint(numbers, right + 1, k);
}


int median(int a, int b, int c) {
	if (a > b) {
		if (b > c) {
			return b;
		}
		else if (a > c) {
			return c;
		}
		else {
			return a;
		}
	}
	else {
		if (a > c) {
			return a;
		}
		else if (b > c) {
			return c;
		}
		else {
			return b;
		}
	}
}


void Quicksort_medianOfThree(int numbers[], int i, int k){ 
    if(i >= k) return; //base case 

    int pivot = median(numbers[i], numbers[i + (k-i)/2], numbers[k]); //median of the three values at beginning, mid, and end will be the pivot point
    int leftSide = i;
    int rightSide = k;

    //partition algorithm
    while(true){
        while(numbers[leftSide] < pivot) leftSide +=1;  //increments left 

        while(numbers[rightSide] > pivot) rightSide -= 1; //decrements right 

        if(leftSide >= rightSide) break; //nothing left to sort aka if zero or one elements remain, break 
        else{ // otherwise we swap
            //swap numbers at leftIndex and rightIndex
            int temp = numbers[leftSide];
            numbers[leftSide] = numbers[rightSide];
            numbers[rightSide] = temp;
            //update left and right indeces
            leftSide += 1;
            rightSide -= 1;
        }
    }
    //recursively sort from numbers[i] to numbers[rightSide]
    Quicksort_medianOfThree(numbers, i, rightSide);
    //recursively sort from numbers[rightSide + 1] to numbers[k]
    Quicksort_medianOfThree(numbers, rightSide + 1, k);
}


// this is an n^2 algo and I referenced zybooks
void InsertionSort(int numbers[], int numbersSize){
    for (int i = 1; i < numbersSize; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (numbers[j] < numbers[j - 1])
            {
                int temp = numbers[j];
                numbers[j] = numbers[j - 1];
                numbers[j - 1] = temp;
            }
        }
    }
}
int main(){
    int arr[NUMBERS_SIZE];
    int arr2[NUMBERS_SIZE];
    int arr3[NUMBERS_SIZE];

    fillArrays(arr, arr2, arr3);

    cout << "Now testing runtime of 3 sorting algs on arrays of size: " << NUMBERS_SIZE << endl;

    clock_t Start = clock();
    Quicksort_midpoint(arr, 0, NUMBERS_SIZE);
    clock_t End = clock();
    int elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Time for Quicksort midpoint in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    InsertionSort(arr2, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Insertion Sort in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    End = clock();
     elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Quicksort median of three in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    Quicksort_midpoint(arr, 0, NUMBERS_SIZE);
    End = clock();
     elapsedTime = (End - Start)/CLOCKS_PER_MS; // converts elapsed time from microseconds to milliseconds.
    cout << "Time for Quicksort midpoint in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    InsertionSort(arr2, NUMBERS_SIZE);
    End = clock();
    elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Insertion Sort in milliseconds: " << elapsedTime << " ms" << endl;

    Start = clock();
    Quicksort_medianOfThree(arr2, 0, NUMBERS_SIZE);
    End = clock();
     elapsedTime = (End - Start)/CLOCKS_PER_MS;
    cout << "Time for Quicksort median of three in milliseconds: " << elapsedTime << " ms" << endl;


   

}