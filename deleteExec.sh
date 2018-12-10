#bash command that search for all executables avoiding this and git internal files,
#and after this, it deletes them
#TODO FIX, this deletes makefiles
#find . -type f -executable -not -path "./.git/*" -not -name "deleteExec.sh" -delete
