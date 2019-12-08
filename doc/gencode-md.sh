#!/bin/sh

printf '%s\n' 'Exemplaire du code'
printf '%s\n\n' '======================'

for file in "$@"; do
    title=$(basename $file)
    printf '%s\n\n' "## $title"
    printf '\lstinputlisting[language=c]{%s}\n\n' "$file"
done
