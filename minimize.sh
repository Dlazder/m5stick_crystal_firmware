minimized_html=$(tr -d '\r\n\t' < './web/index.html' | sed 's/"/\\"/g')
printf "String mainHTML() {\n\tString html = \"%s\";\n\treturn html;\n}\n\n" "$minimized_html" > './utils/webServerUtils.h'

minimized_css=$(tr -d '\r\n\t' < './web/style.css' | sed 's/"/\\"/g')
printf "String mainCSS() {\n\tString css = \"%s\";\n\treturn css;\n}\n\n" "$minimized_css" >> './utils/webServerUtils.h'

minimized_js=$(tr -d '\r\n\t' < './web/index.js' | sed 's/"/\\"/g')
printf "String mainJS() {\n\tString js = \"%s\";\n\treturn js;\n}\n\n" "$minimized_js" >> './utils/webServerUtils.h'

echo done