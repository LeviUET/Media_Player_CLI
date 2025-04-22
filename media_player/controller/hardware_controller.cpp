#include "hardware_controller.hpp"
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <errno.h>
#include <chrono>
using namespace std;

#define UART_BAUD_RATE B9600  // Define the baud rate for UART communication

int HardwareController::uart_init(const char* port) {
    int fd = open(port, O_RDWR | O_NOCTTY | O_NDELAY);  // Open UART device

    struct termios options;
    tcgetattr(fd, &options);  // Get the current UART options

    // Configure UART parameters
    cfsetispeed(&options, UART_BAUD_RATE);  // Input baud rate
    cfsetospeed(&options, UART_BAUD_RATE);  // Output baud rate

    // Set UART to 8N1 (8 data bits, no parity, 1 stop bit)
    options.c_cflag &= ~PARENB;  // No parity
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;      // 8 data bits
    options.c_cflag &= ~CRTSCTS;    // No hardware flow control
    options.c_cflag |= CREAD | CLOCAL;  // Enable receiver and set to local mode
    options.c_iflag &= ~(IXON | IXOFF | IXANY);  // Disable flow control
    options.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG);  // Disable canonical mode
    options.c_oflag &= ~OPOST;

    // Apply changes
    tcsetattr(fd, TCSANOW, &options);
    return fd;
}

void HardwareController::uart_receive_thread(Application& _app, int fd) {
    std::string received_data;
    char buffer[1];  // Buffer to read one character at a time

    // Set up select() to monitor UART input
    fd_set readfds;
    int max_fd = fd + 1;  // UART file descriptor
    auto last_n_press_time = std::chrono::steady_clock::now();  // To track time between 'N' presses
    bool waiting_for_second_n = false;  // Flag to check if we are waiting for the second "N"

    while (true) {
        // Reset the file descriptor set
        FD_ZERO(&readfds);
        FD_SET(fd, &readfds);  // Monitor UART
        struct timeval timeout = {1, 0}; // Timeout of 1 second

        // Use select to wait for UART input (non-blocking read)
        int activity = select(max_fd, &readfds, NULL, NULL, &timeout);

        if (activity < 0) {
            std::cerr << "Error in select()" << std::endl;
            break;  // Exit the loop on error
        }

        // Check if UART data is available
        if (FD_ISSET(fd, &readfds)) {
            ssize_t bytesRead = read(fd, buffer, sizeof(buffer));  // Read one byte from UART

            if (bytesRead < 0) {
                std::cerr << "Error reading from UART" << std::endl;
                break;  // Exit the loop on error
            }

            if (bytesRead == 0) {
                std::this_thread::sleep_for(std::chrono::milliseconds(10));  // Sleep briefly if no data is received
                continue;
            }
            received_data += buffer[0];
            // Process each character received
            if (buffer[0] == '.') {  // End-of-message indicator
                // Process the received data
                if (received_data == "P.") {
                    MediaPlayerController::pauseMusic();  // Pause the music
                    GeneralView::generateView(_app);
                } else if (received_data == "N.") {
                    // If this is the first "N" press, remember the time
                    if (!waiting_for_second_n) {
                        std::cout << "Skipping music..." << std::endl;
                        MediaPlayerController::skipMusic(_app);  // Skip the music
                        GeneralView::generateView(_app);

                        // Wait for the second "N" press
                        waiting_for_second_n = true;
                        last_n_press_time = std::chrono::steady_clock::now();
                    }
                    // Otherwise, handle double "N" press (skip to previous song)
                    else {
                        auto now = std::chrono::steady_clock::now();
                        auto duration_since_last_n = std::chrono::duration_cast<std::chrono::milliseconds>(now - last_n_press_time);

                        if (duration_since_last_n.count() < 1000) {  // 500 ms between presses
                            std::cout << "Skipping back to the previous song..." << std::endl;
                            MediaPlayerController::rewindMusic(_app);  // Go back to previous song
                            MediaPlayerController::rewindMusic(_app);  // Go back to previous song
                            GeneralView::generateView(_app);
                        }
                        else {
                            // Reset and just skip as usual if the time is too long
                            std::cout << "Skipping music..." << std::endl;
                            MediaPlayerController::skipMusic(_app);  // Skip the music
                            GeneralView::generateView(_app);
                        }

                        waiting_for_second_n = false;  // Reset after processing
                    }
                } else {
                    std::string number_str;
                    for (char c : received_data) {
                        if (isdigit(c)) {
                            number_str += c;
                        }
                    }
                    Mix_VolumeMusic(stoi(number_str));
                }
                // Clear received data for the next message
                received_data.clear();
            }
        }
    }
    close(fd);
}