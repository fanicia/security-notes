# Portforward with socat

assuming, we own SRV1, and we want to portforward traffic from `SRV1:${LISTENING_PORT}` to `${REMOTE_HOST}:${REMOTE_PORT}`,
we can do it with socat:
```
socat -ddd TCP-LISTEN:${LISTENING_PORT},fork TCP:${REMOTE_HOST}:${REMOTE_PORT}
```
