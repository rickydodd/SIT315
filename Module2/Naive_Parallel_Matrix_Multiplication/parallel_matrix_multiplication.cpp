#include <iostream> // std::cout, std::endl
#include <chrono>   // namespace std::chrono
#include <string>   // std::string, std::to_string
#include <stdlib.h> // std::rand, std::srand
#include <fstream>  // std::ofstream
#include <pthread.h>
#include <math.h>

using namespace std::chrono;
using std::cout, std::endl;
using std::string;
using std::ofstream;
using std::ios;
using std::to_string;

#define MAX 2
#define MAX_THREADS 10

int A[MAX][MAX];
int B[MAX][MAX];
int C[MAX][MAX];

struct Data
{
    int lower_limit;
    int upper_limit;
};

void* matrix_product(void* arg)
{
    Data* d = static_cast<Data*>(arg);
    int lower_limit = d->lower_limit, upper_limit = d->upper_limit;

    // C[i][j] += A[i][k] * B[k][j], where i is the lower_limit until it reaches the upper_limit
    while(lower_limit < upper_limit)
    {
        for(int j = 0; j < MAX; j++)
            for(int k = 0; k < MAX; k++)
                C[lower_limit][j] += A[lower_limit][k] * B[k][j];

        lower_limit++;
    }

    free(arg); // freeing Data struct that's on heap
    return 0;
}

void print_matrix(int matrix[MAX][MAX])
{
    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
        {
            cout << matrix[i][j] << "\t";
            if(j == MAX-1)
                cout << "\n";
        }
}

string matrix_to_string(int matrix[MAX][MAX])
{
    string matrix_string;

    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
        {
            matrix_string.append(to_string(matrix[i][j]) + "\t");
            if(j == MAX-1)
                matrix_string.append("\n");
        }
    
    return matrix_string;
}

int main()
{
    string file_string;
    ofstream file;
    struct Data* d;
    pthread_t threads[MAX_THREADS];
    int lower_limit = 0, upper_limit = 0;

    srand(time(NULL)); // pseudo-randomness

    for(int i = 0; i < MAX; i++)
        for(int j = 0; j < MAX; j++)
        {
            A[i][j] = rand() % 100+1;
            B[i][j] = rand() % 100+1;
            C[i][j] = 0;
        }

    // measure time at beginning of thread parallelised matrix multiplication
    auto start = steady_clock::now();

    // create MAX_THREADS (or i < MAX) threads and pass the addr of the Data struct that's on heap
    for(int i = 0; i < MAX_THREADS; i++)
    {
        if(i >= MAX)
            break;

        // allocating memory on heap for Data struct
        d = (struct Data*) malloc(sizeof(struct Data));

        // determining upper-limit and lower-limit to be passed to the thread of this for-loop iter
        lower_limit = upper_limit;
        upper_limit += round(MAX / MAX_THREADS);

        // if integer division results in zero, then add one to uppper_limit
        if(round(MAX / MAX_THREADS) == 0)
        {
            upper_limit += 1;
        }

        // if there's more to the matrix than can be evenly divided between the threads, then put all that work into the last thread
        if(i == MAX_THREADS-1 & (MAX % MAX_THREADS) != 0)
        {
            upper_limit += MAX % MAX_THREADS;
        }

        // passing lower_limit and upper_limit to struct on heap
        (*d).lower_limit = lower_limit;
        (*d).upper_limit = upper_limit;

        // creating a thread and passing the addr of the matrix_product function and the Data struct on heap
        pthread_create(&threads[i], NULL, &matrix_product, (void*)d);
    }

    // wait for worker threads to re-join the main thread
    for(int i = 0; i < MAX_THREADS; i++)
    {
        if(i >= MAX)
            break;
        
        pthread_join(threads[i], NULL);
    }
    // measure time after all threads have re-joined the main thread
    auto end = steady_clock::now();

    // print matrices
    /*
    print_matrix(A);
    cout << endl;
    print_matrix(B);
    cout << endl;
    print_matrix(C);
    cout << endl;
    */

    cout << "Time to execute matrix multiplication: " << duration_cast<nanoseconds>(end - start).count() << " ns" << endl;

    // write to file
    file.open("parallel.txt", ios::out);
    if(file.is_open())
    {
        file << "A:\n";
        file << matrix_to_string(A);
        file << "\n";
        file << "B:\n";
        file << matrix_to_string(B);
        file << "\n";
        file << "C:\n";
        file << matrix_to_string(C);
        file << "T: " + to_string(duration_cast<nanoseconds>(end - start).count()) + " ns";

        file.close();
    }

    return EXIT_SUCCESS;
}