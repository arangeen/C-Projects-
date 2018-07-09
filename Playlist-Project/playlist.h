////////////////////////////////////////////////////////////////////////////////
// playlist.h : CSC340 Project 4
// Copyright (C) 2018 Garo Bournoutian
// San Francisco State University
//
// DO *NOT* EDIT THIS FILE
//
////////////////////////////////////////////////////////////////////////////////

#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <functional>   // For std::function
#include <string>
#include <list>

using namespace std;

extern void SongCallback();

class Song {
  public:
    explicit Song(const string& title, const string& artist,
                  const function<void()> = &SongCallback);
    const string& GetTitle() const;
    const string& GetArtist() const;
    bool operator==(const Song& s) const;
    bool operator()(const Song& s) const;

    static bool CompareTitle(const Song& s1, const Song& s2);
    static bool CompareArtistTitle(const Song& s1, const Song& s2);

  private:
    const string title_;
    const string artist_;
    const function<void()> callback_;
};

class Playlist {
  public:
    explicit Playlist() {}
    void AddSong(const string& title, const string& artist);
    unsigned int RemoveSongs(const string& title, const string& artist);
    list<Song> PlaylistSortedByTitle() const;
    list<Song> PlaylistSortedByArtistTitle() const;
    unsigned int NumSongs() const;
    unsigned int NumSongs(const string& artist) const;

  private:
    list<Song> songs_;
};

#endif // PLAYLIST_H
