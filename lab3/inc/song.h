#ifndef SONG_H
#define SONG_H

#include "lendable.h"

#include <string>

class Song : public Lendable {
      protected:
	std::string album;
	int bpm;

      public:
	Song();
  Song(Song& song);
  Song(long id);
  Song(long id, std::string title);
	Song(long id, std::string title, std::string author, long length);
  Song(long id, std::string title, std::string author, long length, std::string album);
  Song(long id, std::string title, std::string author, long length, int bpm);

	Song &setAlbum(std::string album);
	std::string getAlbum();

	Song &setBpm(int bpm);
	int getBpm();

	~Song();
};

#endif