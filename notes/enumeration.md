# Enumeration

## Nmap

By default, nmap will do a SYN scan, in which it will send a SYN package to a given port, and get a SYN-ACK back if the port is open.
The TCP protocol states that the client then states that the client should end the handshake with an ACK package, but nmap deliberately doesn't do this.
This has the benefit of not completing the handshake, which decreases the likelyhood of this being logged by the server as we never get to the application layer.
Therefore, the standard scan is also called a Stealth scan.
It is equivalent to using the flag `-sS`.

Consider just scanning the most common 1000 ports by using `nmap -sV $RHOST`
The "big hammer":`nmap -sV -p- $RHOST`

If you are scanning multiple hosts, it can be beneficial to get them from a file and also output the results to a file.
This can be done with:
```
nmap -sS -iL ip-range.txt -oN nmap-out.txt
```
where ip-range.txt is a file with the ips separated by line breaks.


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

## Netcraft

[netcraft](https://searchdns.netcraft.com/) can help with passive recon of a domain.


## DNS

`dnsrecon` and `dnsenum` for enumerating a specific domain




