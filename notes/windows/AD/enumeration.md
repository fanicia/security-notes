# AD Enumeration

## Enum in CMD

use net to enumerate eg. users, groups and so on:
```
net user ${user} /domain
```

```
net user /domain
```

```
net groups /domain
```

or the password policy for the domain: `net accounts /domain`


Has to be done from a domain-joined machine though, and it does not necessarily show the full output.


Enumerating SMB shares from the DC can be done with:

```
net view \\dc01 /all
```

## Enum in Powershell

### Manual Powershell enum

See [AD-Querier.ps1](./../../../payloads-n-scripts/scripts/AD-Querier.ps1).
When this script is imported, it can be used to make queries of the form:

```powershell
$user = LDAPSearch -Query "(&(objectCategory=user)(cn=*${USER_NAME}*))"
```
or
```powershell
$group = LDAPSearch -Query "(&(objectCategory=group)(cn=*${GROUP_NAME}*))"
```
```powershell
$group = LDAPSearch -Query "(objectCategory=computers)"
```

````powershell
$group = LDAPSearch -Query "(distinguishedname=${DISTINGUISHED_NAME_OF_OBJECT})"
`````

### Automation tools

#### RSAT (Requires local admin)

AD-RSAT tooling gives us a lot of options.
Install it by running:

```
Install-WindowsFeature -Name "RSAT-AD-PowerShell" -IncludeAllSubFeature
```

from an admin powershell.

Similar to the `net` tool, powershell has cmdlets like `GetADUser`, `Get-ADGroup` or more generically, `GetAD-Object` 
A good flag to use is `-Properties` with these, which takes a comma-separated list, or wildcards `*`


#### Enum and much else: PowerSploit

[PowerView](https://github.com/PowerShellEmpire/PowerTools/blob/master/PowerView/powerview.ps1)

Examples of commands:

* `Get-NetUser ${USER_NAME}`
* `Get-NetGroup ${GROUP}`
* `Get-NetComputer`
* `Find-LocalAdminAccess` (Finds computers in the domain in which current user is local admin).
* `Get-NetSession -ComputerName ${COMPUTER_NAME} -Verbose` (`-Verbose` to let us know if we simply don't have privileges to make the call).

TL;DR regarding finding active sessions for users: `Get-NetSession` will not work by default on Windows 11.
If that is the case, it may be worth trying the `PSLoggedOn`-tool for this purpose:
```
PSLoggedOn.exe \\${COMPUTER_NAME}
```
Just keep in mind that a blank output here can also just mean that the pre-reqs for the tool are simply not met, as it uses Remote Registry,
which has been turned off by default since Windows 8.


## Bloodhound

[Bloodhound](https://github.com/BloodHoundAD/BloodHound) with Sharphound can also be used for a graph overview of the domain.
It has the drawback of being quite noisy though.

