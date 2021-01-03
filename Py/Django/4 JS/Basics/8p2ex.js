var country1 = "USA";
var country2 = "Germany";
var country3 = "Spain";

var countries = [country1, country2, country3];
var myArr = ['one', 'two', 'three'];
var nest = [countries, myArr];
var iter = [];

for(var i = 0; i < myArr.length; i++){
  var new_string = nest[1][i]+" "+nest[0][i]
  iter.push(new_string)
}

for(item of iter){ console.log(item)}

function someFunc(string = "strings"){
  console.log(string+" is a thing!")
}

iter.forEach(someFunc)
