# SUID & Capabilities

## SUID
Find SUID bit enabled files:

```
find / -perm -u=s -type f 2>/dev/null
```
Check interesting files on [gtfobins](https://gtfobins.github.io/).

## Capabilities

use `getcap` to look for capabilities:

```
/usr/sbin/getcap -r / 2>/dev/null
```

Anyone with `cap_setuid+ep` should be checked on [gtfobins](https://gtfobins.github.io/)


