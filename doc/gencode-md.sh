#!/bin/sh

printf '%s\n' 'Exemplaire du code'
printf '%s\n\n' '======================'

for file in "$@"; do
    title=$(basename $file)
    printf '\lstinputlisting[caption={%s}]{%s}\n\n'  "$title" "$file"
done
