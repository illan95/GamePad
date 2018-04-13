To compile, run:
sudo ./CompileGamePad.sh

To run the progrma, execute:
sudo ./gamepad

NOTES:
The GamePad is supposed to be in /dev/input/event6
When X button (LEFT) is pressed, both for GAME and KEY, the program logs the current time.
When A button (DOWN) is pressed, both for GAME and KEY, the program logs (different file than before) the current time.
When TRIANGLE button (RIGHT) is held only for KEY, the program stops OpenC2X project, avoids OpenC2X to load at the next startup and the PC shuts down.
When any other button is pressed or held, nothing happens.
If the GamePad turns off, the program stops.

Future improvements:
 - Include EASYLOGGING (example in OpenC2X project)
 - Use std::map rather than if-else sentences
 - Automatically detect where the GamePad is (/dev/input/eventX)
