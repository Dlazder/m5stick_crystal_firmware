document.querySelector('.btn-up').addEventListener('click', () => {
	sendToServer({data: 'up'});
});


document.querySelector('.btn-down').addEventListener('click', () => {
	sendToServer({data: 'down'});
});


document.querySelector('.btn-a').addEventListener('click', () => {
	sendToServer({data: 'a'});
});


document.querySelector('.btn-b').addEventListener('click', () => {
	sendToServer({data: 'b'});
});

async function sendToServer(argsObject) {
	const formData = new FormData();
	
	const args = Object.entries(argsObject);
	for (const [key, value] of args) {
		formData.append(key, value);
	}
	
	fetch('/post', {method: 'POST', body: formData});
}