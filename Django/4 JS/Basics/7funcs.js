function hello(name="user"){
  console.log("hello "+name);
}

function addCat(num1,num2) {
  console.log(num1+num2)
}

function nameCall(name="Jose", title="Master"){
  return title+" "+name;
}

function maths(numbR){
  var result = numbR * numbR
  return result
}

var v = "Global Var"
var stuffs = "Global Stuffs"

function dumbFun(stuffs){
  console.log(v);
  stuffs = "this ain't the same nomo"
  console.log(stuffs);
}

dumbFun();
console.log(stuffs);
