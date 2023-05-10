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
to look for cron jobs scheduled as root:

```
sudo crontab -l
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

## Automated techniques

We can use `unix-privesc-check` located in `/usr/bin/unix-privesc-check`, or linpeas on `/usr/share/peass/linpeas`.



