## What is it?
- A simple non-preemptive kernel written in C for an OS course, alongside a sample user program that will get loaded and executed by the OS.
## How to compile
- Running the `make` command should do the trick
- Consult Makefile for more details
## How to run
`make boot` would do that
# IMPORTANT NOTICE
- `-fno-pie` has been added to the gcc compiler command because without it, it reports a `kernel.c:(.text+0x10): undefined reference to '_GLOBAL_OFFSET_TABLE_'` error

Best regards,
Name            | ID
-----------------------------               
Biruk Solomon   | ATR/5471/11
Natneam Mesele  | ATR/9672/11

### Modifications made on original documents
- Loaded extra sectors from disk (Doesn't load all of the user ELF otherwise)
- we haven't used any assembly(TSL) to implement the sync( mutex and semaphore)
    - Since the kernel is a non preemptive one, we know for sure that the mutex implementations are atomic which is what the document requires
- We increased the size of the kernel from 5kb to around 10kb in the os-image, because when we didn't the kernel was hard faulting
