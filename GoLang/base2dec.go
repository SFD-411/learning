package GoLang

// Learning example sourced from Gophercises

func Base2Dec(value string, base int) int{
    const hexset = "0123456789ABCDEF"
    result := 0
    multiplier := 1

    // iterates through the input value index
    for i := len(value)-1; i>=0; i--{
        index := -1
        
        // iterates through the hexset characters
        for j, char := range hexset{
            if char == rune(value[i]){
                index = j
                break
            }
        }

        // err
        if index < 0{ panic("Invalid Character in Base to Decimal Conversion!") }

        result = result + index*multiplier
        multiplier = multiplier * base 
    }
    return result
}
