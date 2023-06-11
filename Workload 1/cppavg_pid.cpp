#include <iostream>
#include <fstream>
#include <unistd.h>
#include <chrono>
#include <thread>
#include <sys/times.h>
#include <sys/resource.h>

// Function to get CPU usage of the process
double get_cpu_usage() {
    struct rusage ruse;
    getrusage(RUSAGE_SELF, &ruse);

    // Calculate CPU usage
    double cpu_usage = (ruse.ru_utime.tv_sec + ruse.ru_stime.tv_sec) * 1000000.0 +
                       (ruse.ru_utime.tv_usec + ruse.ru_stime.tv_usec);
    cpu_usage /= 1000000.0;
    return cpu_usage;
}

// Function to get memory usage of the process
long get_memory_usage() {
    struct rusage ruse;
    getrusage(RUSAGE_SELF, &ruse);

    // Return memory usage in bytes
    return ruse.ru_maxrss;
}

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
    double prev_cpu_usage = get_cpu_usage();
    long total_cpu_jiffies_start = sysconf(_SC_CLK_TCK) * sysconf(_SC_NPROCESSORS_ONLN);
    for (int i = 1; i <= 15; ++i) {
        std::cout << i << std::endl;
        double current_cpu_usage = get_cpu_usage();
        long total_cpu_jiffies_end = sysconf(_SC_CLK_TCK) * sysconf(_SC_NPROCESSORS_ONLN);
        double cpu_usage_percent = ((current_cpu_usage - prev_cpu_usage) / 
                                    (total_cpu_jiffies_end - total_cpu_jiffies_start)) * 100;
        prev_cpu_usage = current_cpu_usage;
        total_cpu_jiffies_start = total_cpu_jiffies_end;

        long memory_usage = get_memory_usage();
        std::ofstream results_file("results.txt", std::ios_base::app);
        if (results_file.is_open()) {
            results_file << "At second " << i << ", CPU usage: " << cpu_usage_percent 
                         << "%, Memory usage: " << memory_usage << "KB\n";
            results_file.close();
        } else {
            std::cout << "Unable to open file";
        }
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}
