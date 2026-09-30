# Classic-Snake-Game
This launches the classic Snake game in your terminal. 

This project is intended for simple OOP practice.

Note that this game only works in a Unix-like environment since it uses `ncurses`.

## Usage
1. Compile the game using `make`.

```bash
make
```

2. you can run the game using the following command and specify the speed and food amount. The screen size will automatically adjust to fit the terminal window.

```bash
snake [-s speed] [-f food]
```

## Example
The speed can be set between 0 and 5.

The default speed is `2` and the default food amount is `5`.

```bash
snake -s 3 -f 10
```
