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
Name            | ID
-----------------------------               
Biruk Solomon   | ATR/5471/11
Natneam Mesele  | ATR/9672/11

### Corners cut so far
- Loaded extra sectors from disk (Doesn't load all of the user ELF otherwise)
- we haven't used any assembly(TSL) to implement the sync( mutex and semaphore)
    - Since the kernel is a non preemptive one, we know for sure that the mutex implementations are atomic which is what the document requires
- We increased the size of the kernel from 5kb to around 10kb in the os-image, because when we didn't the kernel was hard faulting
