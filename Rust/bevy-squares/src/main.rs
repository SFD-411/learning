#![allow(unused_imports)]
#![allow(unused_variables)]
#![allow(dead_code)]

use bevy::{
    app::App,
    input::keyboard::{KeyCode, KeyboardInput},
    prelude::*,
};

const GRID: u32 = 12;
const SQSIZE: f32 = 0.9;

#[derive(SystemLabel, Debug, Hash, PartialEq, Eq, Clone)]
pub enum KeyStatus {
    Active,
    Dormant,
}

#[derive(Default)]
struct Key(Vec<Entity>);

struct KeyColor {
    /// Octave is Active AND Key is pressed
    pressed: Handle<ColorMaterial>,
    /// Octave is Active but no key is pressed
    active: Handle<ColorMaterial>,
    /// Octave is Dormant
    dormant: Handle<ColorMaterial>,
}

#[derive(Default, Copy, Clone, Eq, PartialEq, Hash)]
struct Tone { pc: u8, oct: u8 }
struct Octave { no: u8 }
struct Size { w: f32, h: f32 }


impl Size {
    pub fn square(x: f32) -> Self {
        Self {
            w: x,
            h: x,
        }
    }
}

fn setup(
    mut command: Commands,
    mut materials: ResMut<Assets<ColorMaterial>>,
    mut octave: ResMut<Octave>,
) {
    // Create 2d Camera
    command.spawn_bundle(OrthographicCameraBundle::new_2d());
    // Create Button Material Resource
    let pressed_material = materials.add(Color::rgb(0.0, 0.8, 0.2).into());
    let active_material = materials.add(Color::rgb(0.1, 0.2, 0.6).into());
    let dormant_material = materials.add(Color::rgb(0.7, 0.6, 0.5).into());
    command.insert_resource(
        KeyColor {
            pressed: pressed_material.clone(),
            active: active_material.clone(),
            dormant: dormant_material.clone(),
        }
    );
    command.insert_resource( ToneTracker::default() );
    // Create Buttons
    for oct in 0..12 {
        for pc in 0..12 {
            let entity = command
                .spawn_bundle(SpriteBundle {
                    material: dormant_material.clone(),
                    ..Default::default()
                })
                .insert(Tone { pc, oct })
                .insert(Size::square(SQSIZE))
                .id();
        }
    }
}

fn scale(window: Res<Windows>, mut q: Query<(&Size, &mut Sprite)>) {
    let surface = window.get_primary().unwrap();

    for (sprite_size, mut sprite) in q.iter_mut() {
        sprite.size = Vec2::new(
            sprite_size.w / GRID as f32 * surface.width() as f32,
            sprite_size.h / GRID as f32 * surface.height() as f32,
        )
    }
}

fn position(window: Res<Windows>, mut q: Query<(&Tone, &mut Transform)>) {
    let surface = window.get_primary().unwrap();

    fn offset(position: f32, window: f32, grid: f32) -> f32 {
        let tile = window / grid;
        position / grid * window - (window / 2.) + (tile / 2.)
    }

    for (position, mut transform) in q.iter_mut() {
        transform.translation = Vec3::new(
            offset(position.pc as f32, surface.width() as f32, GRID as f32),
            offset(position.oct as f32, surface.height() as f32, GRID as f32),
            0.0,
        );
    }
}

pub struct ToneTracker(u8, [bool; 144]);

impl ToneTracker {
    pub fn get_active_octave(&self) -> u8 {
        self.0
    }
    pub fn octave_pressed(&mut self, oct: u8) {
        self.0 = oct
    }
    pub fn set_octave_state(&mut self, octave: u8) {
        assert!(octave >= 1);
        assert!(octave <= 10);
        self.0 = octave;
    }
    pub fn tone_pressed(&self, oct: u8, pc: u8) -> bool {
        self.1[(oct * 12 + pc) as usize]
    }
    pub fn set_tone_state(&mut self, pc: u8, pressed: bool) {
        assert!(pc <= 23);
        self.1[(self.0 * 12 + pc) as usize] = pressed;
    }
}

impl Default for ToneTracker {
    fn default() -> ToneTracker {
        ToneTracker(4, [false; 144])
    }
}

impl Default for Octave {
    fn default() -> Octave {
        Octave { no: 4 }
    }
}

