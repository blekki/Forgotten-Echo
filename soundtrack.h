#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <opus/opusfile.h>

using namespace std;

class Soundtrack
{
    private:
        ALuint alBuffer;
        ALuint alSource;

    public:
        ALuint getSource();
        ALuint getBuffer();

        void play();
        void loadSound(const char* path);

        Soundtrack(){
            alGenBuffers(1, &alBuffer);
            alGenSources(1, &alSource);
        }
};