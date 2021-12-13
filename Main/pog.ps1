$house = Get-Location
$pros = Get-ChildItem -Path $house -Recurse -Include *.pros
$time = Get-Date -UFormat '%m/%d %T'
$pog = Get-Content $pros -raw | ConvertFrom-Json    
$pog.'py/state'.project_name = "Code ${time}"
$pog | ConvertTo-Json -depth 32| set-content $pros
Write-Output $time
pros build;
pros upload
