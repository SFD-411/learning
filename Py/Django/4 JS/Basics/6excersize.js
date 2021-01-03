ufname = prompt("Enter Your First Name: ")
ulname = prompt("Enter Your Last Name: ")
if (ufname[0] == ulname[0]){
  uage = prompt("Enter Your Age: ")
  if (27 < uage < 31){
    uheight = prompt("Enter Your Height in cm: ")
    if (uheight > 170){
      upet = prompt ("Enter Your Pet Name: ")
      if (upet[upet.length - 1] === 'y'){
        console.log("This Is Top Secret Business Kid!")
      } else {
        alert("Who do you think you are?!")
      }
    } else {
      alert("Not so fast Short Stuff!")
    }
  } else {
    alert("You just don't make the cut.")
  }
} else {
  alert("Sorry. You are not him.")
}
