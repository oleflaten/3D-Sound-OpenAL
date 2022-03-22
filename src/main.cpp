#include "soundmanager.h"
#include "soundsource.h"
#include "vector3.h"
#include <iostream>
#include <chrono>   //for sleep_for
#include <thread>   //for sleep_for

///This is just a simple testprogram for the SoundManager.

int main()
{
    //Some sounds...
    SoundSource* mExplosionSound{};
    SoundSource* mLaserSound{};
    SoundSource* mStereoSound{};
    SoundSource* mSong{};

    //makes the soundmanager
    //it is a Singleton!!!
    SoundManager::getInstance()->init();

    //loads the sounds
    //Vector - placement - no effect on stereo sound
    //parameters:
    //createSource(std::string name, Vector3 pos, std::string filePath, bool loop, float gain)
    mExplosionSound = SoundManager::getInstance()->createSource(
                "Explosion", Vector3(10.0f, 0.0f, 0.0f),
                "../Sound/Assets/explosion.wav", false, 1.0f);
    mLaserSound = SoundManager::getInstance()->createSource(
                "Laser", Vector3(20.0f, 0.0f, 0.0f),
                "../Sound/Assets/laser.wav", true, 0.7f);

    mStereoSound = SoundManager::getInstance()->createSource(
                "Stereo", Vector3(0.0f, 0.0f, 0.0f),
                "../Sound/Assets/stereo.wav", false, 1.0f);

    mSong = SoundManager::getInstance()->createSource(
                "Caravan", Vector3(0.0f, 0.0f, 0.0f),
                "../Sound/Assets/Caravan_mono.wav", false, 1.0f);

    //plays the sounds
    mStereoSound->play();
    mStereoSound->setPosition(Vector3(200.0f, 30.0f, -1000.0f));
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    mExplosionSound->play();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    mLaserSound->play();

    //placing the listener:
    Vector3 pos(0.0f, 0.0f, 0.0f);
    Vector3 vel(0.0f, 0.0f, 0.0f);
    Vector3 dir(0.0f, 0.0f, -1.0f);
    Vector3 up(0.0f, 1.0f, 0.0f);

    //set the listener position
    SoundManager::getInstance()->updateListener(pos, vel, dir, up);

    //vector for source placement
    Vector3 sourceVec3;

    //pans the lazer sound across the speakers
    std::cout << "\nMoves sound from left to right\n";
    for (float f = -5.0f; f < 5.0f; f += 0.1f)
    {
        sourceVec3.x = f;
        mLaserSound->setPosition(sourceVec3);

        std::cout << f << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    //resets vector for next test
    sourceVec3.x = 0.0f;
    sourceVec3.y = 0.0f;
    sourceVec3.z = 0.0f;
    //resets lazer position for next test
    mLaserSound->setPosition(sourceVec3);

    //moves listener around test
    std::cout << "\n\nMoves listener from -5 left to 5 right\n";
    std::cout << "Sound is at 0,0,0\n";
    for (float f = -5.0f; f < 5.0f; f += 0.1f)
    {
        sourceVec3.x = f;
        SoundManager::getInstance()->updateListener(sourceVec3, vel, dir, up);

        std::cout << f << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    mLaserSound->stop();

    //saves pos for next test:
    pos = sourceVec3;

    //resets vector for next test
    sourceVec3.x = 0.0f;
    sourceVec3.y = 0.0f;
    sourceVec3.z = 0.0f;

    mSong->play();

    //rotates listener around
    std::cout << "\n\nRotates listener from up to down\n";
    std::cout << "Sound is at 0,0,0\n";
    std::cout << "Listener is at 5,0,0\n";
    for (float f = 1.0f; f > -1.1f; f -= 0.01f)
    {
        sourceVec3.y = f;
        SoundManager::getInstance()->updateListener(pos, vel, dir, sourceVec3);

        std::cout << f << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    //Must cleanly shut down the soundmanager
    SoundManager::getInstance()->cleanUp();

    return 0;
}
