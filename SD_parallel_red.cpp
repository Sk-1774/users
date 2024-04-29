#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Function to perform parallel reduction for minimum value
int parallelMin(const vector<int> &arr)
{
    int result = arr[0];
#pragma omp parallel for reduction(min : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result = min(result, arr[i]);
    }
    return result;
}

int Min(const vector<int> &arr)
{
    int result = arr[0];
    for (int i = 0; i < arr.size(); ++i)
    {
        result = min(result, arr[i]);
    }
    return result;
}

// Function to perform parallel reduction for maximum value
int parallelMax(const vector<int> &arr)
{
    int result = arr[0];
#pragma omp parallel for reduction(max : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result = max(result, arr[i]);
    }
    return result;
}

int Max(const vector<int> &arr)
{
    int result = arr[0];
    for (int i = 0; i < arr.size(); ++i)
    {
        result = max(result, arr[i]);
    }
    return result;
}

// Function to perform parallel reduction for sum
int parallelSum(const vector<int> &arr)
{
    int result = arr[0];
#pragma omp parallel for reduction(+ : result)
    for (int i = 0; i < arr.size(); ++i)
    {
        result += arr[i];
    }
    return result;
}

int Sum(const vector<int> &arr)
{
    int result = arr[0];
    for (int i = 0; i < arr.size(); ++i)
    {
        result += arr[i];
    }
    return result;
}

// Function to perform parallel reduction for average
double parallelAverage(const vector<int> &arr)
{
    int sum = parallelSum(arr);
    return static_cast<double>(sum) / arr.size();
}

double Average(const vector<int> &arr)
{
    int sum = Sum(arr);
    return static_cast<double>(sum) / arr.size();
}

int main()
{
    const int size = 1000000;
    vector<int> arr(size);

    // Initialize the array with random values
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 10;
        // cout << arr[i] << " ";
    }
    cout << endl;
    double start_time, end;

    // Compute min, max, sum, and average using parallel reduction
    start_time = omp_get_wtime();
    int pminVal = parallelMin(arr);
    end = omp_get_wtime();

    auto ptimemin = (end - start_time);

    start_time = omp_get_wtime();
    int minVal = Min(arr);
    end = omp_get_wtime();

    auto timemin = (end - start_time);
    start_time = omp_get_wtime();
    int pmaxVal = parallelMax(arr);
    end = omp_get_wtime();

    auto ptimemax = (end - start_time);

    start_time = omp_get_wtime();
    int maxVal = Max(arr);
    end = omp_get_wtime();

    auto timemax = (end - start_time);

    start_time = omp_get_wtime();
    int psum = parallelSum(arr);
    end = omp_get_wtime();

    auto ptimesum = (end - start_time);

    start_time = omp_get_wtime();
    int sum = Sum(arr);
    end = omp_get_wtime();

    auto timesum = (end - start_time);

    start_time = omp_get_wtime();
    double paverage = parallelAverage(arr);
    end = omp_get_wtime();

    auto ptimeaverage = (end - start_time);

    start_time = omp_get_wtime();
    double average = Average(arr);
    end = omp_get_wtime();

    auto timeaverage = (end - start_time);

    cout << "Minimum value: " << minVal << endl;
    cout << "P Minimum value: " << pminVal << endl;
    cout << "Sequential time for min value: " << timemin << endl;
    cout << "Parallel time for min value: " << ptimemin << endl;

    cout << "Maximum value: " << maxVal << endl;
    cout << "P Maximum value: " << pmaxVal << endl;
    cout << "Sequential time for max value: " << timemax << endl;
    cout << "Parallel time for max value: " << ptimemax << endl;

    cout << "Sum: " << sum << endl;
    cout << "P Sum: " << psum << endl;
    cout << "Sequential time for sum value: " << timesum << endl;
    cout << "Parallel time for sum value: " << ptimesum << endl;

    cout << "Average: " << average << endl;
    cout << "P Average: " << paverage << endl;
    cout << "Sequential time for max value: " << timeaverage << endl;
    cout << "Parallel time for max value: " << ptimeaverage<< endl;

    return 0;
}