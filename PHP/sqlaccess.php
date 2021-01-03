<html>
<body>
<form method="post">
    Edit Song Database:<br>
    Song ID Number:
    <input type="number" name="songid"><br>
    Artist Name:
    <input type="text" name="artist"><br>
    Song Title:
    <input type="text" name="track"><br>
    Album Title:
    <input type="text" name="album"><br>
    Release Date: "YYYY-MM-DD"
    <input type="text" name="release"><br>
    Songwriters:
    <input type="text" name="songwriters"><br>
    Producers:
    <input type="text" name="producers"><br>
    Contributing Artists:
    <input type="text" name="contributors"><br>
    Insert : <input type="submit" name="submit"><br>
    
    </form>
</body>
</html>

<?php

$user = 'phpaccess';
$pass = 'testing';

    
if($_POST){
    // create PHP Database Object
    $myPDO = new PDO('mysql:host=localhost; dbname=BrandMedia', $user, $pass);
    $myPDO->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
    $songid = $_POST['songid'];
    $artist = $_POST['artist'];
    $track = $_POST['track'];
    $album = $_POST['album'];
    $release = $_POST['release'];
    $songwriters = $_POST['songwriters'];
    $producers = $_POST['producers'];
    $contributors = $_POST['contributors'];

    if($track && $songid){
        // access DB
        $inserttabledata = $myPDO->prepare("
            INSERT INTO music (song_id, artist_name, track_name, album_title, release_date, songwriters, producers, contributing_artist)
            VALUES('$songid', '$artist', '$track', '$album', '$release', '$songwriters', '$producers', '$contributors');
        "       );
        $inserttabledata->execute();
    } else if(!$track && $songid){
        $deletetabledata = $myPDO->prepare("DELETE FROM music WHERE song_id='$songid'");
        $deletetabledata->execute();
    }
    $myPDO = null;
}


echo "<table style='border: solid 1px black;'>";
echo "<tr><th>Song ID</th><th>Artist Name</th><th>Track Name</th><th>Album Title</th><th>Release Date</th><th>Songwriters</th><th>Producers</th><th>Contributing Artists</th></tr>";

class TableRows extends RecursiveIteratorIterator {
    function __construct($it){
        parent::__construct($it, self::LEAVES_ONLY);
    }

    function current(){
        return "<td style='border:1px solid black;'>".parent::current()."</td>";
    }

    function beginChildren(){
        echo "<tr>";
    }

    function endChildren(){
        echo "</tr>"."\n";
    }
}



try{

    $myPDO = new PDO('mysql:host=localhost; dbname=BrandMedia', $user, $pass);
    $myPDO->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    
    // collect data from table
    $gettabledata = $myPDO->prepare("SELECT * FROM music");
    $gettabledata->execute();
    
    // format associateive data
    $results = $gettabledata->setFetchMode(PDO::FETCH_ASSOC);
    foreach(new TableRows(new RecursiveArrayIterator($gettabledata->fetchAll())) as $k=>$v){
        echo $v;
    }
} catch (PDOException $e){
    echo "ERROR: ".$e->getMessage();
}
$myPDO = null;
echo "</table>";
?>

