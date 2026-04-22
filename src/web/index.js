const screen = document.querySelector('.screen');
const menuScreen = screen.querySelector('.menu-screen');
const functionScreen = screen.querySelector('.function-screen');

let currentData = '';
let cursor = 0;

document.querySelector('.btn-up').addEventListener('click', () => {
	sendToServer({data: 'up'}).then(res => res.text()).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));
});

document.querySelector('.btn-down').addEventListener('click', () => {
	sendToServer({data: 'down'}).then(res => res.text()).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));
});

document.querySelector('.btn-a').addEventListener('click', () => {
	sendToServer({data: 'a'}).then(res => res.text()).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));
});

document.querySelector('.btn-b').addEventListener('click', () => {
	if (currentData.type === "function") {
		sendToServer({data: 'b'}).then(sendToServer({data: 'update'}).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res))));
	} else sendToServer({data: 'b'}).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));
});

document.querySelector('.btn-update').addEventListener('click', () => {
	sendToServer({data: 'update'}).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));
});

function parse(dataString) {
	dataString = dataString.replace(/;$/, '');
	const type = dataString.split(";")[0];
	if (type === "menu") {
		const cursor = Number(dataString.split(";")[1]);
		const menuItems = dataString.split(";").slice(2);
		return {
			type,
			cursor,
			menuItems: menuItems.map(e => e.split(",")),
		}
	} else if (type === "function") {
		const functionItems = dataString.split(";").slice(1);
		return {
			type,
			functionItems: functionItems.map(e => e.split(",")),
		}
	}
	
}

function draw(data) {
	clearScreen();
	currentData = parse(data);
	
	/* if (currentData.cursor === curr	entData.menuItems.length) cursor = 0; */
	/* if (currentData.cursor < 0) cursor = menuItems.length - 1; */
	if (currentData.type === "menu") {
		currentData.menuItems.forEach((e, i) => {
			const name = e[0];
			const htmlEl = document.createElement('div');
			htmlEl.innerText = `\u00A0${name}`;
			htmlEl.className = 'menu-item';
			if (i === currentData.cursor) {
				htmlEl.classList.add('active');
			}
			menuScreen.append(htmlEl);
		});
	} else if (currentData.type === "function") {
		currentData.functionItems.forEach((e, i) => {
			const text = e[0];
			const size = calcTextSize(e[1]);
			const align = e[2];
			const htmlEl = document.createElement('div');
			htmlEl.innerHTML = `${text}`;
			htmlEl.className = `function-item ${size} ${align}`;
			functionScreen.append(htmlEl);
		});
	}
	
}


function calcTextSize(sizeNum) {
	switch (Number(sizeNum)) {
		case 1:
			return "small";
		case 2:
			return "medium";
		case 3:
			return "big";
	}
}

function clearScreen() {
	functionScreen.innerHTML = '';
	menuScreen.innerHTML = '';
}

async function sendToServer(argsObject) {
	const formData = new FormData();
	
	const args = Object.entries(argsObject);
	for (const [key, value] of args) {
		formData.append(key, value);
	};
	
	return await fetch('/post', {method: 'POST', body: formData});
}


sendToServer({data: 'update'}).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));