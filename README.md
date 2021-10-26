# Advent Calendar LEDs
Program for Arduino to light up led strip for 1-25 Dec; to be paired with 25 houses in a Christmas village.

*Using Adafruit_NeoPixel library*


## Intended functionality
 - [X] On button press, a single LED lights up, adding one (warm yellow) light until the 25th.
 - [X] On 25th day/button press, all LEDs will be lit
 - [ ] On 25th day/press, LEDs will flicker softly.
 - [X] On 26th press all lights will be off.
 - [ ] On long press (3000ms), all lights will clear, counters reset, no matter what point in calendar

## Existing functionality
 - On button press, a single LED lights up, adding one light until the 25th (Set to specific indeces to match housing spacing -- LEDs too close together).
 - On 25th day/button press, all LEDs are lit in rainbow pattern.
 - On 26th press all lights turn off, counters reset.
  
## Future implementations
 - Add Artuino RealTimeClock to light up by day and avoid button all together
 
## ToDo
 - [X] Make 24 balsa & vellum houses
 - [X] Troubleshoot button connection
 - [X] Design base to hold Arduino, breadboard, lights and houses.
 - [ ] Reglue lights with epoxy glue
 - [ ] Convert from solderless breadboard to permanent setup
