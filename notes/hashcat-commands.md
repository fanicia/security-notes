# Hashcat commands

## NTLM

For NTLM hash cracks you will have something like this:
 
```
Password:
[*] Dumping Domain Credentials (domain\uid:rid:lmhash:nthash)
[*] Using the DRSUAPI method to get NTDS.DIT secrets
Administrator:500:aad3b435b51404eeaad3b435b51404ee:${NTLM_HASH}:::
Guest:501:aad3b435b51404eeaad3b435b51404ee:${NTLM_HASH}:::
krbtgt:502:aad3b435b51404eeaad3b435b51404ee:${NTLM_HASH}:::
thm.red\thm:1114:aad3b435b51404eeaad3b435b51404ee:${NTLM_HASH}:::
```
Copy `{NTLM_HASH}` into a file `hash.txt` and:

```
hashcat -m 1000 hash.txt /usr/share/wordlists/rockyou.txt
```

## NTLMv2

Copy the full hashline (everything, including username) into a file with `echo -n "..." > hash.txt` and then:

```
hashcat -m 5600 hash.txt /usr/share/wordlists/rockyou.txt 
```



