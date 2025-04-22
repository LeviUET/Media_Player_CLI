#include <iostream>
#include <string>
#include <filesystem>
#include <thread>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <errno.h>
#include "model/application.hpp"
#include "controller/general_controller.hpp"
#include "view/general_view.hpp"
#include "controller/hardware_controller.hpp"
using namespace std;


int main(){
    const char* device = "/dev/ttyACM0";
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << endl;
        return 1;
    }
    if (Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 4096) < 0) {
        cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << endl;
        return 1;
    }

    Application      app;
    app.setControllerState(HOME_CONTROLLER);
    app.setViewState(HOME_VIEW);
    int fd = HardwareController::uart_init(device);
    app.setFd(fd);
    app.setVolume(128);
    
    
    std::thread uart_thread([&](){
        // Pass the member function correctly along with the object instance.
        HardwareController::uart_receive_thread(app, app.getFd());
    });
    uart_thread.detach();
    

    while(true){
        int fd = HardwareController::uart_init(device);
        app.setFd(fd);
        GeneralController::executeState(app);
    }
    Mix_HaltMusic();
    Mix_CloseAudio();
    SDL_Quit();

    return 0;
}