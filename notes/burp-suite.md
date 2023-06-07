# Burp Suite

A lot could be said about Burp.
Most of my learning on Burp happened before starting these notes, though.
So this will mostly contain small snippits.

## Misc.

In repeater, use CRTL+u to  encode the highlighted text.
CRTL+SHIFT+u to decode.

## Redirect cURL to Burp

say you have been fuzzing an API at `/users/v1` with cURL and you would like to continue the work in burp.
After turning on the proxy on burp, you can hit burp by adding `--insecure -x 127.0.0.1:8080` to the curl call:
```
curl --insecure -x 127.0.0.1:8080 -d '{"password":"pwned","username":"admin"}' -H 'Content-Type: application/json'  http://$RHOST:5002/users/v1/login
```

`-x 127.0.0.1:8080` points it to the proxy, and `--insecure` turns of SSL validation
