use bevy::{
    app::{App, Plugin},
    prelude::*,
};

pub struct HelloPlug;
struct Person;
struct Name(String);

fn hello(){  println!("Hello, World!"); }

fn populate(mut commands: Commands){
    commands.spawn().insert(Person).insert(Name("Fuck Face".to_string()));
    commands.spawn().insert(Person).insert(Name("Foreskin Man".to_string()));
    commands.spawn().insert(Person).insert(Name("B Flat".to_string()));
}

fn greetings(query: Query<&Name, With<Person>>){
    for name in query.iter() {
        println!("Hello {}!", name.0);
    }
}

impl Plugin for HelloPlug {
    fn build(&self, app: &mut AppBuilder) {
        app.add_startup_system(populate.system())
        .add_system(hello.system())
        .add_system(greetings.system());
    }
}

fn main() {
    App::build()
        .add_plugins(DefaultPlugins)
        .add_plugin(HelloPlug)
        .run();
}
