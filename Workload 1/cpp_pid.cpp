#include <iostream>
#include <fstream>
#include <unistd.h>
#include <thread>

int main() {
    // Get the process id
    pid_t pid = getpid();

    // Write the PID to a file
    std::ofstream pid_file("process.pid");
    if (pid_file.is_open()) {
        pid_file << pid;
        pid_file.close();
    } else {
        std::cout << "Unable to open file";
    }

    // Sleep for 5 seconds
    std::this_thread::sleep_for(std::chrono::seconds(5));

    // Print numbers 1 through 15 with a 2 second delay between each
    for (int i = 1; i <= 15; ++i) {
        std::cout << i << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
