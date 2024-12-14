const screen = document.querySelector('.screen');

let currentData = '';
let cursor = 0;
let currentType;

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
	sendToServer({data: 'b'}).then(res => res.text()).then(sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res)));
});

function parse(dataString) {
	const type = dataString.split(";")[0];
	const cursor = Number(dataString.split(";")[1]);
	const menuItems = dataString.split(";").slice(2);
	return data = {
		type,
		cursor,
		menuItems: menuItems.map(e => e.split(",")),
	}
}

function draw(data) {
	screen.innerHTML = '';
	currentData = parse(data);
	
	/* if (currentData.cursor === curr	entData.menuItems.length) cursor = 0; */
	/* if (currentData.cursor < 0) cursor = menuItems.length - 1; */
	currentData.menuItems.forEach((e, i) => {
		const name = e[0];
		const htmlEl = document.createElement('div');
		htmlEl.innerText = `\u00A0${name}`;
		htmlEl.className = 'menu-item';
		if (i === currentData.cursor) {
			htmlEl.classList.add('active');
		}
		screen.append(htmlEl);
	});
}

async function sendToServer(argsObject) {
	const formData = new FormData();
	
	const args = Object.entries(argsObject);
	for (const [key, value] of args) {
		formData.append(key, value);
	};
	
	return await fetch('/post', {method: 'POST', body: formData});
}


sendToServer({data: 'get'}).then(res => res.text()).then(res => draw(res));