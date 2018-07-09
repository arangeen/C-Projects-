////////////////////////////////////////////////////////////////////////////////
// semi_isograms.h : CSC340 Project 3
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// DO *NOT* EDIT THIS FILE
//
////////////////////////////////////////////////////////////////////////////////

#ifndef SEMI_ISOGRAMS_H
#define SEMI_ISOGRAMS_H

#include <string>
#include <unordered_set>

using namespace std;

struct CustomHasher {
    size_t operator()(const char& c) const;
};

void populate_multiset(const string& s,
                       unordered_multiset<char, CustomHasher>* ms);

bool is_semi_isogram(const unordered_multiset<char, CustomHasher>& ms,
                     unsigned int* count);

#endif // SEMI_ISOGRAMS_H

