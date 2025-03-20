#!/bin/bash
# profile=NL-3124u_CTU
profile=NL-3124u_OS

# menuconfig 
# make PROFILE=NL-3124u_OS menuconfig

# Capture the start time in seconds since epoch
start_time=$(date +%s)

# Run your compile command (replace 'make' with your compile command)
make PROFILE=$profile 2>&1 | tee compile_$(date '+%Y%m%d%H%M%S').log && sync

# Capture the end time in seconds since epoch
end_time=$(date +%s)

# Calculate the time spent in seconds
time_spent=$(( end_time - start_time ))

echo "Compilation took $time_spent seconds."

