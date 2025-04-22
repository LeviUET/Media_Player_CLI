#include "hardware_view.hpp"
using namespace std;

void HardwareView::generateHardwareView(Application& _app) {
    system("clear");
    while (true) {
        cout << "=======HARDWARE VIEW=======" << endl;
        cout << "UART Port: " << "/dev/ttyACM0" << endl;
        cout << "Baud Rate: " << 9600 << endl;
        if (_app.getFd() == -1) {
            cout << "Failed to initialize UART on port: " << "/dev/ttyACM0" << endl;
        } else {
            cout << "UART initialized successfully." << endl;    
        }
        this_thread::sleep_for(chrono::seconds(1));
    }
}