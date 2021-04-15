use rand::prelude::random;
use bevy::{
    core::FixedTimestep,
    app::App,
    prelude::*,
    //ecs::schedule::RunOnce,
};

// dimensions
const AWIDTH: u32 = 24;
const AHEIGHT: u32 = 24;
const SQSIZE: f32 = 0.8;
static mut speed: f64 = 0.5;
static mut level: i32 = 1;

// snake status
#[derive(SystemLabel, Debug, Hash, PartialEq, Eq, Clone)]
pub enum SnakeMoves {
    Input,
    Move,
    Eat,
    Grow,
}

// snake head directions
#[derive(PartialEq, Copy, Clone)]
enum Direction {
    Left,
    Up,
    Right,
    Down,
}

impl Direction {
    fn opposite(self) -> Self {
        match self {
            Self::Left => Self::Right,
            Self::Right => Self::Left,
            Self::Up => Self::Down,
            Self::Down => Self::Up,
        }
    }
}

// data placeholders
struct SnekHed { direct: Direction, }
#[derive(Default)]
struct SnekBod(Vec<Entity>);
#[derive(Default)]
struct TailTell(Option<Pos>);
struct Food;
struct FoodEvent;
struct GrowthEvent;
struct Mats { head: Handle<ColorMaterial>, food: Handle<ColorMaterial>, }
#[derive(Default, Copy, Clone, Eq, PartialEq, Hash)]
struct Pos { x: i32, y: i32, }
struct Size { w: f32, h: f32, }

// square size
impl Size {
    pub fn square(x: f32) -> Self {
        Self {
            w: x,
            h: x,
        }
    }
}

// FUNCTIONS //
// initialized resources
fn setup(mut commands: Commands, mut materials: ResMut<Assets<ColorMaterial>>){
    commands.spawn_bundle(OrthographicCameraBundle::new_2d());
    commands.insert_resource(Mats {
        head: materials.add(Color::rgb(0.0, 0.0, 0.7).into()),
        food: materials.add(Color::rgb(0.7, 0.1, 0.3).into())
    });
}

// creates snek obj
fn snek_bod(mut commands: Commands, material: &Handle<ColorMaterial>, pos: Pos,) -> Entity {
    commands
        .spawn_bundle(SpriteBundle {
            material: material.clone(),
            ..Default::default()
        })
    .insert(SnekBod)
    .insert(pos)
    .insert(Size::square(SQSIZE))
    .id()
}

fn snek_spawn(mut commands: Commands, materials: Res<Mats>, 
        mut body: ResMut<SnekBod>, mut feed: EventWriter<FoodEvent>)
{
    body.0 = vec![
        commands
            .spawn_bundle(SpriteBundle {
                material: materials.head.clone(),
                sprite: Sprite::new(Vec2:: new(10.0, 10.0)),
                ..Default::default()
            })
            .insert(SnekHed { direct: Direction::Right })
            .insert(SnekBod)
            .insert(Pos { x: 12, y: 12 })
            .insert(Size::square(SQSIZE))
            .id(),
        snek_bod( commands, &materials.head, Pos { x: 11, y: 12 },),
    ];
    feed.send(FoodEvent);
}

// generates food obj in random locations
fn snak_spawn(mut commands: Commands, materials: Res<Mats>, mut foodif: EventReader<FoodEvent>)
{
    if foodif.iter().next().is_some(){
        commands
            .spawn_bundle(SpriteBundle {
                material: materials.food.clone(),
                ..Default::default()
            })
            .insert(Food)
            .insert(Pos{
                x: (random::<f32>() * AWIDTH as f32) as i32,
                y: (random::<f32>() * AHEIGHT as f32) as i32,
            })
            .insert(Size::square(SQSIZE));   
    }
}

// handles spite sizing
fn scaling(windows: Res<Windows>, mut q: Query<(&Size, &mut Sprite)>) 
{
    let window = windows.get_primary().unwrap();
    for (sprite_size, mut sprite) in q.iter_mut() {
        sprite.size = Vec2::new(
            sprite_size.w / AWIDTH as f32 * window.width() as f32,
            sprite_size.h / AHEIGHT as f32 * window.height() as f32,
        );
    }
}

// aligns sprites to bottom left
fn positioning(windows: Res<Windows>, mut q: Query<(&Pos, &mut Transform)>) {
    fn convert(pos: f32, bound_window: f32, bound_game: f32) -> f32 {
        let tile_size = bound_window / bound_game;
        pos / bound_game * bound_window - (bound_window / 2.) + (tile_size / 2.)
    }
    let window = windows.get_primary().unwrap();
    for (pos, mut transform) in q.iter_mut(){
        transform.translation = Vec3::new(
            convert(pos.x as f32, window.width() as f32, AWIDTH as f32),
            convert(pos.y as f32, window.height() as f32, AHEIGHT as f32),
            0.0,
        );
    }
}

