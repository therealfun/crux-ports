#!/bin/bash

# License: Public Domain

readme_gen() {
	echo "# CRUX ports"

	echo "Name | Version | Description"
	echo "-|-|-"
	for p in */Pkgfile
	do (
		. $p
		url=$( grep -m1 '^# URL:'         $p | sed -n 's/[^:]*:[ ]*//p')
		desc=$(grep -m1 '^# Description:' $p | sed -n 's/[^:]*:[ ]*//p')

		echo "[$name]($url) | $version | $desc"
	) done
}

repgen() {
	find . -type d -printf "%P\n" \
		| egrep -v '^\.'      \
		| egrep '.+'          \
		| sort                \
		| sed 's/^/d:/'

	find . -type f -printf "%P\n"       \
		| egrep -v '^\.'            \
		| egrep -v '^[A-Z][^/]*$'   \
		| xargs md5sum              \
		| sort -k 2                 \
		| awk '{print "f:"$1":"$2}'
}

repgen     > REPO
readme_gen > README.md
git diff
git diff --cached
git status
for d in */; do upkg-mk -v $d || echo $d; done
