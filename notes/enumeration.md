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

To search for nmap scripts for SMB, do something like `ls -1 /usr/share/nmap/scripts/smb*`.

Or do something like `grep $keyword /usr/share/nmap/scripts/*.nse`.
Keywords here can be eg. `enumerate, fuzz, brute force, detect or exploit`.

To get help with a script, use `nmap --script-help=${SCRIPT}`





## Random commands

Useful early enumeration commands:
* T4 for quickscan: `nmap -T4 -p- -Pn $RHOST`
* `nmap -sV -p- $RHOST`
* `nikto -host ${RHOST}`
* `smbmap -H ${RHOST}`


If you see a port that none of the normal enumeration tools can identify,
it can be beneficial to do a simple

```
echo "version" | nc $RHOST $PORT 
```

The service might just answer something useful back.

### SMB enumeration

If you want `smbmap` with a host-file, do `--host-file hosts.txt`

example of recursive smbget:
`smbget -R smb://${RHOST}:${PORT}/${DIRECTORY} -U ${USER}`


or of you have found a set of credentials for SMB, you can do:

```
smbclient -p ${PORT} //$RHOST/${SHARE} -U ${USER} --password=${PASSWORD}
```
Standard port is 445


To communicate with a public share, do:
```
smbclient //$RHOST/${SHARE} -U Guest 
```
and then use empty password.

Assuming you have credentials from a domain user, you can check what shares are available:

```
crackmapexec smb $RHOST -u $USER -p $PASSWORD --share
```


Most basic gobuster command:
`gobuster dir -u  $RHOST -w /usr/share/wordlists/dirbuster/directory-list-2.3-small.txt`

if you need it to look for words in a pattern, eg `{word}/v1` and `{word}/v2`, you can add the patterns:

```
{GOBUSTER}/v1
{GOBUSTER}/v2
```
to a patterns.txt file and then add the flag `-p patterns.txt` to the gobuster command.


### SNMP Enumeration

Good resource on SNMP Enumeration in general [here](https://book.hacktricks.xyz/network-services-pentesting/pentesting-snmp).
Good resource on extending the usual commands [here](https://book.hacktricks.xyz/network-services-pentesting/pentesting-snmp/snmp-rce).


The quick version is that `sudo env "PATH=$PATH" autorecon $RHOST` will do most of the enumeration for you.
To do the enumeraton with snmpwalk do:

```
snmpwalk 192.168.217.149:161 -c public -v 2c 1.3.6.1.2.1.6.13.1.3
```
where the OID will define what you are querying. (note that the community is probably e.g. `manager, public, private`)
Standard OIDs are:

```
1.3.6.1.2.1.25.1.6.0 System Processes
1.3.6.1.2.1.25.4.2.1.2 Running Programs
1.3.6.1.2.1.25.4.2.1.4 Processes Path
1.3.6.1.2.1.25.2.3.1.4 Storage Units
1.3.6.1.2.1.25.6.3.1.2 Software Name
1.3.6.1.4.1.77.1.2.25 User Accounts
1.3.6.1.2.1.6.13.1.3 TCP Local Ports
```

the tool `onesixtyone` will attempt to bruteforce the community for you (this is also run by autorecon).
Also, the version `-v ` is probably either `-v1`, `-v 2c` or `-v 3`.

Note that the network administrator may have extended the functionality with custom commands.
Read this with:

```
snmpwalk -v2c -c public $RHOST NET-SNMP-EXTEND-MIB::nsExtendObjects
```

(again note the version and community).


### WebDav

Sometimes, a nikto scan will reveal WebDav to be enabled on a webserver.
This is an extension to HTTP that allows us to interact with the webserver similarly to FTP.

If this is the case, we can test what we can upload to the server with (leave out the `[-auth]` section if you don't have valid creds. might still work):

```
davtest [-auth user:password] -sendbd auto -url http://$RHOST
```
This will tell us which file extensions we can upload to the server.

Assuming .apsx is an option, we can now generate an .aspx shell with msfvenom, and upload it with:

```
cadaver $RHOST
```
Once you are logged in, use `put shell.aspx` to upload the file.

Now, you trigger it by going to e.g. `http://$RHOST/shell.aspx`.




## Powershell
```
1..1024 | % {echo ((New-Object Net.Sockets.TcpClient).Connect("$RHOST", $_)) " $_/tcp open"} 2>$null
```


## GHDB for google dorking

[GHDB](https://www.exploit-db.com/google-hacking-database)

A good one is to use `site:youtube.com` to only search for results on youtube.
There's also `filetype:` which you can use to search for things like txt files with juicy info.

## Netcraft

[netcraft](https://searchdns.netcraft.com/) can help with passive recon of a domain.


## DNS

`dnsrecon` and `dnsenum` for enumerating a specific domain


## cURL

When curling, you can use --path-as-is to keep any `/../` in the URLs.

