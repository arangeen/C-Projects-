////////////////////////////////////////////////////////////////////////////////
// playlist.cc : CSC340 Project 4
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// ALL YOUR WORK SHOULD BE DONE IN THIS FILE
//
// Student Name: Ahmad Rangeen 
// Student ID: 916775826
// Student Email: arangeen@mail.sfsu.edu
////////////////////////////////////////////////////////////////////////////////

#include "playlist.h"

#include <functional>   // For std::function
#include <string>
#include <list>

using namespace std;

// Constructs a Song object, storing the 3 parameters into their respective
// member fields via initializer list syntax (the body of this ctor should be
// empty). Note that callback has a default in the .h file, and you should not
// specify the callback argument when creating Song objects.
Song::Song(const string& title,
           const string& artist,
           const function<void()> callback) : title_(title), artist_(artist), callback_() {


}

// Returns the title.
const string& Song::GetTitle() const {
    // Your code goes here

    return title_; 
   
}

// Returns the artist.
const string& Song::GetArtist() const {
    // Your code goes here
   // return Song.artist_;
    
    return artist_;
}

// Returns true if the given Song s is equal to this instance. In other words,
// if the title and artist of Song s are equal to the title and artist of this
// instance.
bool Song::operator==(const Song& s) const {
    // Your code goes here



    if (s.GetTitle() == title_ && s.GetArtist()  == artist_) {
        return true;
    } else{
        return false;
    }




}

// Defines a function call operator on an instance of Song. This will be called
// by list::remove_if to determine if the element should be removed or not. You
// must do the following in this function:
// 1) Call the callback_ member field.
// 2) Check if the given Song s matches this instance's title & artist and
//    return true if so, false otherwise.
// If this instance's title_ or artist_ fields are empty (""), that should be
// treated as a wildcard (matching any title and/or artist of s, respectively).
bool Song::operator()(const Song& s) const {
    // Your code goes here


    SongCallback();

    if (s.GetTitle() == title_ && s.GetArtist() == artist_) {

        return true;

    } else if (s.GetTitle() == title_ && artist_ == "") {

        return true;

    } else if (title_ == "" && s.GetArtist() == artist_) {

        return true;

    }else if (s.GetTitle() == "" && s.GetArtist() == ""){

        return true;

    } else if (title_ =="" && artist_ == ""){

        return true;

    } else{

        return false;

    }


}




// Used for sorting by title only (should return true if s1 is before s2).
/*static*/ bool Song::CompareTitle(const Song& s1, const Song& s2) {
    // Your code goes here
    if(s1.GetTitle()  < s2.GetTitle() )
    {
        return true;
    }else{

        return false;

    }

}

// Used for sorting by artist (and then by title for the same artist).
/*static*/ bool Song::CompareArtistTitle(const Song& s1, const Song& s2) {
    // Your code goes here
    if(s1.GetArtist()  < s2.GetArtist()  )
    {
        return true;
    }

    if(s1.GetArtist() == s2.GetArtist())
    {
        if(s1.GetTitle()  < (s2.GetTitle())  )
        {
            return true;
        }
    }

    return false;

}


// This function inserts a new Song object with the given title & artist
// into the songs_ list. Duplicates *are* allowed.
void Playlist::AddSong(const string& title, const string& artist) {
    // Your code goes here
    // creat new instance of song and push back
    Song addtheSong(title, artist);
    songs_.push_back(addtheSong);

}

// This function removes *all* songs in the songs_ list that match the given
// title & artist. If title and/or artist is the empty string (""), that will
// be treated as a wildcard (matching any title and/or artist, respectively).
// This function should also return the number of songs that were removed.
// You *must* use list::remove_if to remove the elements.
unsigned int Playlist::RemoveSongs(const string& title, const string& artist) {
    // Your code goes here

   int songRemoved = 0;

   int sizeee = songs_.size();

   songs_.remove_if(Song(title,artist));

   int anotherSize = songs_.size();

   songRemoved = sizeee - anotherSize;

   return songRemoved;

    
}

// This function will create a new copy of the list, sort it by title, and
// return that sorted list. Hint: Use CompareTitle defined in Song.
list<Song> Playlist::PlaylistSortedByTitle() const {

    // Your code goes here
    list<Song>  copyOne = songs_;
    copyOne.sort(Song::CompareTitle);
    return copyOne;

}

// This function will create a new copy of the list, sort it by artist (then
// title), and return that sorted list. Hint: Use CompareArtistTitle defined in
// Song.
list<Song> Playlist::PlaylistSortedByArtistTitle() const {
    // Your code goes here
    list<Song>  copyTwo = songs_;
    copyTwo.sort(Song::CompareArtistTitle);
    return copyTwo;

}

// This function returns the number of songs in the songs_ list.
unsigned int Playlist::NumSongs() const {
    // Your code goes here
    return songs_.size();
   
}

// This function returns the number of songs in the songs_ list that are by
// the given artist. If artist is not specified, the default is "" which
// should match all artists.
unsigned int Playlist::NumSongs(const string& artist) const {
    // Your code goes here

    int b = 0;
    for( Song cd : songs_){
        if(artist == cd.GetArtist() || artist == "")
        {
            b = b+1;
        }
    }
    return b;
    
}
