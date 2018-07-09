////////////////////////////////////////////////////////////////////////////////
// playlist_test.cc : Test harness for playlist implementation.
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// DO *NOT* EDIT THIS FILE
//
////////////////////////////////////////////////////////////////////////////////

#include "playlist.h"

#include <iostream>
#include <list>

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

unsigned int callback_count = 0;
void SongCallback() {
    ++callback_count;
}

int main() {
    Song s("Bohemian Rhapsody", "Queen");
    CHECK(s.GetTitle() == "Bohemian Rhapsody" && s.GetArtist() == "Queen");
    CHECK(Song("", "")(s) &&
          Song("", "Queen")(s) &&
          Song("Bohemian Rhapsody", "")(s) &&
          Song("Bohemian Rhapsody", "Queen")(s) &&
          !Song("We Are The Champions", "Queen")(s));
    CHECK(callback_count == 5);

    CHECK(!Song::CompareTitle(Song("Bohemian Rhapsody", "Queen"),
                              Song("Baba O'Riley", "The Who")) &&
          Song::CompareTitle(Song("Bohemian Rhapsody", "Queen"),
                             Song("Born To Be Wild", "Steppenwolf")));

    Playlist p;
    p.AddSong("Enter Sandman", "Metallica");
    p.AddSong("Hey Jude", "The Beatles");
    p.AddSong("Money", "The Beatles");
    p.AddSong("Dream On", "Aerosmith");
    p.AddSong("Yesterday", "The Beatles");
    p.AddSong("Money", "Pink Floyd");
    p.AddSong("Blackbird", "The Beatles");
    p.AddSong("Faithfully", "Journey");
    p.AddSong("Enter Sandman", "Metallica");
    p.AddSong("Separate Ways", "Journey");
    p.AddSong("Don't Stop Believin'", "Journey");


    {
        list<Song> stp = p.PlaylistSortedByTitle();
        list<Song> satp = p.PlaylistSortedByArtistTitle();

         CHECK(stp.size() == 11 && satp.size() == 11);
        list<Song> expected_stp = {
            Song("Blackbird", "The Beatles"),
            Song("Don't Stop Believin'", "Journey"),
            Song("Dream On", "Aerosmith"),
            Song("Enter Sandman", "Metallica"),
            Song("Enter Sandman", "Metallica"),
            Song("Faithfully", "Journey"),
            Song("Hey Jude", "The Beatles"),
            Song("Money", "The Beatles"),
            Song("Money", "Pink Floyd"),
            Song("Separate Ways", "Journey"),
            Song("Yesterday", "The Beatles"),
        };
        CHECK(stp == expected_stp);
        list<Song> expected_satp = {
            Song("Dream On", "Aerosmith"),
            Song("Don't Stop Believin'", "Journey"),
            Song("Faithfully", "Journey"),
            Song("Separate Ways", "Journey"),
            Song("Enter Sandman", "Metallica"),
            Song("Enter Sandman", "Metallica"),
            Song("Money", "Pink Floyd"),
            Song("Blackbird", "The Beatles"),
            Song("Hey Jude", "The Beatles"),
            Song("Money", "The Beatles"),
            Song("Yesterday", "The Beatles"),
        };
        CHECK(satp == expected_satp);
    }

    CHECK(p.NumSongs() == 11 && p.NumSongs("The Beatles") == 4 && p.NumSongs("Journey") == 3);
    callback_count = 0;
    CHECK(p.RemoveSongs("Money", "") == 2 && p.NumSongs() == 9 && callback_count == 11);
    callback_count = 0;
    CHECK(p.RemoveSongs("", "The Beatles") == 3 && p.NumSongs() == 6 && callback_count == 9);
    callback_count = 0;
    CHECK(p.RemoveSongs("Separate Ways", "Journey") == 1 && p.NumSongs() == 5 && callback_count == 6);
    callback_count = 0;
    CHECK(p.RemoveSongs("Enter Sandman", "Metallica") == 2 && p.NumSongs() == 3 && callback_count == 5);
    callback_count = 0;
    CHECK(p.RemoveSongs("", "") == 3 && p.NumSongs() == 0 && callback_count == 3);

    p.AddSong("Whole Lotta Love", "Led Zeppelin");
    p.AddSong("Smells Like Teen Spirit", "Nirvana");
    p.AddSong("Won't Get Fooled Again", "The Who");
    p.AddSong("Stairway To Heaven", "Led Zeppelin");
    p.AddSong("Livin' On A Prayer", "Bon Jovi");
    p.AddSong("Stairway To Heaven", "Led Zeppelin");

    {
        list<Song> stp = p.PlaylistSortedByTitle();
        list<Song> satp = p.PlaylistSortedByArtistTitle();
        CHECK(stp.size() == 6 && satp.size() == 6);
        list<Song> expected_stp = {
            Song("Livin' On A Prayer", "Bon Jovi"),
            Song("Smells Like Teen Spirit", "Nirvana"),
            Song("Stairway To Heaven", "Led Zeppelin"),
            Song("Stairway To Heaven", "Led Zeppelin"),
            Song("Whole Lotta Love", "Led Zeppelin"),
            Song("Won't Get Fooled Again", "The Who"),
        };
        CHECK(stp == expected_stp);
        list<Song> expected_satp = {
            Song("Livin' On A Prayer", "Bon Jovi"),
            Song("Stairway To Heaven", "Led Zeppelin"),
            Song("Stairway To Heaven", "Led Zeppelin"),
            Song("Whole Lotta Love", "Led Zeppelin"),
            Song("Smells Like Teen Spirit", "Nirvana"),
            Song("Won't Get Fooled Again", "The Who"),
        };
        CHECK(satp == expected_satp);
    }

    p.RemoveSongs("", "Led Zeppelin");
    p.AddSong("Dust In The Wind", "Kansas");
    p.AddSong("Carry On Wayward Son", "Kansas");

    {
        list<Song> stp = p.PlaylistSortedByTitle();
        list<Song> satp = p.PlaylistSortedByArtistTitle();
        list<Song> expected_stp = {
            Song("Carry On Wayward Son", "Kansas"),
            Song("Dust In The Wind", "Kansas"),
            Song("Livin' On A Prayer", "Bon Jovi"),
            Song("Smells Like Teen Spirit", "Nirvana"),
            Song("Won't Get Fooled Again", "The Who"),
        };
        CHECK(stp == expected_stp);
        list<Song> expected_satp = {
            Song("Livin' On A Prayer", "Bon Jovi"),
            Song("Carry On Wayward Son", "Kansas"),
            Song("Dust In The Wind", "Kansas"),
            Song("Smells Like Teen Spirit", "Nirvana"),
            Song("Won't Get Fooled Again", "The Who"),
        };
        CHECK(satp == expected_satp);
    }

    p.AddSong("Hotel California", "Eagles");
    p.AddSong("Light My Fire", "The Doors");
    p.AddSong("Creep", "Radiohead");

    {
        list<Song> stp = p.PlaylistSortedByTitle();
        list<Song> satp = p.PlaylistSortedByArtistTitle();
        list<Song> expected_stp = {
            Song("Carry On Wayward Son", "Kansas"),
            Song("Creep", "Radiohead"),
            Song("Dust In The Wind", "Kansas"),
            Song("Hotel California", "Eagles"),
            Song("Light My Fire", "The Doors"),
            Song("Livin' On A Prayer", "Bon Jovi"),
            Song("Smells Like Teen Spirit", "Nirvana"),
            Song("Won't Get Fooled Again", "The Who"),
        };
        CHECK(stp == expected_stp);
        list<Song> expected_satp = {
            Song("Livin' On A Prayer", "Bon Jovi"),
            Song("Hotel California", "Eagles"),
            Song("Carry On Wayward Son", "Kansas"),
            Song("Dust In The Wind", "Kansas"),
            Song("Smells Like Teen Spirit", "Nirvana"),
            Song("Creep", "Radiohead"),
            Song("Light My Fire", "The Doors"),
            Song("Won't Get Fooled Again", "The Who"),
        };
        CHECK(satp == expected_satp);
    }

    cout << "Score: " << correct << " / " << total << " (" << (100.0 * correct / total) << "%)" << endl;

    return 0;
}
