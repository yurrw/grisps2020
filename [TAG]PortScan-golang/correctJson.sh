#!/bin/sh

for i in  $(seq 1 20)
do
	sed -i  '$(i)/^{"/' ports.json
done
# sed 's/,/}/g' ports.json
