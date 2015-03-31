$vers = "0.0.0.7"
$root = "C:\test\tungsten"
$binname = "tungsten.exe"
$vpath = Join-Path $root -ChildPath "app"
$vpath = Join-Path $vpath -ChildPath $vers

if (Test-Path $vpath) {
  Write-Host "path exists. aborting"
  return
}

mkdir $vpath
copy F:\src\tungsten\out\debug\tungsten.exe $vpath
copy F:\src\tungsten\out\debug\base.dll $vpath
copy F:\src\tungsten\out\debug\wbrowser.dll $vpath

$rexe = Join-Path $root -ChildPath $binname
$texe = Join-Path $vpath -ChildPath $binname

if (Test-Path $rexe) {
  del $rexe
}
fsutil hardlink create $rexe $texe
