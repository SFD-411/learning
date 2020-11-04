var roster=[];

function addNew() {
  var newName = prompt("What name would you like to add?")
  roster.push(newName)
}

function remove() {
  var remover = prompt("What name would you like to remove?")
  var index = roster.indexOf(remover);
  roster.splice(index,1)
}

function display(){
  console.log(roster);
}

var start = prompt("Would you like to start the roster web app? Y/N?")
var request = "empty";

if (start === 'Y'){
  while (request !== "quit") {
    request = prompt("Please select an action: add, remove, display or quit.")
    if (request === 'add') {
      addNew();
    }
    else if (request === 'display') {
      display();
    }
    else if (request === 'remove') {
      remove();
    }
    else{
      alert("Invalid prompt. Program terminated.")
      request = "quit"
    }
  }
}
alert("Thanks for using the roster! Refresh to start over.")
