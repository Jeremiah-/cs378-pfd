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


// ------------
// pfd_initialize_adjacency_list
// ------------

void pfd_initialize_adjacency_list (vector<int>& predecessors, vector<vector<int>>& successors, istream& r, int numLines) {

    int task;
    int num_dependencies;

    for(int j = 0; j < numLines; ++j) {
        r >> task;
        r >> num_dependencies;
        for (int i = 2; i < num_dependencies + 2; ++i) {
            int dependency;
            r >> dependency;

            // increment how many predecessors this task has
            ++(predecessors[task]);

            // keep track of what successors a task has
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
    assert(results.size() == 0);
    assert(predecessors.size() != 0);
    assert (no_predecessors.size() == 0);

    // do a pass to get the initial no-predecessors
    for (int i = 1; i < predecessors.size(); ++i) {
        if (predecessors[i] == 0) {
            no_predecessors.push(i);
        }
    }
    
    // this is the main work
    // push a task into the priority_queue when it does not have a predecessor
    while (!no_predecessors.empty()) {
        int task = no_predecessors.top();
        no_predecessors.pop();

        // this task does not have a predecessor, so he's ready to be executed
        results.push(task);

        // go through the successors of this task that was pushed
        for (int i : (successors[task])) {

            // if there are no predecessors, push it into the p_queue
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
    int tasks;
    int rules;
    r >> tasks;
    r >> rules;

    // to keep track of how many predecessors a task has
    vector<int> predecessors(tasks + 1, 0);

    // to keep track of what succeeds a task
    vector<vector<int>> successors(tasks + 1);

    pfd_initialize_adjacency_list(predecessors, successors, r, rules);
    queue<int> results = pfd_eval(predecessors, successors);
    pfd_print_result(w, results);
}
int main () {
    // using namespace std;
    pfd_solve(cin, cout);
    return 0;}