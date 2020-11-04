<html>
<body>
<form method="post">
    Pick a Random Number between 1 and 10:
    <input type="number" name="number">
    <input type="submit" name="submit">
</form>
</body>
</html>
<?php
$randumb = rand(1,10);
if($_POST){
    $number = $_POST['number'];
    if ($number == $randumb){
        if(($number % 2) == 0){
            echo "GOOD JOB! You Guessed the Random Even Number $number!";
        } else {
            echo "GOOD JOB! You Guessed the Random Odd Number $number!";
        }
    } else {
        if(($number % 2) == 0){
            if (($randumb % 2) == 0){
                echo "You Guessed the Even Number $number, and the Secret Number was $randumb which is also Even!";
            } else {
                echo "You Guessed the Even Number $number, and the Secret Number was $randumb which is Odd!";
            }
        } else {
            if (($randumb % 2) == 0){
                echo "You Guessed the Odd Number $number, and the Secret Number was $randumb which is Even!";
            } else {
                echo "You Guessed the Odd Number $number, and the Secret Number was $randumb which is also Odd!";
            }
        }
    }

}
?>
