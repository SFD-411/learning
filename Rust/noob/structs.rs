#[derive(Debug)]
struct Person {
    name: String,
    age: u8,
}

struct Unit;

struct Tuple(i32, f32);

struct Point {
    xed: f32,
    yod: f32,
}

#[allow(dead_code)]
struct Rectangle {
    top_left: Point,
    bottom_right: Point,
}

fn main() {
    // create struct instance
    let name = String::from("Dick");
    let age = 21;
    let myself = Person { name, age };

    println!("{:?}", myself);

    // Instantiate a point
    let initpoint: Point = Point { xed: 100.3, yod: 2.7 };

    println!("initpoint values = ({}, {})", point.xed, point.yod);

    // new point using fields of previous
    let bottom_right = Point { xed: 5.2, ..initpoint };

    println!("bottom right values = ({}, {})", bottom_right.xed, bottom_right.yod);

    // Destruct the point using 'let'
    let Point { xed: top_edge, yod: left_edge } = initpoint;
    

    let rectangle = Rectangle {
        top_left: Point { xed: left_edge, yod: top_edge },
        bottom_right: bottom:right,
    }

    println!("Rect.top_left ({}, {}) \nRect.bottom_right ({}, {})", 
        rect.top_left.xed, rect.top_left.yod, rect.bottom_right.xed, rect.bottom_right.yod);

    let _unit = Unit;

    let tuple = Tuple(1, 0.1);

    println!("tuple contains {:?} and {:?}", tuple.0, tuple.1);


    let Pair(integer, decimal) = pair;

    println!("pair contains {:?} and {:?}", integer, decimal);
}