// snake movement logic
fn snek_move_in(key_in: Res<Input<KeyCode>>, mut head: Query<&mut SnekHed>,){
    if let Some(mut hed) = head.iter_mut().next() {
        let dir: Direction = 
            if key_in.pressed(KeyCode::Left) 
                { Direction::Left } else 
            if key_in.pressed(KeyCode::Right)
                { Direction::Right } else
            if key_in.pressed(KeyCode::Up)
                { Direction::Up } else
            if key_in.pressed(KeyCode::Down) 
                { Direction::Down }
            else { hed.direct };
            if dir != hed.direct.opposite() {
                hed.direct = dir;
            }
    }
}

fn snek_move(mut telpos: ResMut<TailTell>, segs: ResMut<SnekBod>, 
    mut head: Query<(Entity, &SnekHed)>, mut pos: Query<&mut Pos>,)
{
    if let Some((head_entity, hed)) = head.iter_mut().next(){
        let segs_pos = segs
            .0
            .iter()
            .map(|e| *pos.get_mut(*e).unwrap())
            .collect::<Vec<Pos>>();
        let mut head_pos = pos.get_mut(head_entity).unwrap();
        match &hed.direct {
            Direction::Left => { head_pos.x -= 1; }
            Direction::Right => { head_pos.x += 1; }
            Direction::Up => { head_pos.y += 1; }
            Direction::Down => { head_pos.y -= 1; }
        };
        segs_pos
            .iter()
            .zip(segs.0.iter().skip(1))
            .for_each(|(posit, segment)| {
                *pos.get_mut(*segment).unwrap() = *posit;
            });
        telpos.0 = Some(*segs_pos.last().unwrap());
    }
}

fn snek_eat(mut commands: Commands, mut grow: EventWriter<GrowthEvent>, 
    mut feed: EventWriter<FoodEvent>,
    food_pos: Query<(Entity, &Pos), With<Food>>,
    head_pos: Query<&Pos, With<SnekHed>>,)
{
    for hedpos in head_pos.iter() 
    {
        for (ent, foodpos) in food_pos.iter() 
        {
            if foodpos == hedpos 
            {
                commands.entity(ent).despawn();
                grow.send(GrowthEvent);
                feed.send(FoodEvent);
                unsafe{
                    speed -= 0.1;
                    level += 1;       
                }
            }
        }
    }
}

fn snek_grow(
    commands: Commands,
    telpos: Res<TailTell>,
    mut segs: ResMut<SnekBod>,
    mut growif: EventReader<GrowthEvent>,
    mats: Res<Mats>,)
{
    if growif.iter().next().is_some() {
        segs.0.push(snek_bod(
                commands,
                &mats.head,
                telpos.0.unwrap(),
        ));
    }
}

fn main() {
    App::build()
        .insert_resource(WindowDescriptor {
            title: "SNEKR!".to_string(),
            width: 500.0,
            height: 500.0,
            ..Default::default()
            })
        .add_startup_system(setup.system())
        .add_startup_stage("Game Time", SystemStage::single(snek_spawn.system()))
        .insert_resource(SnekBod::default())
        .insert_resource(TailTell::default())
        .add_event::<GrowthEvent>()
        .add_event::<FoodEvent>()
        .add_system_set(
            SystemSet::new()
                .with_system(
                    snak_spawn
                        .system()
                        .label(SnakeMoves::Grow)
                        .after(SnakeMoves::Eat)
                ),
            )
        .add_system(snek_move_in
            .system()
            .label(SnakeMoves::Input)
            .before(SnakeMoves::Move),
            )
        .add_system_set(
            SystemSet::new()
                .with_run_criteria(FixedTimestep::step(unsafe{speed}))
                .with_system(snek_move.system().label(SnakeMoves::Move))
                .with_system(
                    snek_eat
                        .system()
                        .label(SnakeMoves::Eat)
                        .after(SnakeMoves::Move),
                )
                .with_system(
                    snek_grow
                        .system()
                        .label(SnakeMoves::Grow)
                        .after(SnakeMoves::Eat),
                )
            )
        .add_system_set_to_stage(
            CoreStage::PostUpdate,
            SystemSet::new()
                .with_system(positioning.system())
                .with_system(scaling.system()),
            )
        .add_plugins(DefaultPlugins)
        .insert_resource(ClearColor(Color::rgb(0.04, 0.04, 0.04)))
        .run();
}
