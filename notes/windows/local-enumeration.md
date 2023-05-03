# Enumerating Windows

## Enum in CMD

```
whoami
```

```
whoami /groups
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
## History

Powershell history: `Get-History`

To get history from PSReadline:
```
(Get-PSReadlineOption).HistorySavePath
```

## Enum and much else: PowerSploit


[PowerUp](https://github.com/PowerShellEmpire/PowerTools/blob/master/PowerUp/PowerUp.ps1)
