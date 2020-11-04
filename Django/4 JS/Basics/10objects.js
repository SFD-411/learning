var employee = {
  name: "John Smith",
  job: "Programmer",
  age: 31,
  namelength : function(){
    console.log(this.name.length)
  },
  reporter: function(){
    alert("Name is "+this.name+", Job is "+this.job+", Age is "+this.age)
  },
  lastname: function(){
    console.log(this.name.split(" ")[1])
  }
}
