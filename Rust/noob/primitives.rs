fn main() {
    // variable annotation
    let logical: bool = true;
    let a_float: f64 = 1.0; // regular annotation
    let an_int = 5i32;// suffix annotation
    // default 
    let def_float = 3.0; // f64
    let def_int = 7; // i32
    // inferred
    let mut inferred_type = 12; // i64 inferred from next line
    inferred_type = 4294967296i64;

    // mutable variables can be changed
    let mut mutable = 12;
    mutable = 21;
    // mutable = true; will not work
    let mutable = true; // Variables can be overwritten with shadowing.
}
