// Чтение данных из файла JSON
async function getResponse() {
	//let response = await fetch('https://jsonplaceholder.typicode.com/photos')
	let response = await fetch('config.json')
	response = await response.json()
	console.log(response)
	
		document.getElementById('ssid').value = response._ssid
		document.getElementById('password').value = response._password

		document.getElementById('ssidAP').value = response._ssidAP
		document.getElementById('passwordAP').value = response._passwordAP

		document.getElementById('authB').value = response._authB
		document.getElementById('serverB').value = response._serverB
		document.getElementById('portB').value = response._portB

		document.getElementById('ssdp').value = response._ssdp

		document.getElementById('ssidW').value = response._ssidW
		document.getElementById('passwordW').value = response._passwordW

		document.getElementById('ssidFTP').value = response._ssidFTP
		document.getElementById('passwordFTP').value = response._passwordFTP
	
}
getResponse();


// Отправка данных на сервер
function val(id){
 var v = document.getElementById(id).value;
 return v;
}
function send_request(submit,server){
 request = new XMLHttpRequest();
 request.open("GET", server, true);
 request.send();
 save_status(submit,request);
}
function save_status(submit,request){
 old_submit = submit.value;
 request.onreadystatechange = function() {
  if (request.readyState != 4) return;
  submit.value = request.responseText;
  setTimeout(function(){
   submit.value=old_submit;
   submit_disabled(false);
  }, 1000);
 }
 submit.value = 'Подождите...';
 submit_disabled(true);
}
function submit_disabled(request){
 var inputs = document.getElementsByTagName("input");
 for (var i = 0; i < inputs.length; i++) {
  if (inputs[i].type === 'submit') {inputs[i].disabled = request;}
 }
}
function toggle(target) {
 var curVal = document.getElementById(target).className;
 document.getElementById(target).className = (curVal === 'hidden') ? 'show' : 'hidden';
}
