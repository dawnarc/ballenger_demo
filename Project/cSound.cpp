#include "cSound.h"

cSound::cSound(void)
{
	FMOD::System_Create(&system);// create an instance of the game engine
	system->init(32, FMOD_INIT_NORMAL, 0);// initialise the game engine with 32 channels (cantidad de sonido simultaneo que puede haber)
}

cSound::~cSound(void)
{
	for(int i=0; i<NUM_SOUNDS; i++) sounds[i]->release();
    system->release();
}

bool cSound::Load()
{
	system->createStream("Sounds/ambient.mp3",       FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &sounds[SOUND_AMBIENT]);
	system-> createSound("Sounds/swish.wav",         FMOD_HARDWARE, 0, &sounds[SOUND_SWISH]);
	system-> createSound("Sounds/warp.wav",          FMOD_HARDWARE, 0, &sounds[SOUND_WARP]);
	system-> createSound("Sounds/unlock.wav",        FMOD_HARDWARE, 0, &sounds[SOUND_UNLOCK]);
	system-> createSound("Sounds/energyflow.wav",    FMOD_HARDWARE, 0, &sounds[SOUND_ENERGYFLOW]);
	system-> createSound("Sounds/bounce.wav",        FMOD_HARDWARE, 0, &sounds[SOUND_BOUNCE]);
	system-> createSound("Sounds/pickup.wav",        FMOD_HARDWARE, 0, &sounds[SOUND_PICKUP]);
	system-> createSound("Sounds/screwgravity.wav",  FMOD_HARDWARE, 0, &sounds[SOUND_SCREWGRAVITY]);
	return true;
}

void cSound::Play(int sound_id)
{
	if (sound_id == SOUND_AMBIENT) {
		system->playSound(FMOD_CHANNEL_FREE, sounds[SOUND_AMBIENT], false, &ambient1Channel);
		ambient1Channel->setVolume( 0.25f ); //between 0 and 1
	}
	else system->playSound(FMOD_CHANNEL_FREE,sounds[sound_id], false, 0);
}

void cSound::PlayBounce(float vol)
{
	system->playSound(FMOD_CHANNEL_FREE,sounds[SOUND_BOUNCE], true, &bounceChannel);
	bounceChannel->setVolume(vol);
	bounceChannel->setPaused(false);
}

void cSound::StopAll()
{
	ambient1Channel->stop();
}

void cSound::Update()
{
	system->update();
}