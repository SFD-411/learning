package GoLang


func Dec2Base(decimal, base int) string{
    const hexset = "0123456789ABCDEF"
    var result string
    
    for decimal > 0{
        remainder := decimal % base
        result = string(hexset[remainder]) + result
        decimal = decimal / base
    }

    return result
}
