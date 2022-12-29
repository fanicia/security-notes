# Enumeration

<!-- TODO: Add possible flags for these -->
Useful early enumeration commands:
* T4 for quickscan: `nmap -T4 -p- -Pn $RHOST`
* `nmap -sV -p- $RHOST`
* `nikto -host ${RHOST}`
* `smbmap -H ${RHOST}`

example of recursive smbget: 
`smbget -R smb://10.10.86.167:445/${directory} -U ${user}`
