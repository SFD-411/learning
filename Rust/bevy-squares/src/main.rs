use bevy::{
    app::App,
    prelude::*,
};

const GRID: u32 = 12;
const SQSIZE: f32 = 0.9;


#[derive(SystemLabel, Debug, Hash, PartialEq, Eq, Clone)]
pub enum KeyStatus{
    Active,
    Dormant,
}

#[derive(Default)]
struct Key(Vec<Entity>);
struct ActiveKey(Option<Position>);
struct Activate { status: KeyStatus, }
struct ActiveEvent;
struct KeyColor { active: Handle<ColorMaterial>, dormant: Handle<ColorMaterial>, }
#[derive(Default, Copy, Clone, Eq, PartialEq, Hash)]
struct Position { x: i32, y: i32, }
struct Size { w: f32, h: f32 }

impl Size {
    pub fn square(x: f32) -> Self {
        Self{
            w: x,
            h: x,
        }
    }
}

fn setup(mut command: Commands, mut materials: ResMut<Assets<ColorMaterial>>){
    command.spawn_bundle(OrthographicCameraBundle::new_2d());
    command.insert_resource(
        KeyColor {
        active: materials.add(Color::rgb(0.1, 0.2, 0.6).into()),
        dormant: materials.add(Color::rgb(0.7, 0.6, 0.5).into())
        }
    );
}

fn pitch_table(mut command: &mut Commands, materials: &Handle<ColorMaterial>, position: Position,) -> Entity {
        command
            .spawn_bundle(SpriteBundle {
                material: materials.clone(),
                ..Default::default()
            })
            .insert(Key)
            .insert(position)
            .insert(Size::square(SQSIZE))
            .id()        
    }

fn spawn_dormant(mut command: Commands, materials: Res<KeyColor>, mut keys: ResMut<Key>,) {
    for pc in 0..12{
        for oct in 0..12{
            keys.0.push(pitch_table(
                    &mut command,
                    &materials.active,
                    Position { x: pc, y: oct },
            ));
        }
    }
}

//fn active_note()

fn scale(window: Res<Windows>, mut q: Query<(&Size, &mut Sprite)>){
    let surface = window.get_primary().unwrap();
    
    for (sprite_size, mut sprite) in q.iter_mut() {
        sprite.size = Vec2::new(
            sprite_size.w / GRID as f32 * surface.width() as f32,
            sprite_size.h / GRID as f32 * surface.height() as f32,
        )
    }
}

fn position(window: Res<Windows>, mut q: Query<(&Position, &mut Transform)>){
    let surface = window.get_primary().unwrap();
    
    fn offset(position: f32, window: f32, grid: f32) -> f32 {
        let tile = window / grid;
        position / grid * window - (window / 2.) + (tile / 2.)
    }
    
    for (position, mut transform) in q.iter_mut(){
        transform.translation = Vec3::new(
            offset(position.x as f32, surface.width() as f32, GRID as f32),
            offset(position.y as f32, surface.height() as f32, GRID as f32),
            0.0,
        );
    }
}

fn main() {
    println!("Musicae!");

    App::build()
        .insert_resource(WindowDescriptor{
            title: "MUSICAE!".to_string(),
            width: 600.0,
            height: 600.0,
            ..Default::default()
        })
        .add_startup_system(setup.system())
        .add_startup_stage("NOTEWORTHY", SystemStage::single(spawn_dormant.system()))
        .insert_resource(Key::default())
        .add_event::<ActiveEvent>()
        .add_system_set_to_stage(
            CoreStage::PostUpdate,
            SystemSet::new()
                .with_system(position.system())
                .with_system(scale.system()),
        )
        .add_plugins(DefaultPlugins)
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .run();
}
