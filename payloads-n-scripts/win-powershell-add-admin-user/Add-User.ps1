# Enable RDP so we can access the system afterwards
Set-ItemProperty -Path 'HKLM:\System\CurrentControlSet\Control\Terminal Server' -name "fDenyTSConnections" -value 0

# Set up user
$username = "hackmin"
$password = ConvertTo-SecureString "Password123$" -AsPlainText -Force
New-LocalUser -Name "$username" -Password $password -FullName "$username" -Description "hackmin"

Add-LocalGroupMember -Group "Administrators" -Member "hackmin"
