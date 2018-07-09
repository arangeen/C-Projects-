////////////////////////////////////////////////////////////////////////////////
// semi_isograms_test.cc : Test harness for semi_isograms implementation.
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// DO *NOT* EDIT THIS FILE
//
////////////////////////////////////////////////////////////////////////////////

#include "semi_isograms.h"

#include <iostream>
#include <string>
#include <unordered_set>

using namespace std;

unsigned int total = 20;
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
    unordered_multiset<char, CustomHasher> ms;
    ms.max_load_factor(1000);
    ms.rehash(26);

    ms.clear();
    populate_multiset("hello", &ms);
    CHECK(ms.size() == 5);
    CHECK(ms.bucket('h') == 7 && ms.bucket_size(ms.bucket('h')) == 1);
    CHECK(ms.bucket('e') == 4 && ms.bucket_size(ms.bucket('e')) == 1);
    CHECK(ms.bucket('l') == 11 && ms.bucket_size(ms.bucket('l')) == 2);
    CHECK(ms.bucket('o') == 14 && ms.bucket_size(ms.bucket('o')) == 1);

    ms.clear();
    populate_multiset("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", &ms);
    CHECK(ms.size() == 52);
    bool pass = true;
    for (char c = 'a'; c <= 'z'; ++c) {
        if (ms.bucket(c) != (unsigned char)(c - 'a') || ms.bucket_size(ms.bucket(c)) != 2) {
            pass = false;
            break;
        }
    }
    CHECK(pass);
    CHECK(pass);
    CHECK(pass);
    CHECK(pass);

    unsigned int count;
    ms.clear();
    populate_multiset("abc", &ms);
    CHECK(is_semi_isogram(ms, &count) && count == 1);

    ms.clear();
    populate_multiset("aabbuu", &ms);
    CHECK(!is_semi_isogram(ms, &count));

    ms.clear();
    populate_multiset("aaazzzzzziii", &ms);
    CHECK(is_semi_isogram(ms, &count) && count == 6);

    ms.clear();
    populate_multiset("abb", &ms);
    CHECK(!is_semi_isogram(ms, &count));

    ms.clear();
    populate_multiset("aeb", &ms);
    CHECK(!is_semi_isogram(ms, &count));

    ms.clear();
    populate_multiset("aeiouee", &ms);
    CHECK(is_semi_isogram(ms, &count) && count == 7);

    ms.clear();
    populate_multiset("aeiouz", &ms);
    CHECK(!is_semi_isogram(ms, &count));

    ms.clear();
    populate_multiset("sfiesfsfsfsfaou", &ms);
    CHECK(is_semi_isogram(ms, &count) && count == 5);

    ms.clear();
    populate_multiset("sfiesfsfsfsfaouo", &ms);
    CHECK(!is_semi_isogram(ms, &count));

    ms.clear();
    populate_multiset("zzzzzzzzzzzzzzzzzzzuieoaazaaaaaeezoiueeieoaz", &ms);
    CHECK(is_semi_isogram(ms, &count) && count == 22);

    cout << "Score: " << correct << " / " << total << " (" << (100.0 * correct / total) << "%)" << endl;

    return 0;
}
