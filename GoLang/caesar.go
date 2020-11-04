package main

import( 
    "fmt"
    "strings"
    "bufio"
    "io"
    "os"
)

func main(){
    alpha := []rune(" ZYXWVUTSRQPONMLKJIHGFEDCBAzyxwvutsrqponmlkjihgfedcba0123456789!?/.,=-_)(*&^%$#@!~][}{';:><")

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

    for _, ch := range input {
        retainer = append(retainer, cipher(ch, delta, alpha))
    }

    fmt.Println(string(retainer))
}

func cipher(s rune, delta int, key []rune) rune{
    index := strings.IndexRune(string(key), s)
    
    if (index < 0 && index != ' ') {
        panic("index not found")
    }

    index = (index + delta) % len(key)

    return key[index]
}
