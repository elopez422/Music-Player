#ifndef SONGPLAYER_H
#define SONGPLAYER_H
#include"song.h"
#include<string>
using namespace std;

class SongPlayer
{
 private:
  Song* head;
  Song* current;
 public:
  SongPlayer();
  ~SongPlayer();
  void addSong(string sName, string sArtist, string sGenre, double sLength);
  void playSong(string sName);
  void playCurrentSong();
  void playNextSong();
  void playPreviousSong();
  void deleteSong(string sName);
  void deleteCurrentSong();
  void playAll(string sGenre);
  void playList();
  void reversePlayList();
  void processTransactionFile();
};

#endif
