#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <queue> //priority_queue
#include <vector>

// #include "PFD.h"
#ifdef ONLINE_JUDGE
    #define NDEBUG
#endif

using namespace std;


// This method is taken from http://code.runnable.com/VHb0hWMZp-ws1gAr/splitting-a-string-into-a-vector-for-c%2B%2B
// since I couldn't find a simple library function to split a string
vector<string> pfd_split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
  
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
  
  return internal;
}

// ------------
// pfd_initialize_adjacency_list
// ------------

void pfd_initialize_adjacency_list (vector<int>& predecessors, vector<vector<int>>& successors, istream& r) {
    string s;
    while (getline(r, s)) {

        vector<string> nums = pfd_split(s, ' ');
        int task = stoi(nums[0]);
        int num_dependencies = stoi(nums[1]);
        // priority_queue<int> p;
        // priority_queue<int> s;

        for (int i = 2; i < num_dependencies + 2; ++i) {
            int dependency = stoi(nums[i]);
            ++(predecessors[task]);
            successors[dependency].push_back(task);
        }
    }
}

// ------------
// pfd_eval
// ------------

queue<int> pfd_eval (vector<int>& predecessors, vector<vector<int>>& successors) {
    priority_queue<int, vector<int>, greater<int>> no_predecessors;
    queue<int> results;
    // assert(results.size() == 0);
    // assert(predecessors.size() != 0);
    // assert (no_predecessors.size() == 0);

    // do a pass to get the initial no-predecessors
    for (int i = 1; i < predecessors.size(); ++i) {
        if (predecessors[i] == 0) {
            no_predecessors.push(i);
        }
    }
    
    while (!no_predecessors.empty()) {
        int task = no_predecessors.top();
        no_predecessors.pop();
        results.push(task);

        for (int i : (successors[task])) {
            if (--predecessors[i] == 0) {
                no_predecessors.push(i);
            }
        }
    }


    return results;
}

// -------------
// pfd_print
// -------------


void pfd_print_result (ostream& w, queue<int>& results) {
    int size = results.size();
    for (int i = 0; i < size - 1; ++i) {
        w << results.front() << " ";
        results.pop();
    }

    w << results.front();
}

// -------------
// pfd_solve
// -------------

void pfd_solve (istream& r, ostream& w) {
    // make an adjacency list of successors
    // make the list of predeccessors for now
    string s;
    getline(r, s);
    vector<string> nums = pfd_split(s, ' ');
    int tasks = stoi(nums[0]);

    // vector<priority_queue<int>> predecessors(tasks + 1); 
    vector<int> predecessors(tasks + 1, 0);
    vector<vector<int>> successors(tasks + 1);

    pfd_initialize_adjacency_list(predecessors, successors, r);
    queue<int> results = pfd_eval(predecessors, successors);
    pfd_print_result(w, results);
}

int main () {
    // using namespace std;
    pfd_solve(cin, cout);
    return 0;}