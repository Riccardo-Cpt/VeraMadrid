var aPos = [];
var k;
var loaded = false;

$(document).ready(function() {
	$("#start").click(function() {
		if(loaded) {
			$("#cover").slideUp(1500);
		}
	});
});



$(window).load(function() {
	var tables = $("table");
	for(var i = 0; i < tables.length; i ++) {
		var img = $(tables[i]).find("img");
		var imgCell = $(tables[i]).find(".imgCell");
		var desc = $(tables[i]).find(".description");
		
		img.css("height", window.innerHeight - $("#description").height() - 64);
	}
	k = window.innerHeight / 4;
		
	$("#cover").css("height", window.innerHeight);
	
	var elem = $("#cover > div");
	$(elem).css("top", ($(window).height() - $(elem).height()) / 2);
	$(elem).css("left", ($(window).width() - $(elem).width()) / 2);
	
	var d = $("#description");
	$(d).css("top", window.innerHeight - $(d).height());
	//$(d).css("width", window.innerWidth);
	
	var aElems = $("a");
	for(var i = 0; i < aElems.length; i ++) {
		aPos[i] = $(aElems[i]).position().top;
		//aPos[i] = i;
	}
	aPos[aPos.length] = $("body").height();
	
	$(document).scrollTop(0);
	$("#description").text(descs[0]);
	
	loaded = true;
	$("#loadingMess").hide();
});

//$(window).resize(setDim());

$(window).scroll(function() {
	var yPos = $(document).scrollTop();
	for(var i = 0; i < aPos.length - 1; i ++) {
		if(((aPos[i] - k) <= yPos) && (yPos < (aPos[i + 1] - k))) {
			$("#description").text(descs[i]);
			break;
		}
	}
});