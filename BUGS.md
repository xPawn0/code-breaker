# Known Bugs:

* Alright :3, looks like compiler's are smart enough nowadays and can feel these sneaky bytes inside them, im not testing this program for every compiler out in this world, because its just a fun project, but most likely the output is known for every compiler out there. only tested compiler/interpreters are: (gcc, python3)

**C/C++ (gcc)**:
```sh
error: invalid preprocessing directive #\U0000200bi\U0000200bn\U0000200bc\U0000200bl\U0000200bu\U0000200bd\U0000200be\U0000200b
```
**Python 3.11:**
```sh
  File ".../code-breaker/test/asd.py", line 3
    do_not_print_please=print
                    ^
SyntaxError: invalid non-printable character U+200B
```

* Something weird in light mode code, sometimes random location will not work and the program will put nothing in the file, maybe because of the code order, idk, but im not willing to fix this, PR's are open tho.
```sh
[code-breaker/] echo 'qwerty' > test/file.txt; ./cbreaker -f test/file.txt -m 0; xxd test/file.txt
mode: "0"         //debug line
randarr[0] = 0    //debug line
randarr[1] = 3    //debug line
randarr[2] = 6    //debug line
xxd: 00000000: 7177 6572 7479 0a                        qwerty.
```
