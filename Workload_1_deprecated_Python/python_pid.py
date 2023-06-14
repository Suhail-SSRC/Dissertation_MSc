import os
import time

# Write the PID to the file
with open("process.pid", "w") as pid_file:
    pid_file.write(str(os.getpid()))

# Sleep for 5 seconds
time.sleep(5)

# Print numbers 1 through 15 with a 2 second delay between each
for i in range(1, 16):
    print(i)
    time.sleep(2)
