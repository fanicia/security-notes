# Hashcat commands

## Hashcat rules

you can define `.rule` files which will alter the wordlists you give hashcat.
This way, we can e.g. capitalize all the first letter of the word or adding a `1` to the end of a word with $.

the rule `c ^1` will  capitalize the first letter of the word and place a `1` in the front.
if rules are placed on individual lines, they result in multiple versions of the word.

check your rules by running `hashcat -r smthing.rules --stdout wordlist.txt`.


Note that there's a specific ruleset made for rockyou.txt at:
```
/usr/share/hashcat/rules/rockyou-30000.rule
```

## Hash identifiers

you can use `hashid` or `hash-identifier` to identify a hash.
online, there's also [hash.com](https://hashes.com/en/tools/hash_identifier)

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


