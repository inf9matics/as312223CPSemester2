#include "song.h"
#include "movie.h"

int main() {
    Song song{1234};
    song.setAlbum("Yeeters Mix").setTitle("Yeeting through the snow");

    Lendable lendable{std::move(song)};

    Movie movie{4321};
    movie.setMainLead("Christopher Nolan").setTitle("Action Movie The Movie");

    return 0;
}