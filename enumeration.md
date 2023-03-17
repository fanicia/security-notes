# Enumeration

<!-- TODO: Add possible flags for these -->
Useful early enumeration commands:
* T4 for quickscan: `nmap -T4 -p- -Pn $RHOST`
* `nmap -sV -p- $RHOST`
* `nikto -host ${RHOST}`
* `smbmap -H ${RHOST}`

example of recursive smbget: 
`smbget -R smb://${RHOST}:${PORT}/${DIRECTORY} -U ${USER}`

Most basic gobuster command:
`gobuster dir -u  $RHOST -w /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt`
