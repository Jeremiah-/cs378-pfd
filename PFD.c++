// ----------------------------
// projects/collatz/Collatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// ----------------------------

// THIS IS A MODIFICATION OF DOWNING'S Collatz.c++

// --------
// includes
// --------

#include <cassert>  // assert
#include <iostream> // endl, istream, ostream
#include <sstream>  // istringstream
#include <string>   // getline, string
#include <utility>  // make_pair, pair
#include <queue> //priority_queue
#include <vector>

#include "PFD.h"

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

        vector<string> nums = split(s, ' ');
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
    
    queue<int> no_predecessors;
    

    return no_predecessors;
}

// -------------
// pfd_print
// -------------

// TODO: may be a problem with printing an extra space at the end

void pfd_print_result (ostream& w, queue<int>& results) {
    int size = results.size();
    for (int i = 0; i < size - 1; ++i) {
        w << results.front() << " ";
        results.pop();
    }

    w << results.front() << endl;
}

// -------------
// pfd_solve
// -------------

void pfd_solve (istream& r, ostream& w) {
    // make an adjacency list of successors
    // make the list of predeccessors for now
    string s;
    getline(r, s);
    vector<string> nums = split(s, ' ');
    tasks = stoi(nums[0]);

    // vector<priority_queue<int>> predecessors(tasks + 1); 
    vector<int> predecessors(tasks + 1, 0);
    vector<vector<int>> successors(tasks + 1);

    pfd_initialize_adjacency_list(predecessors, successors, r);
    queue<int> results = pfd_eval(predecessors, successors);
    pfd_print_result(w, results);
}
