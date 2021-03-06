#[macro_use]
extern crate glium;


fn main() {
    // gl header info
    use glium::{glutin, Surface};

    let event_loop = glutin::event_loop::EventLoop::new();
    let wb = glutin::window::WindowBuilder::new();
    let cb = glutin::ContextBuilder::new();
    let display = glium::Display::new(wb, cb, &event_loop).unwrap();

    // obj template
    #[derive(Copy, Clone)]
    struct Vertex {
        position: [f32; 2],
    }

    implement_vertex!(Vertex, position);


    // obj data
    let mut indexa: [(f32, f32); 144] = [(0.0, 0.0); 144];

    // generates 144 points
    for x in 0..12 {
        for y in 0..12 {
            indexa[y * 12 + x] = ((x as f32 - 5.5) * 0.12, (y as f32 - 5.5) * 0.12);
        }
    }
    
    // generate 576 Vertices
    let mut posit = vec![Vertex { position: [0.0, 0.0] }; 576]; // stores x,y location for each corner of each square
    let mut indexb = vec![0; 864]; // stores the indexing for each position

    let offset = 0.04;
    
    for i in 0..144 {
        let ind_x = indexa[i].0;
        let ind_y = indexa[i].1;
        posit[i * 4] = Vertex {position: [(ind_x - offset), (ind_y - offset)]};
        posit[(i * 4) + 1] = Vertex { position: [(ind_x - offset), (ind_y + offset)]};
        posit[(i * 4) + 2] = Vertex { position: [(ind_x + offset), (ind_y + offset)]};
        posit[(i * 4) + 3] = Vertex { position: [(ind_x + offset), (ind_y - offset)]};
        indexb[i * 6] = (i * 4) as u32;
        indexb[(i * 6) + 1] = ((i * 4) + 1) as u32;
        indexb[(i * 6) + 2] = ((i * 4) + 2) as u32;
        indexb[(i * 6) + 3] = ((i * 4) + 2) as u32;
        indexb[(i * 6) + 4] = ((i * 4) + 3) as u32;
        indexb[(i * 6) + 5] = (i * 4) as u32;
    }

    //let posit = vec![vert1, vert2, vert3, vert3, vert4, vert1];

    // obj buffer
    let tl = glium::VertexBuffer::new(&display, &posit).unwrap();
    let indices = glium::IndexBuffer::new(&display, glium::index::PrimitiveType::TrianglesList, &indexb).unwrap();

    // shader data
    let vertex_shader_src = r#"
      #version 140

      in vec2 position;

      void main(){
        gl_Position = vec4(position, 0.0, 1.0);
      }
    "#;

    let fragment_shader_src = r#"
      #version 140

      out vec4 color;

      void main() {
        color = vec4(0.7, 0.7, 0.7, 1.0);
      }
    "#;
    
    let program = glium::Program::from_source(&display, vertex_shader_src, fragment_shader_src, None).unwrap();


    event_loop.run(move |ev, _, control_flow| {
        let next_frame_time = std::time::Instant::now() + 
            std::time::Duration::from_nanos(16_666_667);
        *control_flow = glutin::event_loop::ControlFlow::WaitUntil(next_frame_time);

        match ev {
            glutin::event::Event::WindowEvent {event, .. } => match event {
                glutin::event::WindowEvent::CloseRequested => {
                    *control_flow = glutin::event_loop::ControlFlow::Exit;
                    return;
                },
                _ => return,
            },
            glutin::event::Event::NewEvents(cause) => match cause {
                glutin::event::StartCause::ResumeTimeReached{ ..  } => (),
                glutin::event::StartCause::Init => (),
                _ => return,
            }
            _ => (),
        }
        let mut target = display.draw();
        target.clear_color(0.0, 0.0, 0.3, 1.0);
        target.draw(&tl, &indices, &program, &glium::uniforms::EmptyUniforms,
            &Default::default()).unwrap();
   //     target.draw(&br, &indices, &program, &glium::uniforms::EmptyUniforms,
     //       &Default::default()).unwrap();
        target.finish().unwrap();

    });
}
