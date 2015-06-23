// --------------------------
// projects/collatz/Collatz.h
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------

#ifndef PDF_h
#define PDF_h

// --------
// includes
// --------

#include <iostream> // istream, ostream
#include <string>   // string
#include <utility>  // pair
#include <queue>
int tasks;
using namespace std;

// ------------
// collatz_read
// ------------

/**
 * read two ints
 * @param s a string
 * @return a pair of ints, representing the beginning and end of a range, [i, j]
 */
void pfd_initialize_adjacency_list (priority_queue<int> predecessors[tasks], priority_queue<int> successors[tasks], istream& r);

// ------------
// collatz_eval
// ------------

/**
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @return the max cycle length of the range [i, j]
 */
queue<int> pfd_eval (priority_queue<int> predecessors)[tasks], priority_queue<int> successors[tasks]);

// -------------
// collatz_print
// -------------

/**
 * print three ints
 * @param w an ostream
 * @param i the beginning of the range, inclusive
 * @param j the end       of the range, inclusive
 * @param v the max cycle length
 */
void pfd_print_result (ostream& w, queue<int>& results);

// -------------
// collatz_solve
// -------------

/**
 * @param r an istream
 * @param w an ostream
 */
void pfd_solve (istream& r, ostream& w);

#endif // Collatz_h
