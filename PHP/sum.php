<?php
$number = 3.1415926535;
$varnum = $number * 10000000000;
$sum = 0; $rem = 0;

for($i = 0; $i < strlen($number); $i++){
    $rem = $varnum % 10;
    $sum = $sum + $rem;
    $varnum = $varnum / 10;
}
echo "The Sum of number $number is $sum";
?>

