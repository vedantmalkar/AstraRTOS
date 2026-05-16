## Multi-task blink sample code

Two tasks blink two leds at different rates using os_delay. 

Task 1 toggles the yellow led on PG13 every 500 ms, task 2 toggles the red LED on PG14 every 700 ms.

Both tasks work simultaneously at different frequencies.

Both tasks run at priority 2 with a stack size of 128
