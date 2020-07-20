#include<iostream>
#include<string>
#include<iomanip>
#include<fstream>
#include"songPlayer.h"
using namespace std;

SongPlayer::SongPlayer()
{
  head = NULL;
}

SongPlayer::~SongPlayer()
{

}

void SongPlayer::addSong(string sName, string sArtist, string sGenre, double sLength)
{
  Song * songPtr;
  Song * newSong;

  newSong = new Song;
  newSong->name = sName;
  newSong->artist = sArtist;
  newSong->genre = sGenre;
  newSong->length = sLength;
  //newSong->next = NULL;

  if(!head)
    {
      head = newSong;
      newSong->next = newSong;
      newSong->previous = newSong;
    }
  else
    {
      songPtr = head;
      Song * last;
      last = head->previous;

      while(sName > songPtr->name && songPtr->next != head)
	{
	  cout << songPtr->name << endl;
	  cout << " **** " << endl;
	  songPtr = songPtr->next;
	}

      if(songPtr == head)
	{
	  head = newSong;
	  newSong->next = songPtr;
	  newSong->previous = last;
	  last->next = newSong;
	  last->previous = newSong;
	}
      else if(songPtr->next == head)
	{
	  if(sName > songPtr->name)
	    {
	      songPtr->next = newSong;
	      newSong->previous = songPtr;
	      newSong->next = head;
	      head->previous = newSong;
	    }
	  else
	    {
	      songPtr->previous->next = newSong;
	      newSong->next = songPtr;
	      newSong->previous = songPtr->previous;
	      songPtr->previous = newSong;
	    }
 	}
      else
	{      
	  songPtr->previous->next = newSong;
	  newSong->next = songPtr;
	  newSong->previous = songPtr->previous;
	  songPtr->previous = newSong;

	}
    }
}
void SongPlayer::playList()
{
  if(!head)
    {
      cout << "There are no songs to play in this playlist" << endl;
      return;
    } 
  //Song * last;
  //last = head->previous; 
  current = head;
  cout << head->name << endl;
  cout << head->artist << endl;
  cout << head->genre << endl;
  cout << head->length << endl;
  current = current->next;

  while(current != head)
    {
      cout << current->name << endl;
      cout << current->artist << endl;
      cout << current->genre << endl;
      cout << current->length << endl;
      current = current->next;
    }
}

void SongPlayer::playSong(string sName)
{
  Song * songPtr;
  Song * last;
  last = head->previous;

  //searching needs to be done using cstring finder !!!!!!!!!
  if(!head)
    return;
  
  if(head->name == sName)
    {
      current = head;
      cout << current->name << endl;
      cout << current->artist << endl;
      cout << current->genre << endl;
      cout << current->length << endl;

    }
  else 
    {

      songPtr = head;

      while((songPtr->name.compare(1, songPtr->name.size(), sName)) > 0 && songPtr != last)
	{
	  songPtr = songPtr->next;
	  cout << songPtr->name.compare(1, songPtr->name.size(), sName) << endl;
	}

      if((songPtr->name.compare(1, songPtr->name.size(), sName)) > 0) 
	{
	  current = songPtr;
	  cout << current->name << endl;
	  cout << current->artist << endl;
	  cout << current->genre << endl;
	  cout << current->length << endl;
	
	}
      else 
	cout << sName << " is not in the playlist so it can not be played" << endl;
    }
}

void SongPlayer::playCurrentSong()
{
  if(!current)
    cout << "There is no current song" << endl;
  else 
    {
      cout << current->name << endl;
      cout << current->artist << endl;
      cout << current->genre << endl;
      cout << current->length << endl;
    }
}

void SongPlayer::playNextSong()
{
  if(!current)
    cout << "There is no current song" << endl;
  else
    {
      current = current->next;

      cout << current->name << endl;
      cout << current->artist << endl;
      cout << current->genre << endl;
      cout << current->length << endl;
    }
}

void SongPlayer::playPreviousSong()
{
  if(!current)
    cout << "There is no current song" << endl;
  else 
    {
      current = current->previous;

      cout << current->name << endl;
      cout << current->artist << endl;
      cout << current->genre << endl;
      cout << current->length << endl;
    }
}

void SongPlayer::deleteSong(string sName)
{
  Song * songPtr;

  if(!head)
    {
      cout << "There is no PlayList" << endl;
      return;
    }

  if(head->name == sName)
    {
      songPtr = head->next;
      delete head;
      head = songPtr;
    }
  else 
    {
      songPtr = head;

      while(songPtr != NULL && songPtr->name != sName)
	songPtr = songPtr->next;

      if(songPtr)
	{
	  songPtr->previous->next = songPtr->next;
	  delete songPtr;
	}
    }
}

void SongPlayer::deleteCurrentSong()
{  
  if(!current)
    {
      cout << "There is no current song" << endl;
      return;
    }
  else
    {
      current->previous->next = current->next;
      delete current;
    }

}

void SongPlayer::playAll(string sGenre)
{
  Song * songPtr;

  if(!head)
    return;
  songPtr = head;

  while(songPtr != NULL)
    {
      if(songPtr->genre == sGenre)
	{
	  current = songPtr;
	  cout << current->name << endl;
	  cout << current->artist << endl;
	  cout << current->genre << endl;
	  cout << current->length << endl;
	}
      songPtr = songPtr->next;
    }
}

void SongPlayer::reversePlayList()
{
  if(!head)
    return;

  current = head->previous;

  while(current != head)
    {
      cout << current->name << endl;
      cout << current->artist << endl;
      cout << current->genre << endl;
      cout << current->length << endl;
      current = current->previous;
    }


}

void SongPlayer::processTransactionFile()
{
  ifstream fin;
  string cmd;
  string sName;
  string sArtist;
  string sGenre;
  double sLength;

  fin.open("songPlayerFile2.txt");

  if(!fin)
    cout << "File can not open." << endl;
  else 
    {
      fin >> cmd;
      while(fin) 
	{
	  if(cmd == "addSong")
	    {
	      fin >> sName >> sArtist >> sGenre >> sLength;
	      addSong(sName, sArtist, sGenre, sLength);
	    }
	  else if(cmd == "playCurrentSong")
	    playCurrentSong();
	  else if(cmd == "playList")
	    playList();
	  else if(cmd == "playSong")
	    {
	      fin >> sName;
	      playSong(sName);
	    }
	  else if(cmd == "playPreviousSong")
	    playPreviousSong();
	  else if(cmd == "playNextSong")
	    playNextSong();
	  else if(cmd == "deleteCurrentSong")
	    deleteCurrentSong();
	  else if(cmd == "deleteSong")
	    {
	      fin >> sName;
	      deleteSong(sName);
	    }
	  else if(cmd == "playAll")
	    {
	      fin >> sGenre;
	      playAll(sGenre);
	    }
	  else if(cmd == "reversePlayList")
	    reversePlayList();

	  fin >> cmd;
	}
    }
}
