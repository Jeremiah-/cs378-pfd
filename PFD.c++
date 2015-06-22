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

#include "PFD.h"

using namespace std;

// ------------
// pfd_read
// ------------

pair<int, int> pfd_read (const string& s) {
    istringstream sin(s);
    int i;
    int j;
    sin >> i >> j;
    return make_pair(i, j);}

// ------------
// pfd_eval
// ------------

int pfd_eval (int i, int j) {
    // // <your code>
    

    return 1;}

// -------------
// pfd_print
// -------------

void pfd_print (ostream& w, int i, int j, int v) {
    w << i << " " << j << " " << v << endl;}

// -------------
// pfd_solve
// -------------

void pfd_solve (istream& r, ostream& w) {
    string s;
    const pair<int, int> p = pfd_read(s);
    const int tasks = p.first;
    const int lines = p.second;
    while (getline(r, s)) {
        const int v = pfd_eval(i, j);
        pfd_print(w, i, j, v);}}
