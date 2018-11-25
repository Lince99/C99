#stupid thing

#find .* -type f -executable -delete
find . -type f -executable -not -path "./.git/*" -not -name "deleteExec.sh"
