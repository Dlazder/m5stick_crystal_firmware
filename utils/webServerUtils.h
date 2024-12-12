String mainHTML() {
	String html = "<!DOCTYPE html><html lang=\"en\"><head><meta charset=\"UTF-8\"><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\"><title>M5-power-firmware</title><link rel=\"stylesheet\" href=\"style.css\"></head><body><h1>M5 power firmware</h1><div class=\"screen\"></div><div class=\"controls\"><div><button class=\"control-btn btn-up\">↑</button><button class=\"control-btn btn-down\">↓</button></div><div><button class=\"control-btn btn-a\">A</button><button class=\"control-btn btn-b\">B</button></div></div><script src=\"index.js\"></script></body></html>";
	return html;
}

String mainCSS() {
	String css = "body {background: rgb(25, 25, 25);font-family: Arial, Helvetica, sans-serif;color: rgb(200, 255, 0);margin: 0;}h1 {text-transform: uppercase;text-align: center;}.container {margin: 0 auto;max-width: 600px;}.screen {margin: 20px auto;background: black;width: 80%;aspect-ratio: 2/1;overflow: hidden;max-width: 600px;}.controls {max-width: 600px;width: 80%;margin: 0 auto;display: flex;justify-content: space-around;}.control-btn {display: block;width: 80px;aspect-ratio: 1/1;background: transparent;border: 1px solid rgb(200, 255, 0);color: rgb(200, 255, 0);font-size: 50px;cursor: pointer;margin-top: 30px;}.menu-item {color: #fff;font-size: 40px;}.active {background: #fff;color: #000;}";
	return css;
}

String mainJS() {
	String js = "const screen = document.querySelector('.screen');let currentData = '';let cursor = 0;let currentType;document.querySelector('.btn-up').addEventListener('click', () => {sendToServer({data: 'up'}).then(res => res.text()).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));});document.querySelector('.btn-down').addEventListener('click', () => {sendToServer({data: 'down'}).then(res => res.text()).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));});document.querySelector('.btn-a').addEventListener('click', () => {sendToServer({data: 'a'}).then(res => res.text()).then(setTimeout(() => {sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res))}, 50));});document.querySelector('.btn-b').addEventListener('click', () => {sendToServer({data: 'b'}).then(res => res.text()).then(setTimeout(() => {sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res))}, 50));});function parse(dataString) {const type = dataString.split(\";\")[0];const cursor = Number(dataString.split(\";\")[1]);const menuItems = dataString.split(\";\").slice(2);return data = {type,cursor,menuItems: menuItems.map(e => e.split(\",\")),}}function draw(data) {screen.innerHTML = '';currentData = parse(data);/* if (currentData.cursor === currentData.menuItems.length) cursor = 0; *//* if (currentData.cursor < 0) cursor = menuItems.length - 1; */currentData.menuItems.forEach((e, i) => {const name = e[0];const htmlEl = document.createElement('div');htmlEl.innerText = `\u00A0${name}`;htmlEl.className = 'menu-item';if (i === currentData.cursor) {htmlEl.classList.add('active');}screen.append(htmlEl);});}async function sendToServer(argsObject) {const formData = new FormData();const args = Object.entries(argsObject);for (const [key, value] of args) {formData.append(key, value);};return await fetch('/post', {method: 'POST', body: formData});}sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res));";
	return js;
}

