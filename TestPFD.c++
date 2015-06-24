// --------------------------------
// projects/collatz/TestCollatz.c++
// Copyright (C) 2015
// Glenn P. Downing
// --------------------------------

// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair
#include <queue> //priority_queue
#include <vector>

#include "gtest/gtest.h"

#include "PFD.h"

using namespace std;

// -----------
// TestPFD
// -----------


TEST(PFDFixture, split) {
    string s("Split me up.");
    vector<string> result = pfd_split(s, ' ');
    // ASSERT_THAT(result, ElementsAre("Split", "me", "up."));
    ASSERT_EQ(result.size(), 3);
    ASSERT_EQ(result[0], "Split");
    ASSERT_EQ(result[1], "me");
    ASSERT_EQ(result[2], "up.");
}

TEST(PFDFixture, split1) {
    string s("1 2 3 4");
    vector<string> result = pfd_split(s, ' ');
    // ASSERT_THAT(result, ElementsAre("1", "2", "3", "4"));
    ASSERT_EQ(result.size(), 4);
    ASSERT_EQ(result[0], "1");
    ASSERT_EQ(result[1], "2");
    ASSERT_EQ(result[2], "3");
    ASSERT_EQ(result[3], "4");
}


// ----
// pfd_initialize_adjacency_list
// ----

TEST(PFDFixture, initialize) {
    istringstream r("1 2 1 2\n2 3 1 2 3");
    vector<int> pre(4);
    vector<vector<int>> suc(4);

    pfd_initialize_adjacency_list(pre, suc, r);

    // ASSERT_THAT( pre[1], ElementsAre(1, 2));
    // ASSERT_THAT( pre[2], ElementsAre(1, 2, 3));

    ASSERT_EQ(pre[1], 2);
    ASSERT_EQ(pre[2], 3);
    ASSERT_EQ( pre[3], 0);
    ASSERT_EQ( suc[1].size(), 2);
    ASSERT_EQ( suc[2].size(), 2);
    ASSERT_EQ( suc[3].size(), 1);
    // ASSERT_THAT(suc[1], ElementsAre(1, 2));
    // ASSERT_THAT(suc[2], ElementsAre(1, 2));
    // ASSERT_THAT(suc[3], ElementsAre(2));
}


// ----
// eval
// ----

TEST(PFDFixture, eval_1) {
    vector<vector<int>> suc(6);
    vector<int> one = {3, 5};
    vector<int> three = {2, 4};
    vector<int> five = {3, 2};

    suc[1] = one;
    suc[3] = three;
    suc[5] = five;

    vector<int> pre = {0, 0, 2, 2, 1, 1};
    queue<int> results = pfd_eval(pre, suc);

    // ASSERT_THAT(results, ElementsAre(1, 5, 3, 2, 4));}
    ASSERT_EQ(results.size(), 5);
    ASSERT_EQ(results.front(), 1);
    results.pop();
    ASSERT_EQ(results.front(), 5);
    results.pop();
    ASSERT_EQ(results.front(), 3);
    results.pop();
    ASSERT_EQ(results.front(), 2);
    results.pop();
    ASSERT_EQ(results.front(), 4);
    results.pop();
}


// -----
// print
// -----

TEST(PFDFixture, print) {
    ostringstream w;
    queue<int> results;
    results.push(1);
    results.push(2);
    results.push(3);
    results.push(4);
    results.push(5);
    pfd_print_result(w, results);
    ASSERT_EQ("1 2 3 4 5", w.str());}

// -----
// solve
// -----

TEST(PFDFixture, solve) {
    istringstream r("5 4\n3 2 1 5\n2 2 5 3\n4 1 3\n5 1 1");
    ostringstream w;
    pfd_solve(r, w);
    ASSERT_EQ("1 5 3 2 4", w.str());}


/*
% ls -al /usr/include/gtest/
...
gtest.h
...



% locate libgtest.a
/usr/lib/libgtest.a
...



% locate libpthread.a
...
/usr/lib32/libpthread.a



% locate libgtest_main.a
/usr/lib/libgtest_main.a
...



% g++-4.8 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz        >  TestCollatz.out 2>&1
% gcov-4.8 -b Collatz.c++     >> TestCollatz.out
% gcov-4.8 -b TestCollatz.c++ >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
...
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
...
*/
