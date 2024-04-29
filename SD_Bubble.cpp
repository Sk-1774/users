
#include <bits/stdc++.h>
#include <omp.h>
using namespace std;

void merge(vector<int> &a, int low, int high)
{
    int mid = (low + high) / 2;
    vector<int> left, right;
    for (int i = low; i <= mid; ++i)
    {
        left.push_back(a[i]);
    }
    for (int i = mid + 1; i <= high; ++i)
    {
        right.push_back(a[i]);
    }
    int i = 0, j = 0, cur = low;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            a[cur] = left[i];
            i++;
        }
        else
        {
            a[cur] = right[j];
            j++;
        }
        cur++;
    }
    while (i < left.size())
        a[cur] = left[i], i++, cur++;
    while (j < right.size())
        a[cur] = right[j], j++, cur++;
}
void mergesort(vector<int> &a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            mergesort(a, low, mid);
            #pragma omp section
            mergesort(a, mid + 1, high);
        }
        merge(a, low, high);
    }
}

vector<int> bubblesort(vector<int>a,int n){
    // int n=a.size();
    for (int i = 0; i < n; ++i)
    {  
    #pragma omp parallel num_threads(n)
    {
        int id=omp_get_thread_num();
        if(i%2){
            if(id%2){
                #pragma omp critical
                {
                    if(id+1<n){
                    if(a[id]>=a[id+1])swap(a[id],a[id+1]);
                }
                }
            }
        }
        else{
            if(id%2==0){
                #pragma omp critical
                {
                    if(id+1<n){
                    if(a[id]>=a[id+1])swap(a[id],a[id+1]);
                }
                }
            }
        }
    }
}

return a;
}







void seq_merge(vector<int> &a, int low, int high)
{
    int mid = (low + high) / 2;
    vector<int> left, right;
    for (int i = low; i <= mid; ++i)
    {
        left.push_back(a[i]);
    }
    for (int i = mid + 1; i <= high; ++i)
    {
        right.push_back(a[i]);
    }
    int i = 0, j = 0, cur = low;
    while (i < left.size() && j < right.size())
    {
        if (left[i] <= right[j])
        {
            a[cur] = left[i];
            i++;
        }
        else
        {
            a[cur] = right[j];
            j++;
        }
        cur++;
    }
    while (i < left.size())
        a[cur] = left[i], i++, cur++;
    while (j < right.size())
        a[cur] = right[j], j++, cur++;
}
void seq_mergesort(vector<int> &a, int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        {
            seq_mergesort(a, low, mid);            
            seq_mergesort(a, mid + 1, high);
        }
        seq_merge(a, low, high);
    }
}

vector<int> seq_bubblesort(vector<int> &a, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - 1-i; j += 1)
        {
            if (a[j] > a[j + 1])
            {
                swap(a[j], a[j + 1]);
            }
        }
    }
    return a;
}






int main()
{
    double start_time, end;
    int n;
    cout << "Enter n: ";
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 1000;
    }
    vector<int> b = a;
    vector<int> c = a;
    vector<int> d = a;

    start_time = omp_get_wtime();
    vector<int> ans = bubblesort(a, n);
    end = omp_get_wtime();
    cout << (end - start_time) << " seconds for parallel bubble sort" << endl;

    start_time = omp_get_wtime();
    mergesort(b, 0, n - 1);
    end = omp_get_wtime();
    cout << (end - start_time) << " seconds for parallel merge sort" << endl;

    cout << "-----------------------------------------------" << endl;


    start_time = omp_get_wtime();
    vector<int> ans1 = seq_bubblesort(c, n);
    end = omp_get_wtime();
    cout << (end - start_time) << " seconds for seq bubble sort" << endl;

    start_time = omp_get_wtime();
    seq_mergesort(d, 0, n - 1);
    end = omp_get_wtime();
    cout << (end - start_time) << " seconds for seq merge sort" << endl;



    // cout<<"Merge sorted : "<<endl;
    //    for(int i=0;i<b.size();i++){
    //     cout<<b[i]<<" ";
    // }
}





























// #include<iostream>
// #include<omp.h>
// #include <chrono>
// #include <bits/stdc++.h>

// using namespace std;
// using namespace std::chrono;

// void bubble(int array[], int n){
//     for (int i = 0; i < n - 1; i++){
//         for (int j = 0; j < n - i - 1; j++){
//             if (array[j] > array[j + 1]) swap(array[j], array[j + 1]);
//         }
//     }
// }

// void pBubble(int array[], int n){
//     for (int i = 0; i < n - 1; i++){
//          #pragma omp parallel for

//         for (int j = 0; j < n - i - 1; j++){
//             if (array[j] > array[j + 1]) swap(array[j], array[j + 1]);
//         }
//     }
// }

// // void pBubble(int array[], int n){
// //     //Sort odd indexed numbers
// //     for(int i = 0; i < n; ++i){
// //         #pragma omp for
// //         for (int j = 1; j < n; j += 2){
// //         if (array[j] < array[j-1])
// //         {
// //           swap(array[j], array[j - 1]);
// //         }
// //     }

// //     // Synchronize
// //     #pragma omp barrier

// //     //Sort even indexed numbers
// //     #pragma omp for
// //     for (int j = 2; j < n; j += 2){
// //       if (array[j] < array[j-1])
// //       {
// //         swap(array[j], array[j - 1]);
// //       }
// //     }
// //   }
// // }

// void printArray(int arr[], int n){
//     for(int i = 0; i < n; i++) cout << arr[i] << " ";
//     cout << "\n";
// }

// int main(){
//     // Set up variables
//     int n = 10;
//     int arr[n];
//     int brr[n];
//     // auto start_time, end_time;

//     // Create an array with numbers starting from n to 1
//     for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;

//     // Sequential time
//     auto start_time = high_resolution_clock::now();
//     bubble(arr, n);
//     auto end_time = high_resolution_clock::now();
//     auto shiv = duration_cast<milliseconds>(end_time - start_time);
//     // cout << "Sequential Bubble Sort took : " << shiv << " seconds.\n";
//     cout << "Sequential Bubble Sort took : " << shiv << " seconds.\n";

//     printArray(arr, n);

//     // Reset the array
//     for(int i = 0, j = n; i < n; i++, j--) arr[i] = j;

//     // Parallel time
//     auto start_time = high_resolution_clock::now();
//     pBubble(arr, n);
//     auto end_time = high_resolution_clock::now();
//     cout << "Parallel Bubble Sort took : " << end_time - start_time << " seconds.\n";
//     printArray(arr, n);
// }