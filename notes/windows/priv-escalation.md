# Privilege Escalation

## WinPeas

[WinPeas](https://github.com/carlospolop/PEASS-ng/tree/master/winPEAS)

(also installable with `sudo apt install peass`, resulting in binaries found with `winpeas --help` and `linpeas --help` )


## PowerUp

[PowerUp.ps1](https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Privesc/PowerUp.ps1)

If the shell complains that scripts are turned off, do `powershell -ep bypass` to allow the script to be run.

Get it onto the target machine, do `Import-Module .\PowerUp.ps1`.
Now, we can run the functions defined in the script, such as `Get-ModifiableServiceFile` or `Get-UnquotedService`

Note that `Get-UnquotedService` will give you all the information you need, including the same results as enumerating which paths we have access to with `icacls $Path`.
It will give you the ModifiablePaths where we can dump our .exe for the service to find.

## Windows services

### Hijacking the binary

remember you can use `Get-ModifiableServiceFile` from PowerUp.

We can query the wmi class `win32_service` in the following manner:
```
Get-CimInstance -ClassName win32_service | Select Name,State,PathName | Where-Object {$_.State -like 'Running'}
```

(will only work over RDP, not WinRM or a nc shell).


Once we identify a potentially vulnerable service, we can use `Get-ACL` or `icacls` to check permissions of the services.

We are looking for services where we are:

* Able to change the executable
* Able to restart the service

If we can switch out the executable with our own (eg from [win-x64-privesc](./../../payloads-n-scripts/win-x64-privesc/createadmin.exe)), we can escalate.

If the service is set to StartMode: Auto, consider if you can restart the machine after swapping out the exe-file.

### Hijacking DLLs

If we can see that a service runs specific DLLs, we might be able to hijack such a DLL and trigger our own code.

### Service Paths

Because of the way windows looks through paths, we can inject an executable into an unquoted path.
If the executable is located in:

```
C:\Program Files\SomeService\Version A\Service.exe
```
and we have write access to eg. 
```
C:\Program Files\SomeService\
```
then we can create a `Version.exe` and place it:
```
C:\Program Files\SomeService\Version.exe
```
This of course requires us to have write-access to part of the unquoted path, and access to restart the service in one way or another.


## Scheduled Tasks


To use tasks we need to consider:
* Who executes the task?
* What triggers the task?
* What happens it triggers?

Cmdlet for querying tasks:

```
schtasks /query /fo LIST /v

```
Information to look at is TaskName, Next Run Time, Author, Task to Run and Run As User.



As the output can be quite long, consider doing something like:

```
schtasks /query /fo LIST /v > tasks.txt
```
And then transfering the list to the attack box


## Misc Exploits

When looking at privilege escalation, the privilege `SeImpersonatePrivilege` can be interesting, as it allows users to run commands as another user.
By default, this privilege is given to the accounts:

* local Administrators
* LOCAL SERVICE
* NETWORK SERVICE
* SERVICE

If we have exploited IIS, it is not uncommon to have a shell running as

* LocalService
* LocalSystem
* NetworkService
* ApplicationPoolIdentity

Which all have SeImpersonatePrivilege.


Note that with SeImpersonatePrivilege it can be good to try out multiple of the "Potato" exploits as they might not all work.
[GodPotato](https://github.com/BeichenDream/GodPotato/releases/tag/V1.20) seems to generally be pretty successful with creating a reverse shell.

