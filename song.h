#ifndef SONG_H
#define SONG_H
//#include"songPlayer.h"
#include<string>
#include<iostream>
using namespace std;

class Song
{
  friend class SongPlayer;
 private:
  string name;
  string artist;
  string genre;
  double length;
  Song * previous;
  Song * next;
};

#endif
