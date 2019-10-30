# Blocky
## Mistakes -> PHPMYADMIN -> Creds -> SSH -> ROOT

> Dirb scan the whole website of 10.10.10.37, you'll find yourself an odd website that will
hold the credentials you will need to continue further

*http://10.10.10.37/plugins/files/* -> You will find a blockycore.jar file that you will
need to decompile and then you will be granted by credentials that you can use
for getting into phpmyadmin panel.

> After you are in phpmyadmin panel, find yourself the wordpress creds in the database. 
You will find yourself the username notch, and a hashed password. Now, you only need the username
and the previous password from the jar file to login through SSH as notch

*BOOM, you are in.*

> Now you can run a privesc recon

```
use post/multi/recon/local_exploit_suggester
set SESSION 1
run

[*] 10.10.10.37 - 31 exploit checks are being tried...
[+] 10.10.10.37 - exploit/linux/local/bpf_sign_extension_priv_esc: The target appears to be vulnerable.
[+] 10.10.10.37 - exploit/linux/local/glibc_realpath_priv_esc: The target appears to be vulnerable.
[+] 10.10.10.37 - exploit/linux/local/netfilter_priv_esc_ipv4: The target appears to be vulnerable.
[+] 10.10.10.37 - exploit/linux/local/pkexec: The target service is running, but could not be validated.
[*] Post module execution completed
```

> Boom, plenty of ways to get root. Pick your favorite one!

