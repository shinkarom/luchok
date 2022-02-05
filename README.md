# luchok

> 64x32 is enough for everybody.

Luchok is a Fantasy Console inspired by Chip-8 (https://en.wikipedia.org/wiki/CHIP-8).

# Features

* Screen: 64x32

* Scripting: Lua

* Sound: 440Hz square wave

* Controls: 16 buttons, labeled from 0 to F


# Building
Building luchok requires:
* cmake (>=3.0)
* libsdl2-dev
* liblua5.4-dev

# Usage
The games for Luchok are written in Lua. (I prefer the .luchok extension, but the engine does not care).

Every frame (60 per second) the function `vblank()` is called.

The API for the fantasy console is:

* `cls()` - clears the screen.
* `draw(sprite, x, y)` - draw the array `sprite` at `x` (0-63) and `y` (0-31).
* `draw(sprite, x, y, start, len)` - draw the array `sprite` (`len` (0-31) bytes starting from index `start`) at `x` (0-63) and `y` (0-31).
* `rnd(limit)` - generate a random integer from 0 to `limit` (0-255).
* `key_pressed(num)` - check if the specified key (0-15) is pressed at this frame.
* `key_released(num)` - check if the specified key (0-15) has been released.
* `bcd(num)` - splits the specified number (0-255), into array of its digits
* `get_sprite(num)` - gets the built-in sprite for the specified number (0-255)
* `delay_timer` (0-255) - decrements every frame until it hits 0
* `sound_timer` (0-255) - decrements every frame until it hits 0, each frame it's not 0 a buzzer sounds

# Keys

Luchok has 16 keys. They are located like this:

> 1 2 3 C
> 
> 4 5 6 D
> 
> 7 8 9 E
> 
> A 0 B F

and mapped to:

> 1 2 3 4
> 
> Q W E R
> 
> A S D F
> 
> Z X C V

# License
GPL 3.


# Author
Roman "shinkarom" Shynkarenko (https://shinkarom.github.io).
