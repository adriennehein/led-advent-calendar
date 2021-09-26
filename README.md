# Advent Calendar LEDs
Program for Arduino to light up led strip for 1-25 Dec; to be paired with 25 houses in a Christmas village.

*Using Adafruit_NeoPixel library*


## Initial functionality
 - On button press, a single LED lights up, adding one light until the 25th (Set to light up every other LED because LEDs on strip are too close together for village layout).
 - On 25th day/button press, all LEDs will be lit, and will flicker softly.
 - On 26th press (or long press 5+ seconds), all lights will be off.
 
## Future implementations
 - Add Artuino RealTimeClock to light up by day and avoid button all together
 
## ToDo
 - Make 24 balsa & vellum houses
 - Troubleshoot button connection
 - Design base to hold Arduino, breadboard, lights and houses.
 - Convert from solderless breadboard to permanent setup
