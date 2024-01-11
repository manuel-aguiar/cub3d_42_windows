#powershell script
# Set-ExecutionPolicy Bypass -Scope Process
#via chatgpt, script to loop through sources and make a similar directory structure

# Specify source and destination paths
$srcPath = "srcs"
$objPath = "objs"

# Get a list of subdirectories in srcPath
$subdirectories = Get-ChildItem -Path $srcPath -Directory

# Loop through each subdirectory and create the corresponding directory in objPath
foreach ($subdir in $subdirectories) {
    $objSubdir = Join-Path $objPath $subdir.Name
    if (-not (Test-Path -Path $objSubdir)) {
        New-Item -ItemType Directory -Path $objSubdir -Force > $null
        # Write-Host "Created directory: $objSubdir"
    } else {
        # Write-Host "Directory already exists: $objSubdir"
    }
}
