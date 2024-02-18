#include <iostream>     // For input and output operations
#include <fstream>      // For file input and output operations
#include <cstdlib>      // For standard library functions like srand, rand, and exit
#include <ctime>        // For functions related to time
#include <chrono>       // For high_resolution_clock

using namespace std;
using namespace std::chrono;

const int N = 300; // Define matrix size

// Function to initialize a matrix with random values
void initializeMatrix(int matrix[N][N]) {
    // Initialize matrix with random values
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            matrix[i][j] = rand() % 10; // Generate random value between 0 and 9
        }
    }
}

// Function to perform matrix multiplication
void multiplyMatrices(int A[N][N], int B[N][N], int C[N][N]) {
    // Perform matrix multiplication
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = 0; // Initialize element of C to 0
            for (int k = 0; k < N; ++k) {
                C[i][j] += A[i][k] * B[k][j]; // Compute sum of products
            }
        }
    }
}

// Function to write matrix to a file
void writeMatrixToFile(int matrix[N][N], const char* filename) {
    // Open file for writing
    ofstream outFile(filename);

    // Write each element of matrix 
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            outFile << matrix[i][j] << " "; 
        }
        outFile << endl; // Newline after each row
    }

    // Close file
    outFile.close();
}

int main() {
    // Seed random number generator
    srand(time(0));

    // Declare matrices A, B, and C
    int A[N][N];
    int B[N][N];
    int C[N][N];

    // Initialize matrices A and B with random values
    initializeMatrix(A);
    initializeMatrix(B);

    // Record the start time
    auto start = high_resolution_clock::now();

    // Perform matrix multiplication
    multiplyMatrices(A, B, C);

    // Record the end time
    auto end = high_resolution_clock::now();

    // Calculate the duration of the multiplication operation
    auto duration = duration_cast<microseconds>(end - start);

    // Write result matrix C to file
    writeMatrixToFile(C, "result_matrix.txt");

    cout << "Matrix multiplication completed in " << duration.count() << " microseconds." << endl;
    cout << "Result written to result_matrix.txt" << endl;

    return 0;
}
