// Restart Game
var restart = document.querySelector("#starter")

// Grabs all the squares
var squares = document.querySelectorAll('td')

// clear all the squares
function clearBoard() {
  for (var i = 0; i < squares.length; i++) {
    squares[i].textContent = '';
  }
}

restart.addEventListener('click',clearBoard)

// check the square marker
var prever = '';

function changeMark(){
  if(prever === '' || prever === 'O')
  {
    this.textContent = 'X';
    prever = 'X';
  }else if(prever === 'X'){
    this.textContent = 'O';
    prever = 'O'
  }
}

// function PlayTicTacToe(){
//   if(squares === ''){
//     prever = 'X';
//     if(prever)
//     }
//   }
// }

for (var i = 0; i < squares.length; i++) {
  if (squares[i].textContent !== 'X' || squares[i].textContent !== 'O'){
    squares[i].addEventListener('click', changeMark)
  }
}

// for loop to add event listener to all the squars
