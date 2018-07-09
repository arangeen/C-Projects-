////////////////////////////////////////////////////////////////////////////////
// csc340_vector_test.cc : Test harness for csc340_vector implementation.
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// DO *NOT* EDIT THIS FILE
//
////////////////////////////////////////////////////////////////////////////////

#include <iostream>

#include "csc340_vector.h"

using namespace std;

unsigned int total = 48;
unsigned int correct = 0;

#define CHECK(condition) check(condition, __LINE__)
void check(bool condition, unsigned int line_number) {
    if (condition) {
        ++correct;
    } else {
        cout << "Failure on line " << line_number << endl;
    }
}

int main() {
    csc340_vector<int> vi;

    CHECK(vi.size() == 0 && vi.capacity() == 1);
    CHECK(vi.empty());

    vi.push_back(42);
    CHECK(vi.size() == 1 && vi.capacity() == 1 && !vi.empty());
    CHECK(vi.front() == 42);
    CHECK(vi.back() == 42);

    vi.push_back(123);
    CHECK(vi.size() == 2 && vi.capacity() == 2 && !vi.empty());

    vi.push_back(420);
    CHECK(vi.size() == 3 && vi.capacity() == 4 && !vi.empty());
    CHECK(vi.back() == 420);

    vi.pop_back();
    CHECK(vi.size() == 2 && vi.capacity() == 4 && !vi.empty());
    CHECK(vi.back() == 123);
    CHECK(vi[0] == 42 && vi[1] == 123);

    vi.push_back(-1);
    CHECK(vi.size() == 3 && vi.capacity() == 4 && !vi.empty());
    CHECK(vi.front() == 42);
    CHECK(vi.back() == -1);
    CHECK(vi.at(0) == 42 && vi.at(1) == 123 && vi.at(2) == -1);

    vi.reserve(4);
    CHECK(vi.size() == 3 && vi.capacity() == 4 && !vi.empty());

    vi.reserve(5);
    CHECK(vi.size() == 3 && vi.capacity() == 5 && !vi.empty());
    CHECK(vi.at(0) == 42 && vi.at(1) == 123 && vi.at(2) == -1);

    vi.push_back(2);
    vi.push_back(9);
    CHECK(vi.size() == 5 && vi.capacity() == 5 && !vi.empty());
    CHECK(vi.at(0) == 42 && vi.at(1) == 123 && vi.at(2) == -1 &&
          vi.at(3) == 2 && vi.at(4) == 9);

    vi.resize(3, -100);
    
    
    //cout << vi.size();
    CHECK(vi.size() == 3);
     CHECK( vi.capacity() == 5);
     CHECK( !vi.empty());
    CHECK(vi.at(0) == 42 && vi.at(1) == 123 && vi.at(2) == -1);

    vi.resize(11, 100);
    cout << vi.size();
    CHECK(vi.size() == 11);
    CHECK( vi.capacity() == 20); 
    CHECK( !vi.empty());
    CHECK(vi.at(0) == 42 && vi.at(1) == 123 && vi.at(2) == -1 &&
          vi.at(3) == 100 && vi.at(4) == 100 && vi.at(10) == 100);

    ++vi.at(2);
    ++vi[2];
    CHECK(vi[2] == 1);

    vi.back() += 5;
    CHECK(vi.size() == 11 && vi.capacity() == 20 && !vi.empty());
    CHECK(vi[10] == 105);

    int expected[11] = {42, 123, 1, 100, 100, 100, 100, 100, 100, 100, 105};
    for (unsigned int i = 0; i < vi.size(); ++i) {
        CHECK(vi[i] == expected[i]);
    }

    CHECK(*vi.begin() == 42);
    CHECK(*(vi.end() - 1) == 105);

    int sum = 0;
    for (auto e : vi) {
        sum += e;
        e = 0;
    }
    CHECK(sum == 971);

    for (auto& e : vi) {
        e *= 2;
    }
    sum = 0;
    for (auto it = vi.begin(); it != vi.end(); ++it) {
        sum += *it;
    }
    CHECK(sum == 1942);

    vi.clear();
    CHECK(vi.size() == 0 && vi.capacity() == 20 && vi.empty());
    CHECK(vi.begin() == vi.end());

    sum = 0;
    for (auto e : vi) {
        sum += e;
    }
    CHECK(sum == 0);

    try {
        sum = vi.at(0);
    } catch (const std::out_of_range& e) {
        CHECK(true);
    }

    vi.push_back(5);
    try {
        CHECK(vi.at(0) == 5);
    } catch (const std::out_of_range& e) {
        CHECK(false);
    }
    CHECK(vi.size() == 1 && vi.capacity() == 20 && !vi.empty());

    cout << "Score: " << correct << " / " << total << " (" << (100.0 * correct / total) << "%)" << endl;

    return 0;
}
