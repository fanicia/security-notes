# Linux Enumeration

## Enumerating the users

full user list can be seen in `/etc/passwd`.

cron jobs for the current user can be seen with:
```
crontab -l
```
Check sudo capabilities for the current user with:
```
sudo -l
```



## Enumerating the system

For info on the system:

```
cat /etc/issue, cat /etc/*-release, uname -r, arch 
```

For displaying the route table (depending on distro):
```
route / routel 
```

list all connections with `ss`:
```
ss
```

Neat trick for gaining an overview of cronjobs:

```
ls -lah  /etc/cron*
```
to look for cron jobs scheduled with sudo privileges of current user: 

```
sudo crontab -l
```
Also remember to check:

```
cat /etc/crontab
```

Dirs we can write to:

```
find / -writeable -type d 2>/dev/null
```

Loaded kernel modules can be found with:

```
lsmod
```
Files with the SUID bit:

```
find / -perm -u=s -type f 2>/dev/null
```

We can check for processes run with passwords in plaintext like so:

```
watch -n 1 "ps -aux | grep pass"
```

And similarly, we can look for passwords in the tcpdump (requires sudo permissions):

```
sudo tcpdump -i lo -A | grep "pass"
```

`-i` chooses network interface, and `-A` prints packets in ASCII.


## Automated techniques

We can use `unix-privesc-check` located in `/usr/bin/unix-privesc-check`, or linpeas on `/usr/share/peass/linpeas`.



