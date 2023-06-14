import os
import time
import psutil

# Get the current process
p = psutil.Process(os.getpid())

# Write the PID to the file
with open("process.pid", "w") as pid_file:
    pid_file.write(str(p.pid))

# Sleep for 5 seconds
time.sleep(5)

# Initialize a list to store CPU usage
cpu_usage = []

# Print numbers 1 through 15 with a 2 second delay between each
for i in range(1, 16):
    print(i)
    process_cpu = p.cpu_percent(interval=1)
    total_cpu = psutil.cpu_percent(interval=1)
    cpu_usage_percent = (process_cpu / total_cpu) * 100 if total_cpu != 0 else 0
    cpu_usage.append(cpu_usage_percent)  # CPU used in the last second as a percentage
    time.sleep(2)

# Fetch the memory usage
memory_usage = p.memory_info().rss  # in bytes

# Write the CPU usage for each second and memory usage to a file
with open("results.txt", "w") as results_file:
    for i, cpu in enumerate(cpu_usage, start=1):
        results_file.write(f"CPU usage at second {i}: {cpu}% of total CPU\n")
    results_file.write(f"Memory usage: {memory_usage / 1024 / 1024} MB\n")
