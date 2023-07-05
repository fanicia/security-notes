# John The Ripper

Use John to brute force hashes from `ssh2john` as hashcat doesn't necessarily support the used algorithm.

To define rules for john, take a ruleset as with [example](example.rule) and do 

```
sudo sh -c 'cat example.rule >> /etc/john/john.conf'
```

Personally, john seems to be performing much better than hashcat due to hashcat primarily using GPU and john using CPU.

## NTLM

```
sudo john --format:NT ${USER_NAME}.hash -w=/usr/share/wordlists/rockyou.txt 
```

## ASREP

--format:krb5asrep


```
sudo john --format:krb5asrep ${USER_NAME}.hash -w=/usr/share/wordlists/rockyou.txt 
```
