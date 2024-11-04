#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <set>
#include <list>
#include <iomanip>
using namespace std;

const int STRUCTURES = 3;
const int ROWS = 4, COLS = 3;
const int W1 = 10;
const int SIMUL = 15;

int main() {
    int results[ROWS][COLS][SIMUL];
    string fobj;
    vector<string> data_vector;
    list<string> data_list;
    set<string> data_set;
    for (int f = 0; f < SIMUL; f++) { // for loop runs 15 for the number of simulations of each race
        // testing for READ operations
        
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
        
        // testing for INSERT operations
        for (int i = 0; i < STRUCTURES; i++) {
            int ind_v = data_vector.size() / 2;
            int ind_l = data_list.size() / 2;
            auto start = chrono::high_resolution_clock::now();
            switch(i) {
                case 0: {  // insert into a vector
                    data_vector.insert(data_vector.begin() + ind_v, "TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][i] = duration.count();
                    break;
                }
                case 1: {  // insert into a list
                    auto it = data_list.begin();
                    advance(it, ind_l);
                    data_list.insert(it, "TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][i] = duration.count();
                    break;
                }
                case 2: {  // insert into a set
                    data_set.insert("TESTCODE");
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[2][i] = duration.count();
                    break;
                }
            }
        }
        
        // testing for DELETE operations
        for (int i = 0; i < STRUCTURES; i++) {
            // select a target value in the vector
            int ind = data_vector.size() / 2;
            string target_v = data_vector[ind];
            
            // select a target value in the list
            auto it1 = data_list.begin();
            advance(it1, ind);
            string target_l = *it1;
            
            // select a target value in the set
            auto it2 = data_set.begin();
            advance(it2, ind);
            string target_s = *it2;
            
            auto start = chrono::high_resolution_clock::now();
            switch(i) {
                case 0: {  // delete by value from vector
                    data_vector.erase(remove(data_vector.begin(), data_vector.end(), target_v));
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][i] = duration.count();
                    break;
                }
                case 1: {  // delete by value from list
                    data_list.remove(target_l);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][i] = duration.count();
                    break;
                }
                case 2: {  // delete by value from set
                    data_set.erase(target_s);
                    auto end = chrono::high_resolution_clock::now();
                    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
                    results[3][i] = duration.count();
                    break;
                }
            }
        }
    }

    string labels[] = {"Read", "Sort", "Insert", "Delete"};
    cout << setw(W1) << "Operation" << setw(W1) << "Vector" << setw(W1) << "List"
         << setw(W1) << "Set" << endl;
    for (int i = 0; i < 4; i++) {
        cout << setw(W1) << labels[i];
        for (int j = 0; j < COLS; j++)
            cout << setw(W1) << results[i][j];
        cout << endl;
    }
    

    return 0;
}
