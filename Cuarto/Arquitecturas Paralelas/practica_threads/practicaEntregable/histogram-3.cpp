#include <vector>
#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>
#include <string>
#include <thread>
#include <mutex>

using namespace std;
int num_threads = 1;
mutex *mtx;

//---------------------
// Class Implementation
class Histogram
{
private:
    int *Hist;
    int sz = 0;

public:
    Histogram(int r) :sz{r}, Hist{new int[r]} { for (int i=0; i<sz; i++) Hist[i]=0; }
    void Calculate(const vector<int>& m,int id)
    {
        int *priv_hist = new int[sz];
        int *mod_pos = new int[sz / num_threads + 1];
        int i, j = 0;
        for (i=id; i<m.size(); i+=num_threads){
            mod_pos[j] = m[i];
            if (priv_hist[m[i]] == 0){
                priv_hist[m[i]] = 0;
            }
            priv_hist[m[i]]++;
            j++;
        }
        for (int i = 0; i < sz; i++){
            mtx[i].lock();
            Hist[mod_pos[i]] += priv_hist[mod_pos[i]];
            mtx[i].unlock();
        }
    }
    void PrintHistogram()
    {
        cout << endl << "HISTOGRAM VALUES" << endl;
        for (int i=0; i<sz; i++)
            cout << i << "        " << Hist[i] << endl;
    }
    void check(int s)
    {
	int suma = 0;
        for (int i=0; i<sz; i++)
            suma += Hist[i];
        cout << endl << "Suma of Histogram Values: " << suma << " must be equal to Matrix Size:  " << s << endl;
    }
};

//---------------------
int main(int argc, char *argv[])
{
    int range = (argc > 1) ? atoi(argv[1]) : 256;
    cout << "Range: " << range << endl;

    // Initialize random number generator
    random_device seed;  // Random device seed
    mt19937 mte{seed()}; // mersenne_twister_engine
    uniform_int_distribution<> uniform{0, range-1};

    // Initialise the array with random number the matrix
    vector<int> M;
    int tam = 16384 * 16384;
    M.reserve(tam);

    int i = 0;
    for (int i=0; i<tam; i++)
    {
        M.push_back(uniform(mte));
    }
    mtx = (mutex*)malloc(tam*sizeof(mutex));
    // Histogram
    Histogram Hist(range);
    vector<thread> thread_list;
    //cout << "Introduce el número de hilos: ";
    //cin >> num_threads;
    
    //Inicializar array de mutexes
    auto t1 = chrono::high_resolution_clock::now();

    for (int i = 0; i < num_threads; i++){
        thread_list.push_back(thread{&Histogram::Calculate, &Hist, M, i});
    }
    for (int i = 0; i < num_threads; i++){
        thread_list[i].join();
    }

    auto t2 = chrono::high_resolution_clock::now();
    
    //Hist.PrintHistogram();
    double t_elapsed = chrono::duration<double, milli>(t2 - t1).count();
    Hist.check(M.size());
    cout << "Serial time: " << t_elapsed << "msec. \n" << endl;
}
