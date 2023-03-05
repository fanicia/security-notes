# Powershell

Discoverability of scripting languages like Powershell or shell is poor by design.
These notes are for the weary shell-user who finds themselves stuck in a powershell (possibly on a remote machine).
Powershell cmdlets follow the naming pattern of `Verb-Noun`.

## Useful commands

Cmdlet for listing other available cmdlets:
```
Get-Command
```

It can take inputs with wildcards.

Once you find the cmdlet you want to use, you can investigate it with:

```
Get-Help ${cmdlet}
```

Now a man-page like output should help discovering how to use it.