/// This system prints out all keyboard events as they come in
fn keyboard_event_system(
    mut keyboard_input_events: EventReader<KeyboardInput>,
    mut tone_tracker: ResMut<ToneTracker>,
    mut octave: ResMut<Octave>,
) {
    for event in keyboard_input_events.iter() {
        match event.key_code {
            // Handle Octaves
            Some(KeyCode::Up) => {
                octave.no -= 1;
                tone_tracker.set_octave_state(octave.no);
            }
            Some(KeyCode::Down) => {
                octave.no += 1;
                tone_tracker.set_octave_state(octave.no);
            }
            Some(KeyCode::Q) => { tone_tracker.set_tone_state(12, event.state.is_pressed()) }
            Some(KeyCode::Key2) => { tone_tracker.set_tone_state(13, event.state.is_pressed()) }
            Some(KeyCode::W) => { tone_tracker.set_tone_state(14, event.state.is_pressed()) }
            Some(KeyCode::Key3) => { tone_tracker.set_tone_state(15, event.state.is_pressed()) }
            Some(KeyCode::E) => { tone_tracker.set_tone_state(16, event.state.is_pressed()) }
            Some(KeyCode::R) => { tone_tracker.set_tone_state(17, event.state.is_pressed()) }
            Some(KeyCode::Key5) => { tone_tracker.set_tone_state(18, event.state.is_pressed()) }
            Some(KeyCode::T) => { tone_tracker.set_tone_state(19, event.state.is_pressed()) }
            Some(KeyCode::Key6) => { tone_tracker.set_tone_state(20, event.state.is_pressed()) }
            Some(KeyCode::Y) => { tone_tracker.set_tone_state(21, event.state.is_pressed()) }
            Some(KeyCode::Key7) => { tone_tracker.set_tone_state(22, event.state.is_pressed()) }
            Some(KeyCode::U) => { tone_tracker.set_tone_state(23, event.state.is_pressed()) }
            Some(KeyCode::Z) => { tone_tracker.set_tone_state(0, event.state.is_pressed()) }
            Some(KeyCode::S) => { tone_tracker.set_tone_state(1, event.state.is_pressed()) }
            Some(KeyCode::X) => { tone_tracker.set_tone_state(2, event.state.is_pressed()) }
            Some(KeyCode::D) => { tone_tracker.set_tone_state(3, event.state.is_pressed()) }
            Some(KeyCode::C) => { tone_tracker.set_tone_state(4, event.state.is_pressed()) }
            Some(KeyCode::V) => { tone_tracker.set_tone_state(5, event.state.is_pressed()) }
            Some(KeyCode::G) => { tone_tracker.set_tone_state(6, event.state.is_pressed()) }
            Some(KeyCode::B) => { tone_tracker.set_tone_state(7, event.state.is_pressed()) }
            Some(KeyCode::H) => { tone_tracker.set_tone_state(8, event.state.is_pressed()) }
            Some(KeyCode::N) => { tone_tracker.set_tone_state(9, event.state.is_pressed()) }
            Some(KeyCode::J) => { tone_tracker.set_tone_state(10, event.state.is_pressed()) }
            Some(KeyCode::M) => { tone_tracker.set_tone_state(11, event.state.is_pressed()) }
            _ => ()
        }
    }
}

fn decorate(
    tone_tracker: Res<ToneTracker>,
    key_color: Res<KeyColor>,
    mut query: Query<(&Tone, &mut Handle<ColorMaterial>)>
) {
    for (tone, mut material) in query.iter_mut() {
        if tone_tracker.tone_pressed(tone.oct, tone.pc) {
            *material = key_color.pressed.clone();
        } else if tone_tracker.get_active_octave() == tone.oct {
            *material = key_color.active.clone(); 
        } else if tone_tracker.get_active_octave() + 1 == tone.oct {
            *material = key_color.active.clone(); 
        } else {
            *material = key_color.dormant.clone();
        }
    }
}

fn main() {
    println!("Musicae!");

    App::build()
        .insert_resource(WindowDescriptor {
            title: "MUSICAE!".to_string(),
            width: 600.0,
            height: 600.0,
            ..Default::default()
        })
        .add_startup_system(setup.system())
//        .add_startup_stage("NOTEWORTHY", SystemStage::single(setu.system()))
        .insert_resource(Key::default())
        .insert_resource(Octave::default())
        .add_system_set_to_stage(
            CoreStage::PostUpdate,
            SystemSet::new()
                .with_system(position.system())
                .with_system(scale.system()),
        )
        .add_system(keyboard_event_system.system())
        .add_system(decorate.system())
        .add_plugins(DefaultPlugins)
        .insert_resource(ClearColor(Color::rgb(0.1, 0.1, 0.1)))
        .run();
}
