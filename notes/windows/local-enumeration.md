# Enumerating Windows

## Enum in CMD

```
whoami
```

```
whoami /groups
```


```
whoami /priv
```

Groups such as Administrators, Backup Operators, Remote Desktop Users, and Remote Management Users can be noteworthy.

## Enum in Powershell

### Users

```powershell
Get-LocalUser
```

```
Get-LocalGroup
```

to check members of a group `$GroupName`, we can do:
```
Get-LocalGroupMember $GroupName 
```

### The System

```
ipconfig /all
```

```
route print
```
gives us the routing table of the machine.

To get active network connections:

```
netstat -ano
```
If e.g. port 3389 (RDP) is shown in this output, other users are currently connected to the system.

Also note that it can be used for debugging potential firewall issues.
Often ports used for listening are also allowed for egress.

Check installed software on the machine:
32-bit:
```
Get-ItemProperty "HKLM:\SOFTWARE\Wow6432Node\Microsoft\Windows\CurrentVersion\Uninstall\*" | select displayname

```
64-bit:
```
Get-ItemProperty "HKLM:\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\*" | select displayname
```

Finally, to get running processes:
```
Get-Process
```

#### PuTTY and SSH 

Is PuTTY / OpenSSH Found on the machine? Look for session credentials.
For PuTTY:
```
reg query "HKCU\Software\SimonTatham\PuTTY\Sessions" /s
```


For  PuTTY SSH keys:
```
reg query HKCU\Software\SimonTatham\PuTTY\SshHostKeys\
```

Also, check for SSH keys in the registry:

```
reg query HKEY_CURRENT_USER\Software\OpenSSH\Agent\Keys
```

More info [here](https://book.hacktricks.xyz/windows-hardening/windows-local-privilege-escalation)


## History

Powershell history: `Get-History`

To get history from PSReadline:
```
(Get-PSReadlineOption).HistorySavePath
```

usually stored in:

```
C:\Users\${USER}\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadLine\ConsoleHost_history.txt
```


## Environment Variables

This is also included in winpeas, but you can do:

```
Get-ChildItem -Path Env:
```
To see env vars.

## AutoLogon Credentials

Should show up using winpeas, but if you want to manually enumerate it, try:


```
REG QUERY "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\WinLogon" /v DefaultPassword
```

or

```
REG QUERY "HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\WinLogon" /v DefaultPassword /reg:64
```


## Enum and much else: PowerSploit


[PowerUp](https://github.com/PowerShellEmpire/PowerTools/blob/master/PowerUp/PowerUp.ps1)
