#include <iostream> // std::cout, std::endl
#include <chrono>   // namespace std::chrono
#include <string>   // std::string, std::to_string
#include <stdlib.h> // std::rand, std::srand
#include <fstream>  // std::ofstream
#include "omp.h"

using namespace std::chrono;
using std::cout, std::endl;
using std::string;
using std::ofstream;
using std::ios;
using std::to_string;

#define MAX 400

struct Data
{
    int A[MAX][MAX];
    int B[MAX][MAX];
    int C[MAX][MAX];
};

string matrix_to_string(int matrix[MAX][MAX])
{
    string output_string;

    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
        {
            output_string.append(to_string(matrix[i][j]) + "\t");
            if(j == MAX-1)
                output_string.append("\n");
        }
    
    return output_string;
}

void print_matrix(int matrix[MAX][MAX])
{
    cout << matrix_to_string(matrix);

    return;
}

int main()
{
    ofstream file;
    string input, file_string;

    Data d;

    srand(time(NULL)); // pseudo-randomness

    // populating matrices A, B with random ints, 0 <= x <= 100
    // and populate matrix C with zeros
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
        {
            d.A[i][j] = rand() % 100+1;
            d.B[i][j] = rand() % 100+1;
            d.C[i][j] = 0;
        }

    // measure time at beginning of sequential multiplication, C = AB.
    auto start = steady_clock::now();

    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
            for(int k = 0; k < MAX; k++)
                d.C[i][j] += d.A[i][k] * d.B[k][j];

    auto end = steady_clock::now();
    // measure time at end of sequential multiplication

    // printing arrays
    /*
    cout << "A:" << endl;
    print_matrix(d.A);
    
    cout << endl << "B:" << endl;
    print_matrix(d.B);

    cout << endl << "C:" << endl;
    print_matrix(d.C);

    cout << endl;
    */

    // time
    cout << "T: " <<  duration_cast<nanoseconds>(end - start).count() << " ns";

    // print to file
    file.open("output.txt", ios::out);
    if(file.is_open())
    {
        file << "A:\n";
        file << matrix_to_string(d.A);
        file << "\nB:\n";
        file << matrix_to_string(d.B);
        file << "\nC:\n";
        file << matrix_to_string(d.C);
        file << "\nT: " << duration_cast<nanoseconds>(end - start).count() << " ns";

        file.close();
    }

    return EXIT_SUCCESS;
}
