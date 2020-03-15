#!/bin/bash

## simple backup script
## save folders in tar.gz daily
## saves the last 3 tars
backup_folders="./t1 ./t2 ./t3"
backup_dir="./backup"
prefix="backup-"
suffix=".tgz"

rotation()
{
# nao eh a melhor solucao mas funciona pra esse caso simples
# deleta os backups mais antigos do que 3 dias
    find $backup_dir -mindepth 1 -mtime +3 -delete
}
# Print start status message.
date=$(date +%y)-$(date +%m)-$(date +%d)
echo "Backing up $backup_folders to $backup_dir/$prefix$date$suffix"
date
echo

tar czf $backup_dir/$prefix$date$suffix $backup_folders

echo
echo "Backup finished"
rotation
# Long listing of files in $dest to check file sizes.
ls -lh $backup_dir/
