# John The Ripper

Use John to brute force hashes from `ssh2john` as hashcat doesn't necessarily support the used algorithm.

To define rules for john, take a ruleset as with [example](example.rule) and do 

```
sudo sh -c 'cat example.rule >> /etc/john/john.conf'
```
