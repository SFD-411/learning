var hot = false;
var temp = 60;

if (temp > 80) {
  console.log(hot)
} else { console.log(!hot)}

var ham = 10;
var cheese = 10;

var report = "blank";

if (ham >= 10 && cheese >= 10){
  report = "strong sales"
} else if (ham === 0 && cheese === 0){
  report = "nothing sold"
} else {
  report = "making sales"
}

;console.log(report);
