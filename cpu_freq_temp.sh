#!/bin/bash

for((;;))
do
temp=`head -n 1 /sys/class/thermal/thermal_zone0/temp | xargs -I{} awk "BEGIN {printf \"%.2f \", {}/1000}"`
echo -n $((`cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_cur_freq`/1000)) MHz, $temp degrees
printf "\r"
sleep 0.5
done
