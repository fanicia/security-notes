# Cross-compiling exploits

Not all exploits can be compiled easily from our attack box to match the architecture of the target machines.
I have not worked a ton with both of these approaches, but it seems that the best way is either to use docker, og XenSpawn.

## Docker

Have a deeper look into [this](https://iq.thc.org/cross-compiling-exploits).

General takeaway is that you can do something like:

```
docker run --rm -v $(pwd):/cve-2022-32250 -w /cve-2022-32250 -it ubuntu:focal-20210416
```
where you choose the image as closely to your target as possible.
Then, the exploit can be compiled with make/gcc on a machine similar to your target.


Good stuff to apt install on ubuntu:

```
apt install gcc make sudo git
sudo apt install g++-multilib
apt install libmnl-dev
apt install libnftnl-dev
```

For Ubuntu 20.04, consider simply permanently running a compiler container with this stuff prepared.




## XenSpawn

[XenSpawn](https://github.com/X0RW3LL/XenSpawn)
