#!/bin/sh
for x in *.h; do
tr -d '\r' < "$x" > "$x.dos"
mv -- "$x.dos" "$x"
done

