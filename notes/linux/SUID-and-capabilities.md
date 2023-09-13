# SUID & Capabilities

## SUID
Find SUID bit enabled files:

```
find / -perm -u=s -type f 2>/dev/null
```
Check interesting files on [gtfobins](https://gtfobins.github.io/).

Also, if you find any custom-looking SUID-binaries, try doing
```
strings <binary>
```
on them.
That will output something like this:

```
/lib64/ld-linux-x86-64.so.2
libc.so.6
setuid
system
__cxa_finalize
setgid
__libc_start_main
GLIBC_2.2.5
_ITM_deregisterTMCloneTable
__gmon_start__
_ITM_registerTMCloneTable
u+UH
[]A\A]A^A_
echo user:user | chpasswd
echo Resetting password of 'kiero' to the default value
:*3$"
GCC: (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
crtstuff.c
deregister_tm_clones
__do_global_dtors_aux
completed.8061
__do_global_dtors_aux_fini_array_entry
frame_dummy
__frame_dummy_init_array_entry
RESET_PASSWD.c
```

In this example, the binary calls `echo user:user | chpasswd`, which is why it needed the SUID bit to work.
This is vulnerable if we prefix the `PATH` with `pwd` containing a malicious `chpasswd` that makes a reverse-shell.

## Capabilities

use `getcap` to look for capabilities:

```
/usr/sbin/getcap -r / 2>/dev/null
```

Anyone with `cap_setuid+ep` should be checked on [gtfobins](https://gtfobins.github.io/)


