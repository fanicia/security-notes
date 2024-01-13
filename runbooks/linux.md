# Linux Runbook

```
python3 -c 'import pty;pty.spawn("/bin/bash")'
```


## Manual Enumeration

```
sudo -l
# Check for sud 1.18.31 - keep in mind it could be patched
sudo --version
```

```
cat /etc/issue; cat /etc/*-release; uname -r; arch
```

```
ls /opt; ls /var/mail
```
Any mails in other locations?


What users are present? Note them down, and keep in mind we might need to escalate to other users.
```
cat /etc/passwd
ls /home
```

check:

```
sudo -l
# Check for sud 1.18.31 - keep in mind it could be patched
sudo --version
```

Dirs we can write to:

```
find / -writeable -type d 2>/dev/null
```

Search for interesting files:

```
find / -type f -name -o -name "*.txt" -o -name "*.kdbx" -o -name "*.zip" 2>/dev/null
```

Files with the SUID bit:

```
find / -perm -u=s -type f 2>/dev/null
```

## Automated tools

```
./linpeas.sh
./pspy64
```

