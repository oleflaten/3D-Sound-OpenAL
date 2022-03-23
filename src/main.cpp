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
    SoundSource* mExplosionSound{nullptr};
    SoundSource* mLaserSound{nullptr};
    SoundSource* mStereoSound{nullptr};
    SoundSource* mSong{nullptr};

    //makes the soundmanager
    //it is a Singleton!!!
    SoundManager::getInstance()->init();

    //placing the listener:
    Vector3 pos(0.0f, 0.0f, 0.0f);  //at world origo
    Vector3 vel(0.0f, 0.0f, 0.0f);  //no velocity
    Vector3 dir(0.0f, 0.0f, -1.0f); //direction into the screen (openal uses right hand axis)
    Vector3 up(0.0f, 1.0f, 0.0f);   //Y is up

    //set the listener position
    SoundManager::getInstance()->updateListener(pos, vel, dir, up);

    //loads the sounds
    //Vector - placement - no effect on stereo sounds
    //parameters:
    //createSource(std::string name, Vector3 pos, std::string filePath, bool loop, float gain)
    mExplosionSound = SoundManager::getInstance()->createSource(
                "Explosion", Vector3(10.0f, 0.0f, 0.0f),
                "../3D-Sound-OpenAL/Assets/explosion.wav", false, 1.0f);
    mLaserSound = SoundManager::getInstance()->createSource(
                "Laser", Vector3(20.0f, 0.0f, 0.0f),
                "../3D-Sound-OpenAL/Assets/laser.wav", true, 0.4f);

    mStereoSound = SoundManager::getInstance()->createSource(
                "Stereo", Vector3(),
                "../3D-Sound-OpenAL/Assets/stereo.wav", false, 1.0f);

    mSong = SoundManager::getInstance()->createSource(
                "Caravan", Vector3(),
                "../3D-Sound-OpenAL/Assets/Caravan_mono.wav", false, 1.0f);


    //1. Stereo sounds can not be moved ******************************
    std::cout << "\nPlaying stereo wav file - positioning have no effect\n";
    mStereoSound->play();
    //this does not have any effect, because the source is stereo
    mStereoSound->setPosition(Vector3(200.0f, 30.0f, -1000.0f));
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    //2. Mono sounds can be positioned ******************************
    std::cout << "\nPlaying Explotion sound at position 10 to the right:\n";
    mExplosionSound->play();
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));

    //vector for source placement in next test
    Vector3 sourceVec3;

    //3. Playing looping sound and moving it from left to right ********************
    std::cout << "\nPlaying looping Laser sound\n";
    mLaserSound->play();

    //pans the lazer sound across the speakers
    std::cout << "\nMoving Laser sound from left to right\n";
    for (float location = -5.0f; location < 5.0f; location += 0.1f)
    {
        sourceVec3.x = location;
        mLaserSound->setPosition(sourceVec3);

        std::cout << location << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    mLaserSound->stop();

    //resets vector for next test
    sourceVec3 = Vector3();


    //4. Moving the listener gives similar effect ***********************************
    mSong->play();

    //moving the listener
    std::cout << "\n\nMoving listener from -5 left to 5 right\n";
    std::cout << "Sound is at 0,0,0\n";

    for (float location = -5.0f; location < 5.0f; location += 0.1f)
    {
        sourceVec3.x = location;
        SoundManager::getInstance()->updateListener(sourceVec3, vel, dir, up);

        std::cout << location << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    //resets vector for next test
    sourceVec3 = Vector3();

    //5. Giving the listener (or source) velocity will give Doppler effect ****************
    std::cout << "\n\nMoving listener from 5 right to -5 left \n";
    std::cout << "with velocity, giving Doppler effect\n";
    vel = Vector3(-15.0f, 0.0f, 0.0f);  //no velocity
    std::cout << "Sound is at 0,0,0\n";

    for (float location = 5.0f; location > -5.f; location -= 0.1f)
    {
        sourceVec3.x = location;
        SoundManager::getInstance()->updateListener(sourceVec3, vel, dir, up);

        std::cout << location << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    std::this_thread::sleep_for(std::chrono::seconds(4));

    //Must cleanly shut down the soundmanager
    SoundManager::getInstance()->cleanUp();

    std::cout << "\n ****Program finished****\n";
    return 0;
}
