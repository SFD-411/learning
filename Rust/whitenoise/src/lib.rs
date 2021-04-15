#[macro_use]
extern crate vst;
extern crate rand;

use vst::plugin::{Info, Plugin, Category};
use vst::buffer::AudioBuffer;
use vst::event::Event;
use vst::api::Events;
use rand::random;

#[derive(Default)]
struct WhiteNoise{
    notes: u8
}

// Implements a trait 'Plugin' for VST stuffs
impl Plugin for WhiteNoise {
    // vst std info
    fn get_info(&self) -> Info {
        Info {
            name: "WhiteNoise".to_string(),
            unique_id: 420,
            inputs: 2,
            outputs: 2,
            category: Category::Synth,
            ..Default::default()
        }
    }

    // receive events
    fn process_events(&mut self, events: &Events) {
        // match MIDI
        for event in events.events() {
            match event {
                Event::Midi(ev) => {
                    // note on/off
                    match ev.data[0] {
                        144 => self.notes += 1u8,
                        128 => self.notes -= 1u8,
                        _ => (),
                    }
                    // pitch of note is stored in ev.data[1]
                }
                // other events are irrelivant for now
                _ => (),
            }
        }
    }
    
    // audio generation
    fn process(&mut self, buffer: &mut AudioBuffer<f32>) {
        // check if a note is held or nah
        if self.notes == 0 {return}

        // split io buffer
        let (_, output_buffer) = buffer.split();

        // loop over output channels - L/R
        for output_channel in output_buffer.into_iter() {
            for output_sample in output_channel {
                *output_sample = (random::<f32>() - 0.5f32) * 2f32;
            }
        }
    }
}

plugin_main!(WhiteNoise);
