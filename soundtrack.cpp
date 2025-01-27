#include <iostream>
#include <AL/al.h>
#include <AL/alc.h>
#include <opus/opusfile.h>

#include "soundtrack.h"

using namespace std;

ALuint Soundtrack::getSource(){
    return alSource;
}

ALuint Soundtrack::getBuffer(){
    return alBuffer;
}

void Soundtrack::play(){
    alSourcePlay(alSource);
}

void Soundtrack::loadSound(const char* path){
    int ok;
    OggOpusFile *file = op_open_file(path, &ok);
    if (ok != 0) {
        cout << "opus file not readed" << endl;
        return;
    }

    int channels = op_channel_count(file, -1);
    int pcm_size = op_pcm_total(file, -1);
    cout << "sound channels: " << channels << endl;
    cout << "sound pcm_size: " << pcm_size << endl;
    cout << "sound length (sec): " << pcm_size / 48000 << endl;

    short* buf = (short *) malloc(pcm_size * channels * sizeof(short));
    int ns = 0;
    int oldNs = ns;
    while (oldNs < pcm_size - 1) {
        ns = op_read(file, &buf[oldNs * channels], pcm_size - oldNs, NULL);
        if (ns == -1) return; //return 10;
        oldNs += ns;
    }

    op_free(file);

    alBufferData(alBuffer, AL_FORMAT_STEREO16, buf, pcm_size * channels * sizeof(short), 48000);
    alSourcei(alSource, AL_BUFFER, alBuffer);
    
    alSource3f(alSource, AL_POSITION, 5, 0, 0);
    alSourcei(alSource, AL_LOOPING, 1);
    alSourcef(alSource, AL_GAIN, 1);
}