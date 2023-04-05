# Enumeration

## Random commands

Useful early enumeration commands:
* T4 for quickscan: `nmap -T4 -p- -Pn $RHOST`
* `nmap -sV -p- $RHOST`
* `nikto -host ${RHOST}`
* `smbmap -H ${RHOST}`

example of recursive smbget:
`smbget -R smb://${RHOST}:${PORT}/${DIRECTORY} -U ${USER}`

Most basic gobuster command:
`gobuster dir -u  $RHOST -w /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt`

if you need it to look for words in a pattern, eg `{word}/v1` and `{word}/v2`, you can add the patterns:

```
{GOBUSTER}/v1
{GOBUSTER}/v2
```
to a patterns.txt file and then add the flag `-p patterns.txt` to the gobuster command.

## GHDB for google dorking

[GHDB](https://www.exploit-db.com/google-hacking-database)

A good one is to use `site:youtube.com` to only search for results on youtube.
There's also `filetype:` which you can use to search for things like txt files with juicy info.
