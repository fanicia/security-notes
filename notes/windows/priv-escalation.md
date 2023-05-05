# Privilege Escalation

## WinPeas

[WinPeas](https://github.com/carlospolop/PEASS-ng/tree/master/winPEAS)

(also installable with `sudo apt install peass`, resulting in binaries found with `winpeas --help` and `linpeas --help` )


## PowerUp

[PowerUp.ps1](https://raw.githubusercontent.com/PowerShellMafia/PowerSploit/master/Privesc/PowerUp.ps1)

If the shell complains that scripts are turned off, do `powershell -ep bypass` to allow the script to be run.

Get it onto the target machine, do `Import-Module .\PowerUp.ps1`.
Now, we can run the functions defined in the script, such as `Get-ModifiableServiceFile`

## Windows services

We can query the wmi class `win32_service` in the following manner:
```
Get-CimInstance -ClassName win32_service | Select Name,State,PathName | Where-Object {$_.State -like 'Running'}
```

(will only work over RDP, not WinRM or a nc shell).


Once we identify a potentially vulnerable service, we can use `Get-ACL` or `icacls` to check permissions of the services.

We are looking for services where we are:

* Able to change the executable
* Able to restart the service

If the service is set to StartMode: Auto, consider if you can restart the machine after swapping out the exe-file.

