# Misc.


If you have the credentials of an Admin user, but you can't remote gain access with it through RDP/SSH or something like that,
you can do

```
cmd /c runas /user:Administrator ./shell.exe 
```
(Though the shell needs to be interactive as it'll prompt for a password).

