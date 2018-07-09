////////////////////////////////////////////////////////////////////////////////
// semi_isograms.cc : CSC340 Project 3
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// ALL YOUR WORK SHOULD BE DONE IN THIS FILE
//
// Student Name: Ahmad Rangeen
// Student ID:   916775826
// Student Email: arangeen@mail.sfsu.edu
////////////////////////////////////////////////////////////////////////////////

#include "semi_isograms.h"

#include <iostream>
#include <list>
#include <locale>       // std::locale and std::tolower
#include <string>
#include <unordered_set>

using namespace std;

// This hashing function should take the given character c and return an integer
// representing the hash value. This will be computed by the position of a-z,
// where a=>0, b=>1, and so on.
size_t CustomHasher::operator()(const char& c) const {
    // Your code goes here
    
    return c - 'a';
    
    //also can do return c - 'a';
}

// This function should populate the provided multiset object (ms). For each
// character in the string s, it should insert that character (lower-cased) into
// ms. The provided string s will only contain the letters A-Z and a-z, and you
// do not need to validate the string. The resulting multiset should contain a
// bucket for each letter a-z and the size of each bucket (i.e. the number of
// elements in that specific bucket) will reflect the number of times the
// corresponding letter appears in string s. The multiset object ms will be
// guaranteed to have at least 26 buckets before it is sent to this function.
void populate_multiset(const string& s,
                       unordered_multiset<char, CustomHasher>* ms) {
    // Your code goes here
    locale loc;
    for(char c : s){
        c = tolower(c, loc);
        ms->insert(c);
    }
    
}

// This function should return true if the data populated in the multiset (ms)
// represents a string that is an Isogram. For this project, an Isogram is where
// each letter appears the same number of times (not necessarily just once). An
// additional twist is that all vowels (a, e, i, o, u) are treated as the same
// letter. Thus, the strings "abc", "aabb", and "abbi" should return true, while
// the strings "abb" and "aeb" would return false. The output parameter 'count'
// should be populated with the number of times that the same letters appeared
// and will only be queried if the string was an Isogram. So, in the examples
// above for "abc", "aabb", and "abbi", the count would be 1, 2, and 2
// respectively.
bool is_semi_isogram(const unordered_multiset<char, CustomHasher>& ms,
                     unsigned int* count) {
    // Your code goes here
    *count = 0;
    char consonants[] = {'b', 'c', 'd', 'f', 'g', 'h', 'j', 'k', 'l', 'm', 'n',
                         'p', 'q', 'r', 's', 't', 'v', 'w', 'x', 'y', 'z'};
    
    char vowels[] = {'a', 'e', 'i', 'o', 'u'};
    
    for (unsigned int i = 0; i < sizeof(consonants); ++i) {
        unsigned int tmp_count = ms.bucket_size(ms.bucket(consonants[i]));
        if (tmp_count != 0) {
            if (*count != 0 && tmp_count != *count) {
                return false;
            }
            *count = tmp_count;
        }
    }
    
    unsigned int vowel_count = 0;
    for (unsigned int i = 0; i < sizeof(vowels); ++i) {
        vowel_count += ms.bucket_size(ms.bucket(vowels[i]));
    }
    
    if (vowel_count != 0) {
        if (*count != 0 && vowel_count != *count) {
            return false;
        }
        *count = vowel_count;
    }
    
    return true;
    


      
    
     
    
    
}
       
      
          
    

