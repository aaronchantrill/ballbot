#/bin/bash

echo "Right"
gcc -lwiringPi -lwiringPiDev right.c -o right
echo "Left"
gcc -lwiringPi -lwiringPiDev left.c -o left
echo "Forward"
gcc -lwiringPi -lwiringPiDev forward.c -o forward
echo "Backward"
gcc -lwiringPi -lwiringPiDev backward.c -o backward
echo "Done!"

