## How to compile
- Running the `make` command should do the trick
- Consult Makefile for more details
## How to run
`make boot` would do that
# IMPORTANT NOTICE
- I tried to google a way to store global constants (static variables) and unfortunately
I couldn't find any therefore I have hard coded all of them
The code works as per the assignment requirments but it could use some refactorings
Just wanted to point out that shortcoming of the code.

- Additionally `-fno-pie` has been added to the gcc compiler command because without it, it reports a `kernel.c:(.text+0x10): undefined reference to '_GLOBAL_OFFSET_TABLE_'` error

Best regards,
Biruk Solomon
ATR/5471/11

### Corners cut so far
- Loaded extra sectors from disk