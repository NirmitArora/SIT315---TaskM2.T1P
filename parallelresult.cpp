#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <pthread.h>

using namespace std;
using namespace std::chrono;

const int N = 300; // Define matrix size
const int NUM_THREADS = 4; // Define the number of threads

int A[N][N];
int B[N][N];
int C[N][N];

// Function to initialize a matrix with random values
void initializeMatrix(int matrix[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10; // Generate random value between 0 and 9
        }
    }
}

// Function to perform matrix multiplication for a specific range of rows
void* multiplyMatrices(void* arg) {
    int thread_id = *((int*)arg);
    int start_row = thread_id * (N / NUM_THREADS);
    int end_row = (thread_id + 1) * (N / NUM_THREADS);

    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0;
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return NULL;
}

int main() {
    srand(time(0));

    initializeMatrix(A);
    initializeMatrix(B);

    pthread_t threads[NUM_THREADS];
    int thread_ids[NUM_THREADS];

    auto start = high_resolution_clock::now();

    for (int i = 0; i < NUM_THREADS; ++i) {
        thread_ids[i] = i;
        pthread_create(&threads[i], NULL, multiplyMatrices, (void*)&thread_ids[i]);
    }

    for (int i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], NULL);
    }

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    ofstream outFile("result_matrix.txt");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            outFile << C[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.close();

    cout << "Matrix multiplication completed in " << duration.count() << " microseconds." << endl;
    cout << "Result written to result_matrix.txt" << endl;

    return 0;
}
