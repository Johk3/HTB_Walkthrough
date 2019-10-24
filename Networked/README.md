# Networked
## The Art of Exploitation

> In this machine you will have to manipulate and study the inner code of how the web server works in order to gain access to the system

First, download and study the 10.10.10.146/backup folder, and then you can hop on to 10.10.10.146/upload.php, and upload yourself a php shell by manipulating the POST request with burp, for example.

> This will grant you shell access to the machine, now upgrade that shell access into a meterpreter one, and lets get to business.

> You can run use post/multi/recon/local_exploit_suggester to find possible privilege escalations for the machine. A few will pop up.

```
[*] 10.10.10.146 - Collecting local exploits for x86/linux...
[*] 10.10.10.146 - 31 exploit checks are being tried...
[+] 10.10.10.146 - exploit/linux/local/netfilter_priv_esc_ipv4: The target appears to be vulnerable.
[+] 10.10.10.146 - exploit/linux/local/network_manager_vpnc_username_priv_esc: The target service is running, but could not be validated.
[+] 10.10.10.146 - exploit/linux/local/pkexec: The target service is running, but could not be validated.
```

> Turns out we cannot run any of these yet, we need to find another way to get in.
