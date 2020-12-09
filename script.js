$(document).ready(function(){
    $("#clignotement").click(function(){
        var valeur = $("#clignotement").val();
        $.post("delayLed",{
            valeurDelayLed: valeur
        });
    });
});

function sendValue() {
		var xhttp = new XMLHttpRequest();
		xhttp.open("GET", "test", true);
		xhttp.send();
}

$(function() {
    $("#mySlider").slider({
		max: 255,
        slide: function(event, ui) {
            //update value display
			var s = document.getElementById("sliderValueDisplay").innerHTML = ""+ui.value;
			var xhttp = new XMLHttpRequest();
			xhttp.open("GET", "led_value/"+ui.value, true);
			xhttp.send();
        }
    });
});

function onButton(){
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "on", true);
    xhttp.send();
}

function offButton(){
    var xhttp = new XMLHttpRequest();
    xhttp.open("GET", "off", true);
    xhttp.send();
}

// pour l'ouverture fermeture de la sidebar

function w3_open() {
    document.getElementById("mySidebar").style.display = "block";
}

function w3_close() {
    document.getElementById("mySidebar").style.display = "none";
}
