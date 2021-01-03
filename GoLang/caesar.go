package main

import( 
    "fmt"
    "strings"
    "bufio"
    "io"
    "os"
)

func main(){
    alpha := []rune("0 1Z2a3Y4b5X6c7W8d9V!e?U/f.T,S=h-R_i)Q(j*P&kO^lN%mM$nL#oK@pJ~qI]rH[sG}tF{uE'vD:wC;xB>yA<z")

    var input []rune
    var retainer []rune

    stdin := bufio.NewReader(os.Stdin)
    
    fmt.Println("Enter Cypher Text: ")
    
    for {
        c, _, err := stdin.ReadRune()
        if err == io.EOF || c == '\n' {break}
        input = append(input, c)
    }

    delta := len(input)
    counter := 0

    for _, ch := range input {
        counter = counter + 1
        retainer = append(retainer, cipher(ch, delta, alpha, counter))
    }

    fmt.Println(string(retainer))
}

func cipher(s rune, delta int, key []rune, counter int) rune{
    index := strings.IndexRune(string(key), s)
    
    if (index < 0 && index != ' ') {
        panic("index not found")
    }

    index = (index + delta) * counter % len(key)

    return key[index]
}
