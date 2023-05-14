# SSH Tunneling

## Local Port Forward

Local SSH tunnel from `$OWNED_IP` to some `EXTERNAL_IP` (run this from kali).
```
ssh -N -L 0.0.0.0:${OWNED_PORT}:${EXTERNAL_IP}:${EXTERNAL_PORT} ${USER}@${OWNED_IP}
```
This will allow traffic to go `${ATTACKER_IP} <--> ${OWNED_IP}:${OWNED_PORT} <--> ${EXTERNAL_IP}:${EXTERNAL_PORT}` 

