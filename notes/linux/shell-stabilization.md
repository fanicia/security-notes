# Shell Stabilization

[source](https://brain2life.hashnode.dev/how-to-stabilize-a-simple-reverse-shell-to-a-fully-interactive-terminal)


1. python3 -c 'import pty;pty.spawn("/bin/bash")'
2. CTRL + Z
3. stty raw -echo; fg
4. export TERM=xterm
5. hit ENTER

