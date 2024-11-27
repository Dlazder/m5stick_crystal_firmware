String mainHTML() {
	String html = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>M5-power-firmware</title><link rel=\"stylesheet\" href=\"style.css\"></head><body><h1>M5 power firmware</h1><div class=\"screen\"></div><div class=\"controls\"><div><button class=\"control-btn btn-up\">↑</button><button class=\"control-btn btn-down\">↓</button></div><div><button class=\"control-btn btn-a\">A</button><button class=\"control-btn btn-b\">B</button></div></div><script src=\"index.js\"></script></body></html>";
	return html;
}

String mainCSS() {
	String css = "body {background: rgb(25, 25, 25);font-family: Arial, Helvetica, sans-serif;color: rgb(200, 255, 0);margin: 0;text-transform: uppercase;}h1 {text-align: center;}.screen {margin: 20px auto;background: black;width: 80%;aspect-ratio: 2/1;}.controls {margin: 0 20px;display: flex;justify-content: space-around;}.control-btn {display: block;width: 80px;aspect-ratio: 1/1;background: transparent;border: 1px solid rgb(200, 255, 0);color: rgb(200, 255, 0);font-size: 50px;cursor: pointer;margin-top: 30px;}";
	return css;
}

String mainJS() {
	String js = "document.querySelector('.btn-up').addEventListener('click', () => {});document.querySelector('.btn-down').addEventListener('click', () => {});document.querySelector('.btn-a').addEventListener('click', () => {});document.querySelector('.btn-b').addEventListener('click', () => {});fetch(\"/post\", {body: 'test'});";
	return js;
}

