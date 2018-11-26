#bash command that search for all executables avoiding this and git internal files,
#and after this, it deletes them
find . -type f -executable -not -path "./.git/*" -not -name "deleteExec.sh" -delete
