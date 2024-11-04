// 210 | Lab 26 | Neil Orton
// IDE Used: Xcode
#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <list>
#include <set>
#include <numeric>
using namespace std;
using namespace std::chrono;

const int STRUCTURES = 3;
const int ROWS = 4, COLS = 3;
const int W1 = 10;
const int SIMUL = 15;

int main() {
    double results[ROWS][COLS][SIMUL];    // results 3D array to store the times of the simulations
    string fobj;
    vector<string> data_vector;
    list<string> data_list;
    set<string> data_set;
    
    for (int f = 0; f < SIMUL; f++) { // for loop runs 15 for the number of simulations of each race
        // READ operations
        for (int j = 0; j < STRUCTURES; j++) {    // for loop runs for each of each of the strcutures being tested
            ifstream reader("codes.txt");
            auto start = chrono::high_resolution_clock::now();    // File is opened and timer begins
            switch(j) {
                case 0: {    // case 0, first iteration, items from file stored in a vector
                    while (reader >> fobj)
                        data_vector.push_back(fobj);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][j][f] = duration.count();    // time for the vecotr to read and store values placed in array
                    break;
                }
                case 1: {     // case 1, second iteration, items from file stored in a list
                    while (reader >> fobj)
                        data_list.push_back(fobj);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][j][f] = duration.count();   // time for the list to read and store values placed in array
                    break;
                }
                case 2: {     // case 1, third iteration, items from file stored in a set
                    while (reader >> fobj)
                        data_set.insert(fobj);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[0][j][f] = duration.count();   // time for the set to read and store values placed in array
                    break;
                }
            }
            reader.close();    // file closed
        }
        
        // SORT tests
        for (int j = 0; j < STRUCTURES; j++) {    // same logic as read race, loop runs for each of each of the strcutures
            auto start = chrono::high_resolution_clock::now();
            switch(j) {
                case 0: {  // first iteration, vector sorted
                    sort(data_vector.begin(), data_vector.end());
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[1][j][f] = duration.count();
                    break;
                }
                case 1: {  // second iteration, list sorted
                    data_list.sort();
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[1][j][f] = duration.count();
                    break;
                }
                case 2: {  // third iteration, set not needed to be sotred, -1 stored
                    results[1][j][f] = -1;
                    break;
                }
            }
        }
        
        // INSERT tests
        for (int j = 0; j < STRUCTURES; j++) {    // same logic as read race, loop runs for each of each of the strcutures
            double ind_v = data_vector.size() / 2;    // iterators for vector and list initialized
            double ind_l = data_list.size() / 2;
            auto start = chrono::high_resolution_clock::now();
            switch(j) {
                case 0: {    // first iteration, vector insert test
                    data_vector.insert(data_vector.begin() + ind_v, "TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][j][f] = duration.count();
                    break;
                }
                case 1: {    // second iteration, list insert test
                    auto it = data_list.begin();
                    advance(it, ind_l);
                    data_list.insert(it, "TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][j][f] = duration.count();
                    break;
                }
                case 2: {    // third iteration, set insert test
                    data_set.insert("TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][j][f] = duration.count();
                    break;
                }
            }
        }
        
        // DELETE tests
        for (int j = 0; j < STRUCTURES; j++) {    // same logic as read race, loop runs for each of each of the strcutures
            // select a target value in the vector
            int ind = data_vector.size() / 2;
            string target_v = data_vector[ind];
            
            // selects target value in the list
            auto it1 = data_list.begin();
            advance(it1, ind);
            string target_l = *it1;
            
            // selects target value in the set
            int ind2 = data_set.size() / 2;
            auto it2 = data_set.begin();
            advance(it2, ind2);
            string target_s = *it2;
            
            auto start = chrono::high_resolution_clock::now();
            switch(j) {
                case 0: {    // first iteration, vector delete test
                    data_vector.erase(remove(data_vector.begin(), data_vector.end(), target_v));
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][j][f] = duration.count();
                    break;
                }
                case 1: {    // second iteration, list delete test
                    data_list.remove(target_l);
                    auto end = high_resolution_clock::now();
                    auto duration = duration_cast<chrono::microseconds>(end - start);
                    results[3][j][f] = duration.count();
                    break;
                }
                case 2: {    // second iteration, set delete test
                    data_set.erase(target_s);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = duration_cast<chrono::microseconds>(end - start);
                    results[3][j][f] = duration.count();
                    break;
                }
            }
        }
        
    }

    // Number of simulations and title of each race outputted
    cout << "Number of Simulations: " << SIMUL << endl;
    string labels[] = {"Read", "Sort", "Insert", "Delete"};
    cout << setw(W1) << "Operation" << setw(W1) << "Vector" << setw(W1) << "List"
         << setw(W1) << "Set" << endl;
    
    for (int i = 0; i < ROWS; i++) {    // for loop goes through all the rows to calculate the average
        cout << setw(W1) << labels[i];    // labels outputted
        for (int j = 0; j < STRUCTURES; j++) {
            int AVG = 0;
            switch(j)
            {
                case 0: {
                    for (int f = 0; f < SIMUL; f++)
                        AVG += results[i][j][f];    // for loop iterates for number of simulations
                    AVG /= SIMUL;    // AVG sums the times and divides by the number of simulations to get the average
                    cout << setw(W1) << AVG;    // Avergare outputted
                    break;
                }
                case 1: {
                    for (int f = 0; f < SIMUL; f++)    // Same logic for the vecotr avergages
                        AVG += results[i][j][f];
                    AVG /= SIMUL;
                    cout << setw(W1) << AVG;
                    break;
                }
                case 2: {
                    for (int f = 0; f < SIMUL; f++)
                        AVG += results[i][j][f];
                    AVG /= SIMUL;
                    if (i == 1) {
                        cout << setw(W1) << 0;
                    } else {
                        cout << setw(W1) << AVG;
                    }
                    break;
                }
            }
        }
        cout << endl;
    }

    return 0;
}
